#include "speedBallEffect.hpp"

using namespace std;

// setters and getters
float speedBallEffect::getRandomIncreaseSpeed() const {
    return dist(gen);
}

EffectType speedBallEffect::getType() const {
    return EffectType::SpeedBall;
}