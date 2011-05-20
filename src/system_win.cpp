#include "system.hpp"

#include <stdlib.h>
#include <windows.h>

namespace FakeInput
{
    void System::run(const std::string& cmd)
    {
        std::string command = "start " + cmd;

        system(command.c_str());
    }

    void System::wait(unsigned int milisec)
    {
        Sleep(milisec);
    }
}
