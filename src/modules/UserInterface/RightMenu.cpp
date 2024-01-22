#include "RightMenu.hpp"
#include "BottomMenu.hpp"
#include "TopMenu.hpp"
#include "raygui-implement.h"
#include "raylib.h"

// TODO: Make panel width adjust on runtime
int RightMenu::width = 128;

void RightMenu::Draw() {
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};

  raygui::GuiPanel(Rectangle{sDim.x-width, (float)TopMenu::width, (float)width,sDim.y-TopMenu::width-BottomMenu::width}, nullptr);
}