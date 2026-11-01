#pragma once

#include <random>
#include "effect.hpp"

using namespace std;

class speedBallEffect : public effect {
protected:
    random_device rd;
    mutable mt19937 gen;
    mutable uniform_real_distribution<float> dist;
public:
    speedBallEffect() : gen(rd()), dist(3.0f, 6.0f) {}
    speedBallEffect(float minIncrease, float maxIncrease) : gen(rd()), dist(minIncrease, maxIncrease) {}

    // setters and getters
    float getRandomIncreaseSpeed() const;
    virtual EffectType getType() const override;
};