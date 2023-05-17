#include <iostream>
#include <chrono>
#include <thread>

void pulsePerSecond(int frequency) {
    // Calculate the duration for one pulse based on the desired frequency
    std::chrono::duration<double> pulseDuration(1.0 / frequency);

    while (true) {
        // Start the timer
        auto startTime = std::chrono::steady_clock::now();

        // Perform the tasks within the loop
        for (int i = 0; i < 10; i++) {
            // Perform your desired operations here
            std::cout << "Iteration: " << i << std::endl;
        }

        // Calculate the elapsed time since the start of the pulse
        auto endTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

        // Sleep for the remaining time of the pulse duration
        auto sleepTime = pulseDuration - elapsed;
        if (sleepTime > std::chrono::duration<double>::zero()) {
            std::this_thread::sleep_for(sleepTime);
        }
    }
}

int main() {
    int frequency = 10;  // Set the desired frequency in pulses per second
    pulsePerSecond(frequency);

    return 0;
}
