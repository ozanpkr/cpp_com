#include <iostream>
#include <thread>

// Function to be executed in parallel
void parallelFunction(int threadId) {
    std::cout << "Thread " << threadId << " is executing." << std::endl;
}

int main() {
    const int numThreads = 5;
    std::thread threads[numThreads];

    // Launch multiple threads
    for (int i = 0; i < numThreads; i++) {
        threads[i] = std::thread(parallelFunction, i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    std::cout << "All threads have completed." << std::endl;

    return 0;
}
