#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <limits>

#include "sbpt_generated_includes.hpp"

/**
 * @brief Statistics for a Stopwatch.
 */
struct StopwatchStats {
    double mean_period;       /**< Average time between presses in seconds */
    double variance_period;   /**< Variance of the periods */
    double stddev_period;     /**< Standard deviation of the periods */
    double average_frequency; /**< Average frequency (Hz) */

    /**
     * @brief Returns a string representation of the stopwatch stats in one line
     * with maximum precision for double values.
     *
     * @return Formatted string of all stats.
     */
    std::string to_string() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10);
        oss << "{ mean_period=" << mean_period << ", variance_period=" << variance_period
            << ", stddev_period=" << stddev_period << ", average_frequency=" << average_frequency << " }";
        return oss.str();
    }
};

/**
 * @brief A stopwatch which measures how frequently it's been pressed in seconds.
 *
 * @note everything is measured in seconds.
 */
class Stopwatch {
  public:
    Stopwatch() : micro_times(10), macro_times(1000), first_time(true) {}

    /**
     * @brief Register a press of the stopwatch.
     */
    void press();

    /**
     * @brief Returns micro statistics (small window, e.g., last 10 presses)
     */
    StopwatchStats get_micro_stats() const;

    /**
     * @brief Returns macro statistics (large window, e.g., last 1000 presses)
     */
    StopwatchStats get_macro_stats() const;

  private:
    bool first_time;
    std::chrono::time_point<std::chrono::system_clock> previous_time;

    // micro (10 samples)
    CircularVector<double> micro_times;

    // macro (1000 samples)
    CircularVector<double> macro_times;
};

#endif
