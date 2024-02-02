#include "RendererDefault.hpp"
#include "BottomMenu.hpp"
#include "Global.hpp"
#include "LeftMenu.hpp"
#include "MainLoop.hpp"
#include "RightMenu.hpp"
#include "State.hpp"
#include "TopMenu.hpp"
#include "Workspace.hpp"
#include "raygui-implement.h"
#include "raylib.h"

RendererDefault::RendererDefault() {
  Workspace::Resize();
  LeftMenu::Resize();

  raygui::GuiEnableTooltip();
}

void RendererDefault::process() {
  if(IsWindowResized()){
    Workspace::Resize();
    LeftMenu::Resize();
  }
  BeginDrawing();
    ClearBackground(raygui::getStyleColor());

    if(G::state._value != STATE::BASE) raygui::GuiLock();
    Workspace::Draw();

    BottomMenu::Draw();
    RightMenu::Draw();
    LeftMenu::Draw();
    TopMenu::Draw();

    raygui::GuiUnlock();

    if(G::state._value == STATE::BASE){
      void (*tool)() = G::tools[G::curTool];
      if(tool) tool();
      G::lastTool = G::curTool;
    }

    if (G::state._value == STATE::EXITING) {
      int result = raygui::GuiMessageBox(
          Rectangle{GetScreenWidth() / 2.0f - 320 / 2.0f,
                    GetScreenHeight() / 2.0f - 120 / 2.0f, 320, 120},
          "Are you sure?", nullptr, "Yes;No");
      if (result == 1)
        MainLoop::Close();
      if( result != -1) G::state = STATE::BASE;
    }
    DrawFPS(10, 10);
  EndDrawing();
}