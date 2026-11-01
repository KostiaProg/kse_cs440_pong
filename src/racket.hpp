#pragma once

#include <vector>
#include <memory>
#include "effect.hpp"
#include "object.hpp"

using namespace std;

class racket : public object {
protected:
    float bottomY;
    float width;

    bool isMoving = false;
    bool isUpperBorder = false;
    bool isLowerBorder = false;

    const float maxSpeed = 50.0f;
    float acceleration = 10.0f;
    float currentSpeed = 0.0f;
    float currentAccel = 0.0f;

    vector<unique_ptr<effect>> effects;

    void updateEffectTimers();
public:
    racket(float x, float y, float initBottomY) : object(x, y), bottomY(initBottomY) {}
    racket(pair<float, float> initCoors, float initBottomY) : object(initCoors), bottomY(initBottomY) {}
    racket(float x, float y, float initBottomY, float initMaxSpeed, float initAcceleration) : object(x, y), bottomY(initBottomY), maxSpeed(initMaxSpeed), acceleration(initAcceleration) {}
    racket(pair<float, float> initCoors, float initBottomY, float initMaxSpeed, float initAcceleration) : object(initCoors), bottomY(initBottomY), maxSpeed(initMaxSpeed), acceleration(initAcceleration) {}
    virtual ~racket() = default;

    void update() override;

    void moveUp();
    void moveDown();

    // setters and getters
    float getBottomY() const;
    float getWidth() const;
    float getDiff() const;
    float getMiddle() const;
    
    bool getIsUpperBorder() const;
    bool getIsLowerBorder() const;

    float getMaxSpeed() const;
    float getAcceleration() const;
    float getCurrentSpeed() const;
    vector<unique_ptr<effect>>& getEffects(); // engine can set to nullptr

    void setBottomY(float y);
    void setWidth(float w);
    void setIsUpperBorder(bool newIsBorder);
    void setIsLowerBorder(bool newIsBorder);
    void resetSpeed();
    void addEffect(unique_ptr<effect> e);
};