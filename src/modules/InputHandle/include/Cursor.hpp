#pragma once

#include "enum.h"

BETTER_ENUM(CURSOR, int,
    CLICK,
    RCLICK,
    HOLD,
    RELEASE,
    SCROLL,
    NUM_INPUTS
)

namespace Cursor
{
    bool IsInputted(CURSOR::_enumerated input);
}