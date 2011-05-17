#include "key_base.h"

#include <stdexcept>
#include <iostream>

namespace FakeInput
{
    Key_base::Key_base()
    {
        code_ = 0;
        name_ = "<no key>";
    }

    unsigned int Key_base::code() const
    {
        return code_;
    }
    
    const std::string& Key_base::name() const
    {
        return name_;
    }
}
