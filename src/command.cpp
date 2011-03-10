#include "command.h"

#include <stdlib.h>

namespace wc
{
    void Command::run(const std::string& cmd)
    {
        std::string command = cmd + " &";
        system(command.c_str());
    }
}
