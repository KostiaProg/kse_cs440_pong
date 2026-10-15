#include <random>
#include <cmath>
#include "ball.hpp"

using namespace std;

ball::ball(float x, float y, float dfSpeed) : object(x, y), defaultSpeed(dfSpeed), currentSpeed(dfSpeed) {
    initVector();
}

ball::ball(pair<float, float> initCoors, float dfSpeed) : object(initCoors), defaultSpeed(dfSpeed), currentSpeed(dfSpeed) {
    initVector();
}


// protected
void ball::normalize() {
    float normFactor = sqrt(pow(vectorDir.first, 2) + pow(vectorDir.second, 2));
    vectorDir = make_pair(vectorDir.first / normFactor, vectorDir.second / normFactor);
}

void ball::initVector() {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(-1.0, 1.0);

    vectorDir = make_pair(dist(gen), dist(gen));
}


// public
void ball::update() {
    updateCoors(vectorDir.first * currentSpeed, vectorDir.second * currentSpeed);
}

void ball::bounceWall() {
    vectorDir.second = -vectorDir.second;
}

void ball::bounceRacket(float hitFactor) {
    vectorDir.first = -vectorDir.first;
    
    vectorDir.second += hitFactor * 0.4f; // 0.4 is a magic number, test it later
    normalize();

    if (currentSpeed != defaultSpeed) currentSpeed = defaultSpeed;
}


// setters and getters
float ball::getRadius() const {
    return r;
}

pair<float, float> ball::getDirection() const {
    return vectorDir;
}


float ball::getCurrentSpeed() const {
    return currentSpeed;
}

void ball::setRadius(float radius) {
    r = radius;
}

void ball::setDirection(const pair<float, float>& dir) {
    vectorDir = dir;
    normalize();                    // always keep it as unit vector
}

void ball::setDirection(float x, float y) {
    vectorDir = make_pair(x, y);
    normalize();
}

void ball::setCurrentSpeed(float speed) {
    currentSpeed = speed;
}