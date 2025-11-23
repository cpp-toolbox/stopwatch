#include "stopwatch.hpp"

void Stopwatch::press() {
    auto current_time = std::chrono::system_clock::now();
    if (first_time) {
        previous_time = current_time;
        first_time = false;
        return;
    }

    std::chrono::duration<double> delta = current_time - previous_time;
    double delta_sec = delta.count();

    // Add to circular buffers
    micro_times.push_back(delta_sec);
    macro_times.push_back(delta_sec);

    previous_time = current_time;
}

StopwatchStats Stopwatch::get_micro_stats() const {
    double mean = math_utils::compute_mean(micro_times.to_vector());
    double var = math_utils::compute_variance(micro_times.to_vector());
    double stddev = std::sqrt(var);
    double freq = mean > 0.0 ? 1.0 / mean : 0.0;
    return StopwatchStats{mean, var, stddev, freq};
}

StopwatchStats Stopwatch::get_macro_stats() const {
    double mean = math_utils::compute_mean(macro_times.to_vector());
    double var = math_utils::compute_variance(macro_times.to_vector());
    double stddev = std::sqrt(var);
    double freq = mean > 0.0 ? 1.0 / mean : 0.0;
    return StopwatchStats{mean, var, stddev, freq};
}
