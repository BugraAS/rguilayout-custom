#include "Workspace.hpp"
#include "BottomMenu.hpp"
#include "LeftMenu.hpp"
#include "RightMenu.hpp"
#include "TopMenu.hpp"
#include "raylib.h"
#include "raygui-implement.h"

int Workspace::size[2] = {};
int Workspace::pos[2] = {};
float Workspace::increment = 4.0f;
bool Workspace::gridVisible = true;

void Workspace::Draw(){
  static Vector2 mouseCell{};
  BeginScissorMode(pos[0], pos[1], size[0], size[1]);
    if(gridVisible){
        raygui::GuiGrid(Rectangle{0,0,(float)GetScreenWidth(),(float)GetScreenHeight()}, nullptr,increment*4, 4, &mouseCell);
    }
  EndScissorMode();
}

void Workspace::Resize(){
  Vector2 sDim{(float)GetScreenWidth(), (float)GetScreenHeight()};
  size[0] = (int)(sDim.x - LeftMenu::width - RightMenu::width);
  size[1] = (int)(sDim.y - TopMenu::width - BottomMenu::width);

  pos[0] = LeftMenu::width;
  pos[1] = TopMenu::width;
}