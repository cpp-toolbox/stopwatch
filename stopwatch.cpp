#include "stopwatch.hpp"

void Stopwatch::press() {
    if (first_time) {
        previous_time = std::chrono::system_clock::now();
        first_time = false;
    } else {
        std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
        // note that we have to assign it the type on the left because otherwise
        // the difference would have type std::chrono::system_clock::duration
        // which is measured in nanoseconds
        std::chrono::duration<double> delta = current_time - previous_time;
        times[curr_idx] = delta.count();
        curr_idx = (curr_idx + 1) % num_times_to_average_over; // circular clobbering array.
        previous_time = current_time;
    }
    average_frequency = 1.0 / this->compute_average_period();
}

double Stopwatch::compute_average_period() {
    double delta_sum = 0.0;
    for (int i = 0; i < num_times_to_average_over; i++) {
        delta_sum += times[i];
    }
    return delta_sum / (double)num_times_to_average_over;
}
