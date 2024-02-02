#pragma once

#include "Param.hpp"
#include "raylib.h"
class PRectangle : public Param{
    private:
    Rectangle data{};
    public:
    virtual void* getData() override;
    virtual void setData(void* data) override;

    inline void setRectangle(Rectangle data){this->data = data;}
    inline Rectangle getRectangle(){return this->data;}
    inline PRectangle(Rectangle rec): Param(ParamTYPE::RECTANGLE), data(rec) {}
    inline PRectangle(): PRectangle(Rectangle{}) {}
    PRectangle(PRectangle &&) = delete;
    PRectangle(const PRectangle &) = delete;
    PRectangle &operator=(PRectangle &&) = delete;
    PRectangle &operator=(const PRectangle &) = delete;
    virtual ~PRectangle() = default;
};