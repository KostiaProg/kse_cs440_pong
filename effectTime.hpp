#pragma once

#include "effect.hpp"

class effectTime : public effect {
protected:
    int time = 20;
public:
    effectTime() {}
    effectTime(int initTime) : time(initTime) {}
    virtual ~effectTime() = default;

    // setters and getters
    void setTime(int newTime) {}
    int updateTime() {}
    int getTime() const {}
};