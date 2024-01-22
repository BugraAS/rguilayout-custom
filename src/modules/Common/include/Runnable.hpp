#pragma once

class Runnable{
  public:
    virtual void process() = 0;
    Runnable() = default;
    virtual ~Runnable() = default;
};