#include "TopMenu.hpp"
#include "raygui-implement.h"
#include "raylib.h"

// TODO: Make panel width adjust on runtime
int TopMenu::width = 64;

void TopMenu::Draw() {
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};

  raygui::GuiPanel(Rectangle{0.0f, 0.0f, sDim.x, (float)width}, nullptr);
}