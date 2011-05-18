#ifndef FI_MAPPER_HPP
#define FI_MAPPER_HPP

#include "mouse.hpp"
#include "key.hpp"

namespace FakeInput
{
    /** Translates MouseButton to the platform's representation of the button. */
    long translateMouseButton(MouseButton button);

    /** Translates KeyType to the platform's representation of the key. */
    unsigned long translateKey(KeyType key);
}

#endif
