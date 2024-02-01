#include "Cursor.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Workspace.hpp"
#include "raygui-implement.h"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "tool.hpp"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <queue>

std::set<GUI*> Tool::selectGUI{};
GUI* Tool::selectHover = nullptr;

static inline bool CheckContainRec(Rectangle big, Rectangle small){
    return
        (big.x <= small.x) & (big.y <= small.y) &
        (big.x + big.width >= small.x + small.width) &
        (big.y + big.height >= small.y + small.height);
}

static GUI* getHover(Vector2 pos){
    GUI* out = nullptr;
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
            if(CheckCollisionPointRec(pos, rec))
                out = gui.get();
        }
    }
    return out;
}
static void areaSelect(Rectangle area){
    Vector2 offset = -Scene::getOffset();
    float zoom = 1/Scene::getZoom();
    area = {
        (area.x + offset.x)*zoom,
        (area.y + offset.y)*zoom,
        area.width*zoom,
        area.height*zoom,
    };
    std::set<GUI*> &out = Tool::selectGUI;
    out.clear();
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
            if(CheckContainRec(area, rec))
                out.insert(gui.get());
        }
    }
}

void Tool::Select(){
    selectHover = nullptr;

    if(!CheckCollisionPointRec(GetMousePosition(), Workspace::rec))
        return;

    static bool dragging = false;
    static double dragStart = 0.0;
    static Vector2 dragOrig{};

    Vector2 mouse = GetMousePosition();

    if(!dragging & Cursor::IsInputted(CURSOR::HOLD) & (dragStart == 0.0)){
        dragStart = GetTime();
        dragOrig = mouse;
    }
    if(!dragging & (dragStart != 0.0)){
        dragging = (GetTime() - dragStart) > 0.1;
        if(Cursor::IsInputted(CURSOR::RELEASE))
            dragStart = 0.0;
    }

    selectHover = getHover(Workspace::posGtoR(mouse));

    //select single
    if(!dragging){
        if(Cursor::IsInputted(CURSOR::CLICK)){
            selectGUI.clear();
            if(selectHover)
                selectGUI.insert(selectHover);
        }
        return;
    }
    //select multiple
    Vector2 pos = {
        std::min(dragOrig.x,mouse.x),
        std::min(dragOrig.y,mouse.y)
    };
    Rectangle area{pos.x,pos.y, fabs(mouse.x-dragOrig.x),fabs(mouse.y-dragOrig.y)};
    raygui::GuiSelection(area, 5.0f);
    areaSelect(area);
    if(selectGUI.empty()) selectHover = nullptr;
    dragging = Cursor::IsInputted(CURSOR::HOLD);
    if(!dragging) dragStart = 0.0;
}