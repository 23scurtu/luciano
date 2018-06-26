#include <iostream>
#include <chrono>
#include <unistd.h>

#include "Level/Level.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char * argv[])
{
    high_resolution_clock::time_point startloop = high_resolution_clock::now();
    high_resolution_clock::time_point endloop;

    MainLevel level(string("some_file.format"));

    while(1) // TODO Only while gamestate is valid
    {
      //Calculate basic delta time
      endloop = high_resolution_clock::now();
      duration<double> dt = duration_cast<duration<double>>(endloop - startloop);
      startloop = high_resolution_clock::now();

      usleep(1000);
      level.update(dt.count());
      printf("%f\n", dt.count());
    }

    return 0;
}
