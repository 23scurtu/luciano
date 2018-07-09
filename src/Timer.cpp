#include "Timer.h"
#include <chrono>

uint64_t Timer::realTime()
{
  return std::chrono::duration_cast<std::chrono::microseconds>
    (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

void Timer::update()
{
  uint64_t current_real_time = realTime();
  delta_time = current_real_time - last_real_time;
  last_real_time = current_real_time;
  updateBy(delta_time);
}

void Timer::updateBy(uint64_t ticks)
{
  last_time = current_time;
  current_time += ticks;

  delta_seconds = static_cast<Real>(1.0/1000000.0)*delta_time;
}

void Timer::SyncronizeWith(const Timer& timer)
{
  last_real_time = timer.last_real_time;
  current_time = timer.current_time;
}
