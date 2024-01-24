#pragma once

#include "Param.hpp"
#include <string>
class PString : public Param{
    private:
    std::string data{};
    public:
    virtual void* getData() override;
    virtual void setData(void* data) override;

    inline PString(std::string str): Param(ParamTYPE::STRING), data(str) {}
    inline PString(): PString("") {}
    PString(PString &&) = delete;
    PString(const PString &) = delete;
    PString &operator=(PString &&) = delete;
    PString &operator=(const PString &) = delete;
    virtual ~PString() = default;
};