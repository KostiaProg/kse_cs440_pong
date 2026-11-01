#pragma once

#include <random>
#include "racket.hpp"
#include "ball.hpp"

using namespace std;

class racketBot : public racket {
protected:
    ball* playball;

    random_device rd;
    mt19937 gen;
    uniform_real_distribution<float> offsetDist;
    uniform_int_distribution<int> reactionDist;

    float currentTargetOffset = 0.0f;
    int reactionTimer = 0;
public:
    racketBot(float x, float y, float initBottomY, ball* initPlayball);
    racketBot(std::pair<float, float> initCoors, float initBottomY, ball* initPlayball);
    racketBot(float x, float y, float initBottomY, float initMaxSpeed, float initAcceleration, ball* initPlayball);
    racketBot(std::pair<float, float> initCoors, float initBottomY, float initMaxSpeed, float initAcceleration, ball* initPlayball);

    void update() override;
};