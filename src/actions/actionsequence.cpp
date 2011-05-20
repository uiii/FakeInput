#include "actionsequence.hpp"

#include <iostream>

namespace FakeInput
{
    ActionSequence::ActionSequence()
    {
    }

    ActionSequence::ActionSequence(const ActionSequence& anotherSequence)
    {
        ActionList::const_iterator it;
        for(it = anotherSequence.actions_.begin(); it != anotherSequence.actions_.end(); ++it)
        {
            actions_.push_back((*it)->clone());
        }
    }

    ActionSequence::~ActionSequence()
    {
        ActionList::iterator it;
        for(it = actions_.begin(); it != actions_.end(); ++it)
        {
            delete (*it);
        }
    }

    Action* ActionSequence::clone() const
    {
        return new ActionSequence(*this);
    }

    ActionSequence& ActionSequence::join(ActionSequence& anotherSequence)
    {
        actions_.push_back(anotherSequence.clone());
        return *this;
    }

    ActionSequence& ActionSequence::press(Key key)
    {
        actions_.push_back(new KeyboardPress(key));
        return *this;
    }

    ActionSequence& ActionSequence::press(KeyType type)
    {
        actions_.push_back(new KeyboardPress(type));
        return *this;
    }

    ActionSequence& ActionSequence::press(MouseButton button)
    {
        actions_.push_back(new MousePress(button));
        return *this;
    }

    ActionSequence& ActionSequence::release(Key key)
    {
        actions_.push_back(new KeyboardRelease(key));
        return *this;
    }

    ActionSequence& ActionSequence::release(KeyType type)
    {
        actions_.push_back(new KeyboardRelease(type));
        return *this;
    }

    ActionSequence& ActionSequence::release(MouseButton button)
    {
        actions_.push_back(new MouseRelease(button));
        return *this;
    }

    ActionSequence& ActionSequence::moveMouse(int dx, int dy)
    {
        actions_.push_back(new MouseRelativeMotion(dx, dy));
        return *this;
    }

    ActionSequence& ActionSequence::moveMouseTo(int x, int y)
    {
        actions_.push_back(new MouseAbsoluteMotion(x, y));
        return *this;
    }

    ActionSequence& ActionSequence::wheelUp()
    {
        actions_.push_back(new MouseWheelUp());
        return *this;
    }

    ActionSequence& ActionSequence::wheelDown()
    {
        actions_.push_back(new MouseWheelDown());
        return *this;
    }

    ActionSequence& ActionSequence::runCommand(const std::string& cmd)
    {
        actions_.push_back(new CommandRun(cmd));
        return *this;
    }

    ActionSequence& ActionSequence::wait(unsigned int milisec)
    {
        actions_.push_back(new Wait(milisec));
        return *this;
    }

    void ActionSequence::send() const
    {
        ActionList::const_iterator it;
        for(it = actions_.begin(); it != actions_.end(); ++it)
        {
            (*it)->send();
        }
    }
}
