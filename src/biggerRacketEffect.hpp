#pragma once
#include "effectTime.hpp"

using namespace std;

class biggerRacketEffect : public effectTime {
protected:
    const float increaseRacketSize = 5.0f;
public:
    biggerRacketEffect() {}
    biggerRacketEffect(float initIncreaseRacketSize) : increaseRacketSize(initIncreaseRacketSize) {}

    // setters and getters
    float getIncreaseRacketSize() const;
    virtual EffectType getType() const override;
};