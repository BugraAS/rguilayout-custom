#pragma once

#include "GUI.hpp"
#include "PString.hpp"
class Button : public GUI{
    private:
    PString text{};
    public:
    virtual std::vector<Param*> getParams() override;
    virtual void draw() override;

    inline Button() : GUI(GUITYPE::BUTTON) {}
};