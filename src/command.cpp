#include "command.h"

#include <stdlib.h>
#include <iostream>

namespace FakeInput
{
    void Command::run(const std::string& cmd)
    {
#ifdef UNIX
        std::string command = cmd + " &";
#elif WIN32
        std::string command = "start " + cmd;
#endif

        system(command.c_str());
    }
}
