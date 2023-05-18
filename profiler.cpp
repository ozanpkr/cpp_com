#include <iostream>
#include <gperftools/profiler.h>

// Function to profile
void myFunction() {
    // Simulate some work
    for (int i = 0; i < 1000000; ++i) {
        // Some computation
    }
}

int main() {
    // Start profiling
    ProfilerStart("myFunction.prof");

    // Call the function to profile
    myFunction();

    // Stop profiling
    ProfilerStop();

    std::cout << "Profiling data saved to myFunction.prof" << std::endl;

    return 0;
}
