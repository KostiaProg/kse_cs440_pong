#include <random>
#include "racketBot.hpp"

using namespace std;

void racketBot::initNoiseMovementRnd() {
    random_device rd;
    gen = mt19937(rd());
    dist = uniform_real_distribution<float>(-acceleration * 2, acceleration * 2);
}

void racketBot::update() {
    racket::update();

    acceleration = dist(gen);
    if (getMiddle() > playball->getY()) moveDown();
    else moveUp();
}