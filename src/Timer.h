#pragma once

#include <iostream>

using Real = double;

class Timer
{
  // All _time's represent milliseconds
  uint64_t current_time;
  uint64_t last_time;
  uint64_t last_real_time;
  uint64_t delta_time;

  Real delta_seconds;

  uint64_t realTime();

public:
  Timer():current_time{0}{};
  void update();
  void updateBy(uint64_t ticks);

  uint64_t curMicros(){ return current_time; };
  uint64_t deltaMicros(){ return delta_time; };
  Real deltaSecs(){ return delta_seconds; };

  void SyncronizeWith(const Timer& timer);
};
