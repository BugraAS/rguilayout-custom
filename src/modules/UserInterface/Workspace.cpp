#include "Workspace.hpp"
#include "BottomMenu.hpp"
#include "LeftMenu.hpp"
#include "RightMenu.hpp"
#include "Scene.hpp"
#include "TopMenu.hpp"
#include "raylib.h"
#include "raygui-implement.h"
#include <cmath>

Rectangle Workspace::rec{};
float Workspace::increment = 4.0f;
bool Workspace::gridVisible = true;

void Workspace::Draw(){
  Vector2 rpos = Scene::getRoot()->pos;
  Vector2 gOffset = { std::fmod(rpos.x,increment*4),std::fmod(rpos.y,increment*4) };
  if(gOffset.x > rec.x) gOffset.x -= increment*4;
  if(gOffset.y > rec.y) gOffset.y -= increment*4;
  static Vector2 mouseCell{};
  BeginScissorMode(rec.x, rec.y, rec.width, rec.height);
    if(gridVisible){
        raygui::GuiGrid(Rectangle{gOffset.x,gOffset.y,(float)GetScreenWidth()-gOffset.x,(float)GetScreenHeight()-gOffset.y}, nullptr,increment*4, 4, &mouseCell);
    }
    raygui::GuiCrossair(Scene::getRoot()->pos);

    Scene::getSingleton()->process();
  EndScissorMode();
}

void Workspace::Resize(){
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};
  rec = {
    (float)LeftMenu::width,
    (float)TopMenu::width,
    sDim.x - LeftMenu::width - RightMenu::width,
    sDim.y - TopMenu::width - BottomMenu::width
  };
}