#ifndef FI_MAPPER_H
#define FI_MAPPER_H

#include "mouse.h"
#include "key.h"

namespace FakeInput
{
    /** Translates MouseButton to the platform's representation of the button. */
    long translateMouseButton(MouseButton button);

    /** Translates KeyType to the platform's representation of the key. */
    unsigned long translateKey(KeyType key);
}

#endif
