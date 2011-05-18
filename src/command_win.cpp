#include "command.hpp"

#include <stdlib.h>
#include <iostream>

namespace FakeInput
{
    void Command::run(const std::string& cmd)
    {
        std::string command = "start " + cmd;

        system(command.c_str());
    }
}
