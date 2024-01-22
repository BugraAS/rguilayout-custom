#pragma once



#include "raylib.h"
#if defined(__cplusplus)
namespace raygui {
    #include "raygui.h"
#else
    #include "raygui.h"
#endif
#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

enum GUI_STYLE
{
    STYLE_DEFAULT,
    STYLE_ASHES,
    STYLE_BLUISH,
    STYLE_CANDY,
    STYLE_CHERRY,
    STYLE_CYBER,
    STYLE_DARK,
    STYLE_ENEFETE,
    STYLE_JUNGLE,
    STYLE_LAVANDA,
    STYLE_SUNNY,
    STYLE_TERMINAL
};
typedef enum GUI_STYLE GUI_STYLE;

Color getStyleColor();
void setFontSize(int size);
void setStyle(GUI_STYLE styleId);

void GuiTabBarNoClose(Rectangle bounds, const char **text, int count, int *active);

#if defined(__cplusplus)
}}
#endif