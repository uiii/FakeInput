#include "commandaction.hpp"

#include "system.hpp"

namespace FakeInput
{
    CommandRun::CommandRun(const std::string& cmd):
        cmd_(cmd)
    {
    }

    Action* CommandRun::clone() const
    {
        return new CommandRun(cmd_);
    }

    void CommandRun::send() const
    {
        System::run(cmd_);
    }
}
