#include <iostream>
#include <omp.h>

void parallelForLoop(int numIterations) {
    #pragma omp parallel for
    for (int i = 0; i < numIterations; i++) {
        int threadId = omp_get_thread_num();
        std::cout << "Thread " << threadId << ": Iteration " << i << std::endl;

        // Perform your computations or operations here
        // ...

        // Example: Accumulate the sum of iterations
        #pragma omp critical
        {
            static int sum = 0;
            sum += i;
            std::cout << "Thread " << threadId << ": Current Sum: " << sum << std::endl;
        }
    }
}

int main() {
    int numIterations = 10;

    // Set the number of threads
    omp_set_num_threads(4);

    parallelForLoop(numIterations);

    return 0;
}
