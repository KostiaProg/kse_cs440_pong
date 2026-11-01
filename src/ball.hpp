#pragma once

#include <utility>
#include "object.hpp"

using namespace std;

class ball : public object {
protected:
    float r = 20.0f;
    pair<float, float> vectorDir; // how the direction updates, unit vector

    const float defaultSpeed = 1.0f;
    float currentSpeed = defaultSpeed;

    void normalize();
    void initVector();
public:
    ball(float x, float y);
    ball(pair<float, float> initCoors);
    ball(float x, float y, float dfSpeed);
    ball(pair<float, float> initCoors, float dfSpeed);
    ball(float x, float y, float dfSpeed, pair<float, float> vecDir) : object(x, y), defaultSpeed(dfSpeed), currentSpeed(dfSpeed), vectorDir(vecDir) {}
    ball(pair<float, float> initCoors, float dfSpeed, pair<float, float> vecDir) : object(initCoors), defaultSpeed(dfSpeed), currentSpeed(dfSpeed), vectorDir(vecDir) {}

    void update() override;

    void bounceWall();
    void bounceRacket(float hitFactor); // where hit the racket

    // setters and getters
    float getRadius() const;
    pair<float, float> getDirection() const;
    float getEdgeY() const;
    float getCurrentSpeed() const;

    void setRadius(float radius);
    void setDirection(const pair<float, float>& dir);
    void setDirection(float x, float y);
    void setCurrentSpeed(float speed);
};