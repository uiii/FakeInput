#include "system.hpp"

#include <stdlib.h>
#include <time.h>

namespace FakeInput
{
    void System::run(const std::string& cmd)
    {
        std::string command = cmd + " &";

        system(command.c_str());
    }

    void System::wait(unsigned int milisec)
    {
        timespec tm;
        tm.tv_sec = milisec / 1000;
        tm.tv_nsec = (milisec % 1000) * 1000000;

        nanosleep(&tm, NULL);
    }
}
