#pragma once

#include "enum.h"
#include <cstddef>
#include <string>

BETTER_ENUM(CONTROL, int,
    INT,
    BOOL
)

// Control objects are meant to be stored as shared_ptr
class Control
{
private:
    const CONTROL type;
    std::string label;
public:
    virtual void* getData() = 0;
    virtual void setData(void* data) = 0;

    inline std::string getLabel() const {return label;}
    inline void setLabel(std::string label) {this->label = label;}
    inline CONTROL getType() const {return type;}
    inline const char* getTypeName() const {return type._to_string();}

    inline Control(CONTROL type):type(type), label(type._to_string()) {}
    Control() = delete;
    Control(Control &&) = delete;
    Control(const Control &) = delete;
    Control &operator=(Control &&) = delete;
    Control &operator=(const Control &) = delete;
    virtual ~Control() = default;
};