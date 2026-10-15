#include "biggerRacketEffect.hpp"

using namespace std;


// setters and getters
float biggerRacketEffect::getIncreaseRacketSize() const {
    return increaseRacketSize;
}

EffectType biggerRacketEffect::getType() const {
    return EffectType::BiggerRacket;
}