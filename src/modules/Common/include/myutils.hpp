#pragma once

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define ICON_STR(x) "#" STR(x) "#"