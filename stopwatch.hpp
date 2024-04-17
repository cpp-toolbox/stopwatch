#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>
/**
 * \brief A stopwatch which measures how frequently it's been pressed in seconds
 * to be used to measure at what frequency a specific line of code is run at.
 */
class Stopwatch {
  public:
    void press();
    double average_frequency = 0.0;

  private:
    double compute_average_period();
    int num_times_to_average_over = 10;
    double times[10] = {0};
    bool first_time = true;
    int curr_idx = 0;
    std::chrono::time_point<std::chrono::system_clock> previous_time;
};

#endif
