#include "raygui-implement.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "ashes/style_ashes.h"
#include "bluish/style_bluish.h"
#include "candy/style_candy.h"
#include "cherry/style_cherry.h"
#include "cyber/style_cyber.h"
#include "dark/style_dark.h"
#include "enefete/style_enefete.h"
#include "jungle/style_jungle.h"
#include "lavanda/style_lavanda.h"
#include "sunny/style_sunny.h"
#include "terminal/style_terminal.h"

void GuiTabBarNoClose(Rectangle bounds, const char **text, int count, int *active)
{
    int tabbar_item_width = (bounds.width - 4*(count - 1))/count;

    //GuiState state = guiState;

    Rectangle tabBounds = { bounds.x, bounds.y, tabbar_item_width, bounds.height };

    if (*active < 0) *active = 0;
    else if (*active > count - 1) *active = count - 1;

    int offsetX = 0;    // Required in case tabs go out of screen
    offsetX = (*active + 2)*tabbar_item_width - GetScreenWidth();
    if (offsetX < 0) offsetX = 0;

    bool toggle = false;    // Required for individual toggles

    // Draw control
    //--------------------------------------------------------------------
    for (int i = 0; i < count; i++)
    {
        tabBounds.x = bounds.x + (tabbar_item_width + 4)*i - offsetX;

        if (tabBounds.x < GetScreenWidth())
        {
            // Draw tabs as toggle controls
            int textAlignment = GuiGetStyle(TOGGLE, TEXT_ALIGNMENT);
            int textPadding = GuiGetStyle(TOGGLE, TEXT_PADDING);
            GuiSetStyle(TOGGLE, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
            GuiSetStyle(TOGGLE, TEXT_PADDING, 8);

            if (i == (*active))
            {
                toggle = true;
                GuiToggle(tabBounds, text[i], &toggle);
            }
            else
            {
                toggle = false;
                GuiToggle(tabBounds, text[i], &toggle);
                if (toggle) *active = i;
            }

            GuiSetStyle(TOGGLE, TEXT_PADDING, textPadding);
            GuiSetStyle(TOGGLE, TEXT_ALIGNMENT, textAlignment);
        }
    }

    // Draw tab-bar bottom line
    GuiDrawRectangle(RAYGUI_CLITERAL(Rectangle){ bounds.x, bounds.y + bounds.height - 1, bounds.width, 1 }, 0, BLANK, GetColor(GuiGetStyle(TOGGLE, BORDER_COLOR_NORMAL)));
    //--------------------------------------------------------------------

}

Color getStyleColor(){
    return GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR));
}

void setFontSize(int size){
    GuiSetStyle(DEFAULT, TEXT_SIZE , size);
}

void setStyle(GUI_STYLE styleId){
    static GUI_STYLE oldStyle = -1;
    if(oldStyle == styleId)
        return;
    oldStyle = styleId;
    switch (styleId) {
        case STYLE_DEFAULT: GuiLoadStyleDefault(); break;// Default style
        case STYLE_ASHES: GuiLoadStyleAshes(); break;
        case STYLE_BLUISH: GuiLoadStyleBluish(); break;
        case STYLE_CANDY: GuiLoadStyleCandy(); break;
        case STYLE_CHERRY: GuiLoadStyleCherry(); break;
        case STYLE_CYBER: GuiLoadStyleCyber(); break;
        case STYLE_DARK: GuiLoadStyleDark(); break;
        case STYLE_ENEFETE: GuiLoadStyleEnefete(); break;
        case STYLE_JUNGLE: GuiLoadStyleJungle(); break;
        case STYLE_LAVANDA: GuiLoadStyleLavanda(); break;
        case STYLE_SUNNY: GuiLoadStyleSunny(); break;
        case STYLE_TERMINAL: GuiLoadStyleTerminal(); break;
        default: break;
    }
}