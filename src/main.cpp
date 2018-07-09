#include <iostream>
#include <chrono>
#include <unistd.h>

#include "Level/Level.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char * argv[])
{
    MainLevel level(string("some_file.format"));

    while(1) // TODO Only while gamestate is valid
    {
      level.update();
    }

    return 0;
}
