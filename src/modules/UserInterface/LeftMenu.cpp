#include "LeftMenu.hpp"
#include "BottomMenu.hpp"
#include "TopMenu.hpp"
#include "raygui-implement.h"
#include "raylib.h"

// TODO: Make panel width adjust on runtime
int LeftMenu::width = 128;

void LeftMenu::Draw() {
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};

  raygui::GuiPanel(Rectangle{0.0f, (float)TopMenu::width, (float)width,sDim.y-TopMenu::width-BottomMenu::width}, nullptr);
}