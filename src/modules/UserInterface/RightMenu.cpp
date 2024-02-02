#include "RightMenu.hpp"
#include "BottomMenu.hpp"
#include "Button.hpp"
#include "GUI.hpp"
#include "Global.hpp"
#include "TopMenu.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "tool.hpp"

static void SelectMenu();
static void CreateMenu();

static Vector2 sDim;
static void (*toolMenu[TOOL::NUM_TOOLS])(){
  SelectMenu,
  SelectMenu,
  SelectMenu,
  SelectMenu,
  CreateMenu,
  SelectMenu,
  SelectMenu,
  SelectMenu,
};

// TODO: Make panel width adjust on runtime
int RightMenu::width = 128;

void RightMenu::Draw() {
  sDim = {(float)GetScreenWidth(), (float)GetScreenHeight()};

  raygui::GuiPanel(Rectangle{sDim.x-width, (float)TopMenu::width, (float)width,sDim.y-TopMenu::width-BottomMenu::width}, nullptr);

  toolMenu[G::curTool]();
}

static void drawSampleGUI(Rectangle rec, GUITYPE type){
  bool locked =raygui::GuiIsLocked();
  GUI *gui = GUI::_from_type(type);
  if(gui==nullptr) return;

  gui->setRectangle(rec);
  bool focused = CheckCollisionPointRec(GetMousePosition(), rec);
  raygui::GuiSetTooltip(type._to_string());
  if(!locked & focused){
    raygui::GuiSetState(raygui::STATE_FOCUSED);
    raygui::_GuiTooltip(rec);
  }

  raygui::GuiLock();
  gui->draw();
  raygui::GuiSetTooltip(nullptr);
  if(!locked) raygui::GuiUnlock();

  if(!locked & focused)
    raygui::GuiSetState(raygui::STATE_NORMAL);

  delete gui;
}

static Rectangle offsetRec(Vector2 off, Rectangle rec){
  return {rec.x+off.x,rec.y+off.y,rec.width,rec.height};
}

static void SelectMenu(){}
static void CreateMenu(){
  static int choosen = -1;

  static float margin = 8;
  static Vector2 scroll = {};
  float width = RightMenu::width;
  Rectangle sRec = { 0 };
  Rectangle bounds = {
    sDim.x-width, (float)TopMenu::width,
    width, sDim.y-BottomMenu::width - TopMenu::width
  };
  static Vector2 itemDim{width - 24, width/2.0f - 8};
  Rectangle content{
    bounds.x, bounds.y + 32,
    bounds.width - 16, (itemDim.y+margin)*GUITYPE::NUM_GUIS
  };

  static Rectangle createPalette[GUITYPE::NUM_GUIS]{};

  raygui::GuiScrollPanel(bounds, "#101#Controls Palette",
      content,
      &scroll, &sRec);

  Vector2 fpos = {content.x + scroll.x + margin ,content.y + scroll.y};
  for(int i = 0; i < GUITYPE::NUM_GUIS; i++){
    createPalette[i] = {fpos.x, fpos.y+(itemDim.y+margin)*i, itemDim.x,itemDim.y};
  }
  BeginScissorMode(sRec.x, sRec.y, sRec.width, sRec.height);
  {
    drawSampleGUI(createPalette[GUITYPE::BUTTON],GUITYPE::BUTTON);
  }
  EndScissorMode();
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) & CheckCollisionPointRec(GetMousePosition(), sRec)) {
    int found = -1;
    for(int i: GUITYPE::_values())
      if(CheckCollisionPointRec(GetMousePosition(), createPalette[i])){
        found = i;
        break;
      }
    if(found != -1){
      Tool::createFlag = true;
      Tool::createChoice = GUITYPE::_from_integral_unchecked(found);
    }
  }
}