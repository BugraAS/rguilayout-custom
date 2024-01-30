#include "Button.hpp"
#include "Cursor.hpp"
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
    Node* root = Scene::getRoot();
    if(held){
        Vector2 delta = GetMouseDelta();
        root->pos = delta + root->pos;
    }
    if(Cursor::IsInputted(CURSOR::SCROLL))
        root->scale += GetMouseWheelMove()*0.1;

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

    Vector2 pos = Workspace::posGtoGrid(GetMousePosition());

    Rectangle sample = Scene::getScaledRec({
        pos.x,
        pos.y,
        (RightMenu::width - 24.0f),
        RightMenu::width/2.0f -8,
    });

    BeginScissorMode(Workspace::rec.x, Workspace::rec.y, Workspace::rec.width, Workspace::rec.height);
    drawSampleGUI(sample, createChoice);
    EndScissorMode();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        //TODO: ADD multiplace keybind
        createFlag = false;

        GUI* gui = GUI::_from_type(createChoice);
        gui->setRectangle(Workspace::recGtoR(sample));
        Scene::addGui(gui);
    }
}