#include "object.hpp"

// setters and getters
void object::setCoors (pair<float, float> newCoors) {
    coors = newCoors;
}
void object::updateCoors(pair<float, float> newCoors) {
    coors.first += newCoors.first;
    coors.second += newCoors.second;
}
void object::setCoors (float x, float y) {
    coors = make_pair(x, y);
}
void object::updateCoors(float x, float y) {
    coors.first += x;
    coors.second += y;
}

pair<float, float> object::getCoors() const {
    return coors;
}
float object::getX() const {
    return coors.first;
}
float object::getY() const {
    return coors.second;
}