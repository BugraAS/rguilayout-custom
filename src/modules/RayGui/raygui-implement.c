#include "raygui-implement.h"
#include "raylib.h"

#define RAYGUI_GRID_ALPHA                 0.1f
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

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

void _GuiTooltip(Rectangle controlRec){
    GuiTooltip(controlRec);
}

void GuiCrossair(Vector2 pos){
    Color color = GetColor(GuiGetStyle(DEFAULT, BORDER_COLOR_FOCUSED));
    Vector2 sDim = {GetScreenWidth(), GetScreenHeight()};
    GuiDrawRectangle(RAYGUI_CLITERAL(Rectangle){ 0, pos.y, sDim.x, 1 }, 0, BLANK, color);
    GuiDrawRectangle(RAYGUI_CLITERAL(Rectangle){ pos.x, 0, 1, sDim.y }, 0, BLANK, color);
}

// Toggle Group control, returns toggled button codepointIndex
// Text should be in the form "label1;tooltop1;label2;tooltip2;.."
int GuiToggleGroupTooltip(Rectangle bounds, const char *text, int *active)
{
    #if !defined(RAYGUI_TOGGLEGROUP_MAX_ITEMS)
        #define RAYGUI_TOGGLEGROUP_MAX_ITEMS    32
    #endif

    int result = 0;
    float initBoundsX = bounds.x;

    int temp = 0;
    if (active == NULL) active = &temp;

    bool toggle = false;    // Required for individual toggles

    // Get substrings items from text (items pointers)
    int rows[RAYGUI_TOGGLEGROUP_MAX_ITEMS] = { 0 };
    int itemCount = 0;
    const char **items = GuiTextSplit(text, ';', &itemCount, rows);

    int prevRow = rows[0];

    for (int i = 0; i < itemCount/2; i++)
    {
        if (prevRow != rows[i])
        {
            bounds.x = initBoundsX;
            bounds.y += (bounds.height + GuiGetStyle(TOGGLE, GROUP_PADDING));
            prevRow = rows[i];
        }

        GuiSetTooltip(items[2*i+1]);
        if (i == (*active))
        {
            toggle = true;
            GuiToggle(bounds, items[2*i], &toggle);
        }
        else
        {
            toggle = false;
            GuiToggle(bounds, items[2*i], &toggle);
            if (toggle) *active = i;
        }
        GuiSetTooltip(NULL);

        bounds.x += (bounds.width + GuiGetStyle(TOGGLE, GROUP_PADDING));
    }

    return result;
}

int GuiPMSpinner(Rectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode)
{
    int result = 1;
    GuiState state = guiState;

    int tempValue = *value;

    Rectangle spinner = { bounds.x + GuiGetStyle(SPINNER, SPIN_BUTTON_WIDTH) + GuiGetStyle(SPINNER, SPIN_BUTTON_SPACING), bounds.y,
                          bounds.width - 2*(GuiGetStyle(SPINNER, SPIN_BUTTON_WIDTH) + GuiGetStyle(SPINNER, SPIN_BUTTON_SPACING)), bounds.height };
    Rectangle leftButtonBound = { (float)bounds.x, (float)bounds.y, (float)GuiGetStyle(SPINNER, SPIN_BUTTON_WIDTH), (float)bounds.height };
    Rectangle rightButtonBound = { (float)bounds.x + bounds.width - GuiGetStyle(SPINNER, SPIN_BUTTON_WIDTH), (float)bounds.y, (float)GuiGetStyle(SPINNER, SPIN_BUTTON_WIDTH), (float)bounds.height };

    Rectangle textBounds = { 0 };
    if (text != NULL)
    {
        textBounds.width = (float)GetTextWidth(text) + 2;
        textBounds.height = (float)GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width + GuiGetStyle(SPINNER, TEXT_PADDING);
        textBounds.y = bounds.y + bounds.height/2 - GuiGetStyle(DEFAULT, TEXT_SIZE)/2;
        if (GuiGetStyle(SPINNER, TEXT_ALIGNMENT) == TEXT_ALIGN_LEFT) textBounds.x = bounds.x - textBounds.width - GuiGetStyle(SPINNER, TEXT_PADDING);
    }

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && !guiLocked && !guiSliderDragging)
    {
        Vector2 mousePoint = GetMousePosition();

        // Check spinner state
        if (CheckCollisionPointRec(mousePoint, bounds))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) state = STATE_PRESSED;
            else state = STATE_FOCUSED;
        }
    }

    if (GuiButton(leftButtonBound, "-")) tempValue--;
    if (GuiButton(rightButtonBound, "+")) tempValue++;

    if (!editMode)
    {
        if (tempValue < minValue) tempValue = minValue;
        if (tempValue > maxValue) tempValue = maxValue;
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    result = GuiValueBox(spinner, NULL, &tempValue, minValue, maxValue, editMode);

    // Draw value selector custom buttons
    // NOTE: BORDER_WIDTH and TEXT_ALIGNMENT forced values
    int tempBorderWidth = GuiGetStyle(BUTTON, BORDER_WIDTH);
    int tempTextAlign = GuiGetStyle(BUTTON, TEXT_ALIGNMENT);
    GuiSetStyle(BUTTON, BORDER_WIDTH, GuiGetStyle(SPINNER, BORDER_WIDTH));
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, tempTextAlign);
    GuiSetStyle(BUTTON, BORDER_WIDTH, tempBorderWidth);

    // Draw text label if provided
    GuiDrawText(text, textBounds, (GuiGetStyle(SPINNER, TEXT_ALIGNMENT) == TEXT_ALIGN_RIGHT)? TEXT_ALIGN_LEFT : TEXT_ALIGN_RIGHT, GetColor(GuiGetStyle(LABEL, TEXT + (state*3))));
    //--------------------------------------------------------------------

    *value = tempValue;
    return result;
}

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

float getFontSize(){
    return GuiGetStyle(DEFAULT, TEXT_SIZE);
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