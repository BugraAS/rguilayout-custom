#include "TopMenu.hpp"
#include "Global.hpp"
#include "myutils.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "tool.hpp"

// TODO: Make panel width adjust on runtime
int TopMenu::width = 64;

void TopMenu::Draw() {
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};
  float bDim{width*(1/3.0f)}; // button size
  float margin{width*(1/12.0f)}; // Margin from edge

  //background GuiPanel
  raygui::GuiPanel(Rectangle{0.0f, 0.0f, sDim.x, (float)width}, nullptr);

  // Separator line
  raygui::GuiLine({margin, width*0.5f, sDim.x - 2*margin,0.0f}, nullptr);

  // Buttons for tools
  static int curTool = G::curTool;
  const char* buttons = // turns out its impossible to convert enums into integral values in compile time.
    ICON_STR(21) ";Select;"
    ICON_STR(19) ";Pan;"
    ICON_STR(79) ";Create element;"
    ICON_STR(144) ";Interact;"
    ICON_STR(68) ";Move;"
    ICON_STR(53) ";Scale"
    ;
  raygui::GuiToggleGroupTooltip(
    Rectangle{ 2*bDim + margin, margin+width/2.0f, bDim, bDim},
    buttons, &curTool
  );
  if(curTool != G::curTool) G::curTool =TOOL::_from_integral(curTool);
}