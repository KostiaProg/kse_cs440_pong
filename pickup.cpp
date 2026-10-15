#include <random>
#include "pickup.hpp"

using namespace std;


pickup::pickup(float x, float y, EffectType initEffectOfPickup) : ball(x, y), effectOfPickup(initEffectOfPickup) {
    initCountToPickup();
}

pickup::pickup(std::pair<float, float> initCoors, EffectType initEffectOfPickup) : ball(initCoors), effectOfPickup(initEffectOfPickup) {
    initCountToPickup();
}

pickup::pickup(float x, float y, float dfSpeed, EffectType initEffectOfPickup) : ball(x, y, dfSpeed), effectOfPickup(initEffectOfPickup) {
    initCountToPickup();
}

pickup::pickup(std::pair<float, float> initCoors, float dfSpeed, EffectType initEffectOfPickup) : ball(initCoors, dfSpeed), effectOfPickup(initEffectOfPickup) {
    initCountToPickup();
}

pickup::pickup(float x, float y, float dfSpeed, std::pair<float, float> vecDir, EffectType initEffectOfPickup) : ball(x, y, dfSpeed, vecDir), effectOfPickup(initEffectOfPickup) {
    initCountToPickup();
}

pickup::pickup(std::pair<float, float> initCoors, float dfSpeed, std::pair<float, float> vecDir, EffectType initEffectOfPickup) : ball(initCoors, dfSpeed, vecDir), effectOfPickup(initEffectOfPickup) {
    initCountToPickup();
}


// protected
void pickup::initCountToPickup() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 6);

    countToPickup = dist(gen);
}

// public
bool pickup::checkCount() {
    if (countToPickup == 0) return true; // engine gives effect to racket and deletes pickup

    --countToPickup;
    return false;
}


// setters and getters
int pickup::getCountToPickup() const {
    return countToPickup;
}

bool pickup::getImage() const {
    return image;
}

EffectType pickup::getEffectType() const {
    return effectOfPickup;
}

void pickup::setCountToPickup(int count) {
    countToPickup = count;
}