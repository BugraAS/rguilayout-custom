#include "BottomMenu.hpp"
#include "Scene.hpp"
#include "Workspace.hpp"
#include "raygui-implement.h"
#include "raylib.h"

// TODO: Make panel width adjust on runtime
int BottomMenu::width = 32;
std::string BottomMenu::message{};

static const float timeout = 2.0f;
static float timer = 0.0f;

void BottomMenu::Draw() {
  float unit = width*(1/6.0f);
  static int curStyle = raygui::STYLE_DEFAULT;
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};
  const char* styleNames = "Default;Ashes;Bluish;Candy;Cherry;Cyber;Dark;Enefete;Jungle;Lavanda;Sunny;Terminal";

  raygui::GuiPanel(Rectangle{0.0, sDim.y - width, sDim.x, (float)width}, nullptr);
  raygui::setStyle(raygui::GUI_STYLE(curStyle));
  raygui::GuiComboBox(Rectangle{sDim.x - unit-100,sDim.y - unit*5.0f,100.0f,unit*4.0f}, styleNames, &curStyle);
  raygui::GuiLabel(Rectangle{sDim.x - unit-220,sDim.y - unit*5.0f,100.0f,unit*4.0f}, TextFormat("Increment: %5.2f",Workspace::increment));
  raygui::GuiLabel(Rectangle{sDim.x - unit-300,sDim.y - unit*5.0f,100.0f,unit*4.0f}, TextFormat("Zoom: %4.1f%%",Scene::getScale()*100.0f));

  const char *text = TextFormat("%24s -- ",message.c_str());
  int textLen = MeasureText(text,(int)raygui::getFontSize());
  raygui::GuiLabel(Rectangle{unit,sDim.y - unit*5.0f,textLen+10.f,unit*4.0f}, text);
  if(timer > 0.0f){
    timer -= GetFrameTime();
    if(timer <= 0.0f)
      message.clear();
  }
}

void BottomMenu::setMessage(std::string message){
  BottomMenu::message = message;
  timer = timeout;
}