//#include <windows.h>
#include <CoreServices/CoreServices.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>
#define _SCL_SECURE_NO_WARNINGS
#define BOOST_DISABLE_ASSERTS 
#include <boost/multi_array.hpp>

int main(int argc, char* argv[])
{
    const int X_SIZE = 200;
    const int Y_SIZE = 200;
    const int ITERATIONS = 500;
    // unsigned int startTime = 0;
    // unsigned int endTime = 0;
    uint64_t        startTime;
    uint64_t        endTime;
    uint64_t        elapsed;
    Nanoseconds     elapsedNano;


    // Create the boost array
    typedef boost::multi_array<double, 2> ImageArrayType;
    ImageArrayType boostMatrix(boost::extents[X_SIZE][Y_SIZE]);

    // Create the native array
    double *nativeMatrix = new double [X_SIZE * Y_SIZE];

    //------------------Measure boost----------------------------------------------
    startTime = mach_absolute_time();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        for (int y = 0; y < Y_SIZE; ++y)
        {
            for (int x = 0; x < X_SIZE; ++x)
            {
                boostMatrix[y][x] = 2.345;
            }
        }
    }
    endTime = mach_absolute_time();
    elapsed = (endTime - startTime);
    elapsedNano = AbsoluteToNanoseconds( *(AbsoluteTime *) &elapsed );
    printf("[Boost] Elapsed time: %6.3f milliseconds\n", float(* (uint64_t *) &elapsedNano) / 1000.0f);

    //------------------Measure native-----------------------------------------------
    startTime = mach_absolute_time();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        for (int y = 0; y < Y_SIZE; ++y)
        {
            for (int x = 0; x < X_SIZE; ++x)
            {
                nativeMatrix[x + (y * X_SIZE)] = 2.345;
            }
        }
    }
    endTime = mach_absolute_time();
    elapsed = (endTime - startTime);
    elapsedNano = AbsoluteToNanoseconds( *(AbsoluteTime *) &elapsed );
    printf("[Native]Elapsed time: %6.3f milliseconds\n", float(* (uint64_t *) &elapsedNano) / 1000.0f);

    return 0;
}