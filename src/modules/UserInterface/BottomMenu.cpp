#include "BottomMenu.hpp"
#include "Workspace.hpp"
#include "raygui-implement.h"
#include "raylib.h"

// TODO: Make panel width adjust on runtime
int BottomMenu::width = 32;

void BottomMenu::Draw() {
  static int curStyle = raygui::STYLE_DEFAULT;
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};
  const char* styleNames = "Default;Ashes;Bluish;Candy;Cherry;Cyber;Dark;Enefete;Jungle;Lavanda;Sunny;Terminal";

  raygui::GuiPanel(Rectangle{0.0, sDim.y - width, sDim.x, (float)width}, nullptr);
  raygui::setStyle(raygui::GUI_STYLE(curStyle));
  raygui::GuiComboBox(Rectangle{sDim.x - width*(1/6.0f)-100,sDim.y - width*(5/6.0f),100.0f,width*(2/3.0f)}, styleNames, &curStyle);
  raygui::GuiLabel(Rectangle{sDim.x - width*(1/6.0f)-220,sDim.y - width*(5/6.0f),100.0f,width*(2/3.0f)}, TextFormat("Increment: %5.2f",Workspace::increment));
}