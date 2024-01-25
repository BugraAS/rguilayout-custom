#include "Workspace.hpp"
#include "BottomMenu.hpp"
#include "LeftMenu.hpp"
#include "RightMenu.hpp"
#include "Scene.hpp"
#include "TopMenu.hpp"
#include "raylib.h"
#include "raygui-implement.h"
#include <cmath>

int Workspace::size[2] = {};
int Workspace::pos[2] = {};
float Workspace::increment = 4.0f;
bool Workspace::gridVisible = true;

void Workspace::Draw(){
  Vector2 rpos = Scene::getRoot()->pos;
  Vector2 gOffset = { std::fmod(rpos.x,increment*4),std::fmod(rpos.y,increment*4) };
  if(gOffset.x > pos[0]) gOffset.x -= increment*4;
  if(gOffset.y > pos[1]) gOffset.y -= increment*4;
  static Vector2 mouseCell{};
  BeginScissorMode(pos[0], pos[1], size[0], size[1]);
    if(gridVisible){
        raygui::GuiGrid(Rectangle{gOffset.x,gOffset.y,(float)GetScreenWidth()-gOffset.x,(float)GetScreenHeight()-gOffset.y}, nullptr,increment*4, 4, &mouseCell);
    }
    raygui::GuiCrossair(Scene::getRoot()->pos);
  EndScissorMode();
}

void Workspace::Resize(){
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};
  size[0] = (int)(sDim.x - LeftMenu::width - RightMenu::width);
  size[1] = (int)(sDim.y - TopMenu::width - BottomMenu::width);

  pos[0] = LeftMenu::width;
  pos[1] = TopMenu::width;
}