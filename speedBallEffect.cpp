#include "speedBallEffect.hpp"

using namespace std;

// setters and getters
float speedBallEffect::getIncreaseSpeed() const {
    return increaseSpeed;
}

EffectType speedBallEffect::getType() const {
    return EffectType::SpeedBall;
}