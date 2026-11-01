#pragma once

#include <utility>

using namespace std;

class object {
protected:
    pair<float, float> coors;
public:
    object(float x, float y) : coors(x, y) {}
    object(pair<float, float> initCoors) : coors(initCoors) {}
    virtual ~object() = default;

    // virtual void draw() const = 0; // MUST CALLS update() INSIDE AT THE BEGINNING
    virtual void update() = 0;

    // setters getters
    void setCoors(pair<float, float> newCoors);
    void updateCoors(pair<float, float> newCoors);
    void setCoors(float x, float y);
    void updateCoors(float x, float y);

    pair<float, float> getCoors() const;
    float getX() const;
    float getY() const;
};