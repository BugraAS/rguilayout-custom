#include "RendererDefault.hpp"
#include "MainLoop.hpp"
#include "raygui-implement.h"
#include "raylib.h"

RendererDefault::RendererDefault() {}

void RendererDefault::process() {
  static bool confirmCloseWindow = false;
  confirmCloseWindow |= WindowShouldClose();
  BeginDrawing();
    ClearBackground(RAYWHITE);
    if (confirmCloseWindow) {
      int result = raygui::GuiMessageBox(
          Rectangle{GetScreenWidth() / 2.0f - 320 / 2.0f,
                    GetScreenHeight() / 2.0f - 120 / 2.0f, 320, 120},
          "Are you sure?", nullptr, "Yes;No");
      if (result == 1)
        MainLoop::Close();
      confirmCloseWindow = result == -1;
    }
    DrawFPS(10, 10);
  EndDrawing();
}