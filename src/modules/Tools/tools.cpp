#include "Button.hpp"
#include "GUI.hpp"
#include "Global.hpp"
#include "Node.hpp"
#include "RightMenu.hpp"
#include "Scene.hpp"
#include "Workspace.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "tool.hpp"
#include "raygui-implement.h"
#include <cmath>

void Tool::Pan(){
    bool held = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    if(held){
        Vector2 delta = GetMouseDelta();
        Node* root = Scene::getRoot();
        root->pos = delta + root->pos;
    }
}

static void drawSampleGUI(Rectangle rec, GUITYPE type){
  bool locked =raygui::GuiIsLocked();
  GUI *gui = GUI::_from_type(type);
  if((gui==nullptr) | locked) return;

  gui->setRectangle(rec);

  raygui::GuiLock();
  raygui::GuiSetAlpha(0.6f);
  gui->draw();
  raygui::GuiSetAlpha(1.0f);
  raygui::GuiUnlock();

  delete gui;
}

GUITYPE Tool::createChoice = GUITYPE::_from_integral(0);
bool Tool::createFlag = false;

void Tool::Create(){
    if(!createFlag) return;
    if(!CheckCollisionPointRec(GetMousePosition(), Workspace::rec)) return;

    Vector2 rpos = Scene::getRoot()->pos;
    Vector2 pos = GetMousePosition();
    float increment = Workspace::increment;
    Vector2 rel = pos - rpos;
    rel.x -= std::fmod(rel.x,increment);
    rel.y -= std::fmod(rel.y,increment);
    pos = rel + rpos;

    Rectangle sample = {
        pos.x,
        pos.y,
        RightMenu::width - 24.0f,
        RightMenu::width/2.0f -8,
    };
    BeginScissorMode(Workspace::rec.x, Workspace::rec.y, Workspace::rec.width, Workspace::rec.height);
    drawSampleGUI(sample, createChoice);
    EndScissorMode();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        //TODO: ADD multiplace keybind
        createFlag = false;

        GUI* gui = GUI::_from_type(createChoice);
        gui->setPos(rel);
        gui->setDim({sample.width,sample.height});
        Scene::addGui(gui);
    }
}