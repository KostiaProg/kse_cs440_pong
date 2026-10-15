#include <cmath>
#include "biggerRacketEffect.hpp"
#include "racket.hpp"

using namespace std;


void racket::moveUp() {
    isMoving = true;
    coors.second += currentSpeed;
    bottomY += currentSpeed;
}
void racket::moveDown() {
    isMoving = true;
    coors.second -= currentSpeed;
    bottomY -= currentSpeed;
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
float racket::getMiddle() const {
    return (coors.second + bottomY) / 2;
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
void racket::update() {
    if (isMoving) currentSpeed = min(maxSpeed, currentSpeed+acceleration);
    else currentSpeed = max(0.0f, currentSpeed-acceleration);

    updateEffectTimers();
}

void racket::addEffect(unique_ptr<effect> e) {
    if (!e) return;
    
    if (auto racketE = dynamic_cast<biggerRacketEffect*>(e.get())) bottomY += racketE->getIncreaseRacketSize();
    effects.push_back(move(e));
}