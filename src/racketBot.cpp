#include <random>
#include "racketBot.hpp"

using namespace std;

racketBot::racketBot(float x, float y, float initBottomY, ball* initPlayball)
    : racket(x, y, initBottomY),
      playball(initPlayball),
      gen(rd()),
      offsetDist(-acceleration * 120.0f, acceleration * 120.0f),
      reactionDist(60, 90) {}

racketBot::racketBot(std::pair<float, float> initCoors, float initBottomY, ball* initPlayball)
    : racket(initCoors, initBottomY),
      playball(initPlayball),
      gen(rd()),
      offsetDist(-acceleration * 120.0f, acceleration * 120.0f),
      reactionDist(60, 90) {}

racketBot::racketBot(float x, float y, float initBottomY, float initMaxSpeed, float initAcceleration, ball* initPlayball)
    : racket(x, y, initBottomY, initMaxSpeed, initAcceleration),
      playball(initPlayball),
      gen(rd()),
      offsetDist(-initAcceleration * 120.0f, initAcceleration * 120.0f),
      reactionDist(60, 90) {}

racketBot::racketBot(std::pair<float, float> initCoors, float initBottomY, float initMaxSpeed, float initAcceleration, ball* initPlayball)
    : racket(initCoors, initBottomY, initMaxSpeed, initAcceleration),
      playball(initPlayball),
      gen(rd()),
      offsetDist(-initAcceleration * 120.0f, initAcceleration * 120.0f),
      reactionDist(60, 90) {}

void racketBot::update() {
    racket::update();

    if (!playball) return;

    // only change position when some time passes
    if (--reactionTimer <= 0) {
        currentTargetOffset = offsetDist(gen);
        reactionTimer = reactionDist(gen);
    }

    float targetY = playball->getY() + currentTargetOffset;
    float botMiddle = getMiddle();
    float deadZone = 30.0f;

    if (targetY < botMiddle - deadZone) moveUp();
    else if (targetY > botMiddle + deadZone) moveDown();
}