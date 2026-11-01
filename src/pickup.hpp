#pragma once

#include "ball.hpp"
#include "effect.hpp"

using namespace std;

class pickup : public ball {
protected:
    int countToPickup = 300;
    int countToBlinking = 100;
    const EffectType effectOfPickup;

    void initCountToPickup();
public:
    pickup(float x, float y, EffectType initEffectOfPickup);
    pickup(pair<float, float> initCoors, EffectType initEffectOfPickup);
    pickup(float x, float y, float dfSpeed, EffectType initEffectOfPickup);
    pickup(pair<float, float> initCoors, float dfSpeed, EffectType initEffectOfPickup);
    pickup(float x, float y, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup);
    pickup(pair<float, float> initCoors, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup);
    pickup(float x, float y, EffectType initEffectOfPickup, int count);
    pickup(pair<float, float> initCoors, EffectType initEffectOfPickup, int count);
    pickup(float x, float y, float dfSpeed, EffectType initEffectOfPickup, int count);
    pickup(pair<float, float> initCoors, float dfSpeed, EffectType initEffectOfPickup, int count);
    pickup(float x, float y, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup, int count);
    pickup(pair<float, float> initCoors, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup, int count);

    bool checkCount();
    void update() override;

    // setters and getters
    int getCountToPickup() const;
    int getCountToBlinking() const;
    bool startBlinking() const;
    EffectType getEffectType() const;

    void setCountToPickup(int count);
};