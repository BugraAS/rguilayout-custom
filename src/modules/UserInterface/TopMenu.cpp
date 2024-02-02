#include "TopMenu.hpp"
#include "Global.hpp"
#include "State.hpp"
#include "Workspace.hpp"
#include "myutils.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "tool.hpp"

// TODO: Make panel width adjust on runtime
int TopMenu::width = 64;

void TopMenu::Draw() {
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};
  float bDim{width*(1/3.0f)}; // button size
  float unit{width*(1/12.0f)}; // Margin from edge
  bool locked = raygui::GuiIsLocked();

  //background GuiPanel
  raygui::GuiPanel(Rectangle{0.0f, 0.0f, sDim.x, (float)width}, nullptr);

  // Separator line
  raygui::GuiLine({unit, width*0.5f, sDim.x - 2*unit,0.0f}, nullptr);

  // Buttons for tools
  static int curTool = G::curTool;
  const char* tools = // turns out its impossible to convert enums into integral values in compile time.
        ICON_STR(21) ";Select"
    ";" ICON_STR(68) ";Move"
    ";" ICON_STR(53) ";Scale"
    ";" ICON_STR(19) ";Pan"
    ";" ICON_STR(79) ";Create element"
    ";" ICON_STR(144) ";Interact"
    ";" ICON_STR(174) ";Group"
    ";" ICON_STR(175) ";Ungroup"
    ;
  raygui::GuiToggleGroupTooltip(
    Rectangle{ 2*bDim + unit, unit+width/2.0f, bDim, bDim},
    tools, &curTool
  );
  if(curTool != G::curTool) G::curTool =TOOL::_from_integral(curTool);

  //Delete button
  if( raygui::GuiButtonTooltip({(TOOL::NUM_TOOLS + 4)*bDim + unit, unit + width/2.0f,bDim,bDim}, ICON_STR(143) ";Delete"))
    Tool::Delete();

  //Increment control
  int increment = Workspace::increment;
  static bool writingInc = false;
  if(writingInc) raygui::GuiUnlock();
  bool result = raygui::GuiPMSpinner({sDim.x - unit - bDim*4, unit + width/2.0f, bDim*4, bDim}, nullptr, &increment, 1, 64, writingInc);
  if(result){
    writingInc^=true;
    if(writingInc)
      G::state._value = STATE::TYPING;
    else
      G::state._value = STATE::BASE;
  }
  Workspace::increment = increment;
  if(locked) raygui::GuiLock();
}