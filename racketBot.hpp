#pragma once

#include <random>
#include "racket.hpp"
#include "ball.hpp"

using namespace std;

class racketBot : public racket {
protected:
    ball* playball;
    float noiseMovement;

    random_device rd;
    mt19937 gen;
    uniform_real_distribution<float> dist;

    void initNoiseMovementRnd();
public:
    racketBot(float x, float y, float initBottomY, ball*  initPlayball) : racket(x, y, initBottomY), playball(initPlayball), gen(rd()), dist(-acceleration * 2, acceleration * 2) {}
    racketBot(pair<float, float> initCoors, float initBottomY, ball*  initPlayball) : racket(initCoors, initBottomY), playball(initPlayball), gen(rd()), dist(-acceleration * 2, acceleration * 2) {}
    racketBot(float x, float y, float initBottomY, float initMaxSpeed, float initAcceleration, ball*  initPlayball) : racket(x, y, initBottomY, initMaxSpeed, initAcceleration), playball(initPlayball), gen(rd()), dist(-acceleration * 2, acceleration * 2) {}
    racketBot(pair<float, float> initCoors, float initBottomY, float initMaxSpeed, float initAcceleration, ball*  initPlayball) : racket(initCoors, initBottomY, initMaxSpeed, initAcceleration), playball(initPlayball), gen(rd()), dist(-acceleration * 2, acceleration * 2) {}

    void update() override;
};