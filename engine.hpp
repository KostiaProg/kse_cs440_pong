#pragma once

#include <utility>
#include <memory>
#include <vector>
#include <random>
#include "object.hpp"
#include "racketBot.hpp"
#include "referee.hpp"

using namespace std;

// ASSIGNMENT 4: images to pickups, their blinking, playground in general


class engine {
private:
    pair<float, float> boardSize;
    float halfHeightRacket;
    float playerX;
    float botX;

    vector<unique_ptr<object>> objs;
    int timeToSpawnPickup;

    unique_ptr<racket> player;
    unique_ptr<racketBot> bot;
    referee refe;

    random_device rd;
    mt19937 gen;
    uniform_int_distribution<int> dist;

    void init();

    void spawnPickup();

    void giveScore(bool isPlayer);
    void startRound();
    void endGame();

    float calculateHitFactor(ball* b, racket* r);
    bool ballAndRacket(ball* b, racket* r, bool isBot);

    bool isEnd = false;
public:
    engine(float width, float height, int maxScore, float initHalfHeightRacket, float initPlayerX, float initBotX)
        : boardSize(width, height),
        halfHeightRacket(initHalfHeightRacket),
        playerX(initPlayerX),
        botX(initBotX),
        refe(maxScore),
        gen(rd()),
        dist(1, 6)
    {}
    engine(pair<float, float> size, int maxScore, float initHalfHeightRacket, float initPlayerX, float initBotX)
        : boardSize(size),
        halfHeightRacket(initHalfHeightRacket),
        playerX(initPlayerX),
        botX(initBotX),
        refe(maxScore),
        gen(rd()),
        dist(1, 6)
    {}

    void update();

    void movePlayerUp();
    void movePlayerDown();

    // getters
    bool getIsEnd() const;
};