#pragma once

using namespace std;

enum class EffectType {
    None,
    BiggerRacket,
    SpeedBall
};

class effect {
public:
    virtual ~effect() = default;
    virtual EffectType getType() const;
};