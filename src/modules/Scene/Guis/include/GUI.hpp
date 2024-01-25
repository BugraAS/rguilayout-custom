#pragma once

#include "Node.hpp"
#include "PRectangle.hpp"
#include "Param.hpp"
#include "raylib.h"
#include <string>
#include <vector>

BETTER_ENUM(GUITYPE, int,
    BUTTON,
    TOGGLE,
    PANEL,
    TABS,
    NUM_GUIS
)

class Node; //fix circular dependency problem

class GUI{
    protected:
    std::string label;
    PRectangle rectangle;
    const GUITYPE type;
    Node* parent{nullptr};

    public:
    static GUI* _from_type(GUITYPE type);

    virtual std::vector<Param*> getParams() = 0;
    virtual void draw() = 0;

    inline Rectangle getRectangle() {return *static_cast<Rectangle*>(rectangle.getData());}
    inline void setRectangle(Rectangle rectangle) {this->rectangle.setData(&rectangle);}
    inline std::string getLabel() const {return label;}
    inline void setLabel(std::string label) {this->label = label;}
    inline GUITYPE getType() const {return type;}
    inline const char* getTypeName() const {return type._to_string();}
    inline Node* getParent(){return parent;}

    Rectangle getGRectangle();
    Vector2 getGPos();
    void setParent(Node* parent);
    void offsetPos(Vector2 delta);
    void offsetDim(Vector2 delta);
    void setPos(Vector2 pos);
    Vector2 getPos();
    void setDim(Vector2 size);
    Vector2 getDim();

    inline GUI(GUITYPE type): type(type), rectangle(), label(type._to_string()) {}
    GUI() = delete;
    GUI(GUI &&) = delete;
    GUI(const GUI &) = delete;
    GUI &operator=(GUI &&) = delete;
    GUI &operator=(const GUI &) = delete;
    virtual ~GUI();
};