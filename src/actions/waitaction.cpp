#include "waitaction.hpp"

#include "system.hpp"

namespace FakeInput
{
    Wait::Wait(unsigned int milisec):
        milisec_(milisec)
    {
    }

    Action* Wait::clone() const
    {
        return new Wait(milisec_);
    }

    void Wait::send() const
    {
        System::wait(milisec_);
    }
}
