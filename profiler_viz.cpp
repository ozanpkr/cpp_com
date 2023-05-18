#include <iostream>
#include <cstdlib>
#include <google/profiler.h>

int main() {
    // Run the profiler
    ProfilerStart("myFunction.prof");

    // Run the code to profile
    // ...

    // Stop the profiler
    ProfilerStop();

    // Visualize the profiling data
    std::string command = "pprof --callgrind myProgram myFunction.prof > profile.callgrind";
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to generate callgrind profile" << std::endl;
        return 1;
    }

    // Open the generated callgrind profile in a web browser
    std::string visualizationCommand = "google-chrome-stable --headless --disable-gpu --no-sandbox --remote-debugging-port=9222 --print-to-pdf=profile.pdf http://localhost:9222/callgrind";
    result = std::system(visualizationCommand.c_str());
    if (result != 0) {
        std::cerr << "Failed to open the profiling visualization" << std::endl;
        return 1;
    }

    std::cout << "Profiling visualization saved to profile.pdf" << std::endl;

    return 0;
}
