#include "Workspace.hpp"
#include "BottomMenu.hpp"
#include "LeftMenu.hpp"
#include "RightMenu.hpp"
#include "Scene.hpp"
#include "TopMenu.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "raygui-implement.h"
#include <cmath>

Rectangle Workspace::rec{};
float Workspace::increment = 4.0f;
bool Workspace::gridVisible = true;

void Workspace::Draw(){
  Vector2 rpos = Scene::getOffset();
  float scale = (Scene::getZoom()*increment*4);
  Vector2 gOffset = { std::fmod(rpos.x,scale),std::fmod(rpos.y,scale) };
  if(gOffset.x > rec.x) gOffset.x -= scale;
  if(gOffset.y > rec.y) gOffset.y -= scale;
  static Vector2 mouseCell{};
  BeginScissorMode(rec.x, rec.y, rec.width, rec.height);
    if(gridVisible){
        raygui::GuiGrid(Rectangle{gOffset.x,gOffset.y,(float)GetScreenWidth()-gOffset.x,(float)GetScreenHeight()-gOffset.y}, nullptr,scale, 4, &mouseCell);
    }
    raygui::GuiCrossair(rpos);

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

Vector2 Workspace::posGtoGrid(Vector2 pos){
  float scale = increment*Scene::getScale();

  Vector2 rpos = Scene::getOffset();
  Vector2 rel = pos - rpos;
  rel.x -= std::fmod(rel.x,scale);
  rel.y -= std::fmod(rel.y,scale);
  return rel + rpos;
}
Vector2 Workspace::posGtoR(Vector2 pos){
  float scale = Scene::getScale();
  Vector2 rpos = Scene::getOffset();
  Vector2 rel = pos - rpos;

  return rel*(1.0f/scale);
}
Rectangle Workspace::recGtoR(Rectangle rec){
  float scale = Scene::getScale();
  Vector2 pos = posGtoR({rec.x,rec.y});
  return {
    pos.x,
    pos.y,
    rec.width/scale,
    rec.height/scale,
  };
}