#pragma once
#include "effect.hpp"

using namespace std;

class speedBallEffect : public effect {
protected:
    const float increaseSpeed = 2.5f;
public:
    speedBallEffect() {}
    speedBallEffect(float initIncreaseSpeed) : increaseSpeed(initIncreaseSpeed) {}

    // setters and getters
    float getIncreaseSpeed() const;
    virtual EffectType getType() const override;
};