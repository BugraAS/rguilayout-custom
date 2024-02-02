#pragma once

#include "Param.hpp"
#include <string>
class PString : public Param{
    private:
    std::string data{};
    public:
    void* getData() override;
    void setData(void* data) override;

    inline void setString(std::string data){this->data = data;}
    inline std::string getString(){return this->data;}
    inline PString(std::string str): Param(ParamTYPE::STRING), data(str) {}
    inline PString(): PString("") {}
    PString(PString &&) = delete;
    PString(const PString &) = delete;
    PString &operator=(PString &&) = delete;
    PString &operator=(const PString &) = delete;
    virtual ~PString() = default;
};