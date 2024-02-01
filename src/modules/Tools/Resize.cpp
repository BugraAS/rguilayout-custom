#include "Cursor.hpp"
#include "Node.hpp"
#include "Scene.hpp"
#include "Workspace.hpp"
#include "enum.h"
#include "raygui-implement.h"
#include "raylib.h"
#include "raylib-wrap.hpp"
#include "raymath.h"
#include "tool.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <math.h>
#include <queue>

Rectangle Tool::resizeArea{};

static Vector2 inverseTransform(Vector2 in, Vector3 trans){
    return {
        (in.x-trans.x)/trans.z,
        (in.y-trans.y)/trans.z
    };
}

static inline Rectangle RecFromAABB(Vector2 tleft, Vector2 bright){
    return{
        tleft.x,
        tleft.y,
        bright.x - tleft.x,
        bright.y - tleft.y,
    };
}

static inline Vector2 translatePos(Vector2 in, Rectangle old, Rectangle cur){
    return {
        cur.x + cur.width*(in.x - old.x)/old.width,
        cur.y + cur.height*(in.y - old.y)/old.height,
    };
}

static Rectangle translateRec(Rectangle in, Rectangle old, Rectangle cur){
    Vector2 tleft{in.x,in.y};
    tleft = translatePos(tleft, old, cur);
    Vector2 bright{in.x+in.width,in.y+in.height};
    bright = translatePos(bright, old, cur);
    return RecFromAABB(tleft, bright);
}

static void createBoundingArea(){
    const float inf = std::numeric_limits<float>::infinity();
    Rectangle aabb{
        inf,
        inf,
        -inf,
        -inf
    };
    for(GUI* gui: Tool::selectGUI){
        Rectangle grec = gui->getGRectangle();
        aabb = {
            std::min(grec.x,aabb.x),
            std::min(grec.y,aabb.y),
            std::max(grec.x + grec.width,aabb.width),
            std::max(grec.y + grec.height,aabb.height),
        };
    }
    Tool::resizeArea = RecFromAABB(
        {
            aabb.x, aabb.y
        }, {
            aabb.width, aabb.height
        });
}

namespace {
    BETTER_ENUM(DIR, int,
        DOWN,
        UP,
        RIGHT,
        LEFT,
        BOTTOMLEFT,
        TOPRIGHT,
        BOTTOMRIGHT,
        TOPLEFT
    )
};
static float distToLine(Vector2 line, Vector2 pos){
    return Vector2LengthSqr(pos - Vector2DotProduct(line, pos)*line);
}
static bool alignedWLine(Vector2 line, Vector2 pos){
    return Vector2DotProduct(line, pos) >= 0.0f;
}

static DIR findDir(Vector2 pos){
    Rectangle area{Tool::resizeArea};
    Vector2 center{area.x + area.width/2,area.y + area.height/2};
    Vector2 diag{1, area.height/area.width};
    diag = Vector2Normalize(diag);

    pos = pos - center;
    DIR res = DIR::DOWN;
    float dist = distToLine({0,1},pos);
    if(!alignedWLine({0,1}, pos)) res._value++;

    DIR tres = DIR::RIGHT;
    float tdist = distToLine({1,0},pos);
    if(!alignedWLine({1,0}, pos)) tres._value++;
    if(tdist < dist){
        dist = tdist;
        res = tres;
    }

    tres = DIR::BOTTOMRIGHT;
    tdist = distToLine(diag,pos);
    if(!alignedWLine(diag, pos)) tres._value++;
    if(tdist < dist){
        dist = tdist;
        res = tres;
    }
    diag.x = -diag.x;

    tres = DIR::BOTTOMLEFT;
    tdist = distToLine(diag,pos);
    if(!alignedWLine(diag, pos)) tres._value++;
    if(tdist < dist){
        dist = tdist;
        res = tres;
    }
    return res;
}

void Tool::Resize(){
    //TODO: add multiple resize modes. Group, Single free, single snap

    static bool dragging = false;
    static DIR dir = DIR::DOWN;
    static bool createBound = true;

    if(selectGUI.empty()){
        dragging = false;
        createBound=true;
        return;
    }
    if(createBound){
        createBoundingArea();
        createBound = false;
    }
    static Vector2 pin{};
    static Vector2 olddelta{};

    Vector2 mouse = Workspace::posGtoR(GetMousePosition());
    bool hold = Cursor::IsInputted(CURSOR::HOLD);
    if(hold & !dragging){
        pin = mouse;
        dragging = true;
        dir = findDir(mouse);
        createBoundingArea();
    }
    Vector2 offset = Scene::getOffset();
    float zoom = Scene::getZoom();
    raygui::GuiSelection({
        resizeArea.x*zoom + offset.x,
        resizeArea.y*zoom + offset.y,
        resizeArea.width*zoom,
        resizeArea.height*zoom,
    }, 5.0f);

    if(!hold | !dragging){
        dragging = false;
        olddelta = {};
        createBound = true;
        return;
    }
    float increment = Workspace::increment;

    Vector2 delta = mouse - pin;
    delta = {
        delta.x - fmodf(delta.x, increment),
        delta.y - fmodf(delta.y, increment),
    };
    Vector2 temp = delta - olddelta;
    if(Vector2LengthSqr(temp) < (increment*increment))
        return;

    olddelta = delta;

    Rectangle old = resizeArea;
    Rectangle cur = resizeArea;
    switch (dir) {
        case DIR::DOWN:
            cur = {cur.x, cur.y, cur.width, cur.height + temp.y};
            break;
        case DIR::UP:
            cur = {cur.x, cur.y+ temp.y, cur.width, cur.height- temp.y};
            break;
        case DIR::RIGHT:
            cur = {cur.x, cur.y, cur.width + temp.x, cur.height};
            break;
        case DIR::LEFT:
            cur = {cur.x+ temp.x, cur.y, cur.width - temp.x, cur.height};
            break;
        case DIR::TOPRIGHT:
            cur = {cur.x, cur.y + temp.y, cur.width + temp.x, cur.height- temp.y};
            break;
        case DIR::BOTTOMLEFT:
            cur = {cur.x+ temp.x, cur.y, cur.width-  temp.x, cur.height+ temp.y};
            break;
        case DIR::TOPLEFT:
            cur = {cur.x + temp.x, cur.y + temp.y, cur.width- temp.x, cur.height- temp.y};
            break;
        case DIR::BOTTOMRIGHT:
        default:
            cur = {cur.x, cur.y, cur.width + temp.x, cur.height + temp.y};
            break;
    }
    for(GUI* gui: selectGUI){
        Rectangle grec = gui->getGRectangle();
        grec = translateRec(grec, old, cur);
        Vector3 trans{gui->getTransform()};
        Vector2 tleft = inverseTransform({grec.x, grec.y}, trans);
        Vector2 bright = inverseTransform({grec.x+grec.width, grec.y+ grec.height}, trans);
        gui->setRectangle(RecFromAABB(tleft, bright));
    }

    resizeArea =cur;
}