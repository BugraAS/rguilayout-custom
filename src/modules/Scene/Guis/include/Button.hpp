#pragma once

#include "GUI.hpp"
#include "PString.hpp"
class Button : public GUI{
    private:
    PString text;
    public:
    std::vector<Param*> getParams() override;
    void draw() override;
    GUI* copy() override;

    inline Button() : GUI(GUITYPE::BUTTON), text(type._to_string()) {}
};