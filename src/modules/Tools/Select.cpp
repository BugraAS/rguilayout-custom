#include "Cursor.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Workspace.hpp"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "tool.hpp"
#include <math.h>
#include <queue>

GUI* Tool::selectGUI = nullptr;
GUI* Tool::selectHover = nullptr;

void Tool::Select(){
    selectHover = nullptr;

    if(selectGUI)
        raygui::GuiSelection(selectGUI->getGRectangle(), 5.0f);

    if(!CheckCollisionPointRec(GetMousePosition(), Workspace::rec))
        return;

    Vector2 mouse = GetMousePosition();
    std::queue<Node*> queue{};
    Node* root = Scene::getRoot();
    queue.push(root);
    for(Node* n=queue.front(); !queue.empty(); n=queue.front()){
        queue.pop();
        auto& childs = n->getChildren();
        for(auto& child: childs)
            queue.push(child.get());
        auto& guis = n->getGuis();
        for(auto& gui: guis){
            Rectangle rec{ gui->getGRectangle()};
            if(CheckCollisionPointRec(mouse, rec))
                selectHover = gui.get();
        }
    }

    if(Cursor::IsInputted(CURSOR::CLICK))
        selectGUI = selectHover;
}