#include "effectTime.hpp"

// setters and getters
void effectTime::setTime(int newTime) {
    time = newTime;
}

int effectTime::updateTime() {
    return --time;
}

int effectTime::getTime() const {
    return time;
}