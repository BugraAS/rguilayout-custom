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
}

void RendererDefault::process() {
  BeginDrawing();
    ClearBackground(raygui::getStyleColor());

    if(G::state != STATE::BASE) raygui::GuiLock();
    Workspace::Draw();

    TopMenu::Draw();
    BottomMenu::Draw();
    RightMenu::Draw();
    LeftMenu::Draw();
    if(G::state != STATE::BASE) raygui::GuiUnlock();

    if (G::state == STATE::EXITING) {
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