#pragma once

#include "raylib.h"
#if defined(__cplusplus)
#include "enum.h"
namespace raygui {
#endif
#include "raygui.h"

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
    STYLE_TERMINAL,
    NUM_STYLES,
};
typedef enum GUI_STYLE GUI_STYLE;

Color getStyleColor();
void setFontSize(int size);
void setStyle(GUI_STYLE styleId);

void GuiCrossair(Vector2 pos);
void GuiTabBarNoClose(Rectangle bounds, const char **text, int count, int *active);
int GuiPMSpinner(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode);
// Text should be in the form "label1;tooltop1;label2;tooltip2;.."
int GuiToggleGroupTooltip(Rectangle bounds, const char *text, int *active);
void _GuiTooltip(Rectangle controlRec);
#if defined(__cplusplus)
}}
#endif