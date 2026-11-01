#include <random>
#include "racketBot.hpp"

using namespace std;

void racketBot::update() {
    if (playball) {
        float targetY = playball->getY();
        float currentY = getMiddle();
        float tolerance = playball->getRadius() + dist(gen); // add some noise to the movement

        if (currentY > targetY + tolerance) moveUp();
        else if (currentY < targetY - tolerance) moveDown();
    }

    racket::update();
}