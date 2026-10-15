#pragma once

#include "ball.hpp"
#include "effect.hpp"

using namespace std;

class pickup : public ball {
protected:
    int countToPickup = 3;
    const bool image = false; // TEMP, blinks when countToPickup == 1
    const EffectType effectOfPickup;

    void initCountToPickup();
public:
    pickup(float x, float y, EffectType initEffectOfPickup) : ball(x, y), effectOfPickup(initEffectOfPickup) {}
    pickup(pair<float, float> initCoors, EffectType initEffectOfPickup) : ball(initCoors), effectOfPickup(initEffectOfPickup) {}
    pickup(float x, float y, float dfSpeed, EffectType initEffectOfPickup) : ball(x, y, dfSpeed), effectOfPickup(initEffectOfPickup) {}
    pickup(pair<float, float> initCoors, float dfSpeed, EffectType initEffectOfPickup) : ball(initCoors, dfSpeed), effectOfPickup(initEffectOfPickup) {}
    pickup(float x, float y, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup) : ball(x, y, dfSpeed, vecDir), effectOfPickup(initEffectOfPickup) {}
    pickup(pair<float, float> initCoors, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup) : ball(initCoors, dfSpeed, vecDir), effectOfPickup(initEffectOfPickup) {}
    pickup(float x, float y, EffectType initEffectOfPickup, int count) : ball(x, y), effectOfPickup(initEffectOfPickup), countToPickup(count) {}
    pickup(pair<float, float> initCoors, EffectType initEffectOfPickup, int count) : ball(initCoors), effectOfPickup(initEffectOfPickup), countToPickup(count) {}
    pickup(float x, float y, float dfSpeed, EffectType initEffectOfPickup, int count) : ball(x, y, dfSpeed), effectOfPickup(initEffectOfPickup), countToPickup(count) {}
    pickup(pair<float, float> initCoors, float dfSpeed, EffectType initEffectOfPickup, int count) : ball(initCoors, dfSpeed), effectOfPickup(initEffectOfPickup), countToPickup(count) {}
    pickup(float x, float y, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup, int count) : ball(x, y, dfSpeed, vecDir), effectOfPickup(initEffectOfPickup), countToPickup(count) {}
    pickup(pair<float, float> initCoors, float dfSpeed, pair<float, float> vecDir, EffectType initEffectOfPickup, int count) : ball(initCoors, dfSpeed, vecDir), effectOfPickup(initEffectOfPickup), countToPickup(count) {}

    bool checkCount();

    // setters and getters
    int getCountToPickup() const;
    bool getImage() const;
    EffectType getEffectType() const;

    void setCountToPickup(int count);
};