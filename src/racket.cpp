#include <cmath>
#include <algorithm>
#include "biggerRacketEffect.hpp"
#include "racket.hpp"

using namespace std;


void racket::moveUp() {
    currentAccel = -acceleration;
}
void racket::moveDown() {
    currentAccel = acceleration;
}

void racket::updateEffectTimers() {
    erase_if(effects, [&](const unique_ptr<effect>& e) {
        if (e == nullptr) return true;

        if (auto* racketE = dynamic_cast<biggerRacketEffect*>(e.get())) {
            if (racketE->updateTime() == 0) {
                bottomY -= racketE->getIncreaseRacketSize();
                return true; // remove it
            }
        }
        return false;
    });
}

// setters and getters
float racket::getBottomY() const {
    return bottomY;
}
float racket::getWidth() const {
    return width;
}
float racket::getDiff() const {
    return bottomY - coors.second;
}
float racket::getMiddle() const {
    return (coors.second + bottomY) / 2;
}

bool racket::getIsUpperBorder() const {
    return isUpperBorder;
}
bool racket::getIsLowerBorder() const {
    return isLowerBorder;
}

float racket::getMaxSpeed() const {
    return maxSpeed;
}
float racket::getAcceleration() const {
    return acceleration;
}
float racket::getCurrentSpeed() const {
    return currentSpeed;
}
vector<unique_ptr<effect>>& racket::getEffects() {
    return effects;
}

void racket::setBottomY(float y) {
    coors.second = coors.second - bottomY + y;
    bottomY = y;
}
void racket::setWidth(float w) {
    width = w;
}
void racket::setPosition(float x, float y) {
    float height = bottomY - coors.second;
    coors.first = x;
    coors.second = y;
    bottomY = y + height;
}
void racket::resetSpeed() {
    currentSpeed = 0.0f;
}
void racket::update() {
    if (currentAccel != 0.0f) currentSpeed += currentAccel;
    else {
        // speed back to 0 when no input key is pressed
        if (currentSpeed > 0.0f) currentSpeed = max(0.0f, currentSpeed - acceleration);
        else if (currentSpeed < 0.0f) currentSpeed = min(0.0f, currentSpeed + acceleration);
    }

    currentAccel = 0.0f;
    currentSpeed = clamp(currentSpeed, -maxSpeed, maxSpeed);

    // not into borders
    if (isUpperBorder && currentSpeed < 0.0f) currentSpeed = 0.0f;
    if (isLowerBorder && currentSpeed > 0.0f) currentSpeed = 0.0f;

    coors.second += currentSpeed;
    bottomY += currentSpeed;

    updateEffectTimers();
}

void racket::addEffect(unique_ptr<effect> e) {
    if (!e) return;
    
    if (auto racketE = dynamic_cast<biggerRacketEffect*>(e.get())) bottomY += racketE->getIncreaseRacketSize();
    effects.push_back(move(e));
}

void racket::setIsUpperBorder(bool newIsBorder) {
    isUpperBorder = newIsBorder;
}
void racket::setIsLowerBorder(bool newIsBorder) {
    isLowerBorder = newIsBorder;
}