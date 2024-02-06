#pragma once

#include "enum.h"
#include <cstddef>
#include <string>

BETTER_ENUM(PARAM, int,
    RECTANGLE,
    STRING,
    STRING_ARRAY,
    INT,
    BOOL
)
class Param
{
private:
    const PARAM type;
    std::string label;
public:
    virtual void* getData() = 0;
    virtual void setData(void* data) = 0;

    inline std::string getLabel() const {return label;}
    inline void setLabel(std::string label) {this->label = label;}
    inline PARAM getType() const {return type;}
    inline const char* getTypeName() const {return type._to_string();}

    inline Param(PARAM type):type(type), label(type._to_string()) {}
    Param() = delete;
    Param(Param &&) = delete;
    Param(const Param &) = delete;
    Param &operator=(Param &&) = delete;
    Param &operator=(const Param &) = delete;
    virtual ~Param() = default;
};