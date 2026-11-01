#pragma once

#include <memory>
#include <random>
#include <utility>
#include <vector>

#include "object.hpp"
#include "racket.hpp"
#include "racketBot.hpp"
#include "referee.hpp"

using namespace std;

class engine {
private:
    referee refe;

    random_device rd;
    mt19937 gen;
    uniform_int_distribution<int> dist;

    int timeToSpawnPickup;
    bool isEnd = false;

    void checkRacketBorders(racket* r, float boardHeight);
    float calculateHitFactor(ball* b, racket* r);
    bool ballAndRacket(ball* b, racket* r, bool isBot, bool& scored);

    void giveScore(bool isBot, vector<unique_ptr<object>>& objs, unique_ptr<racket>& player, unique_ptr<racketBot>& bot, pair<float, float> boardSize, float halfHeightRacket, float playerX, float botX);
public:
    engine(int maxScore);

    void startRound(vector<unique_ptr<object>>& objs, unique_ptr<racket>& player, unique_ptr<racketBot>& bot, pair<float, float> boardSize, float halfHeightRacket, float playerX, float botX);

    void spawnPickup(vector<unique_ptr<object>>& objs, pair<float, float> boardSize);

    void destroyObject(vector<unique_ptr<object>>& objs, object* target);

    bool checkEndGame();

    void update(vector<unique_ptr<object>>& objs, unique_ptr<racket>& player, unique_ptr<racketBot>& bot, pair<float, float> boardSize, float halfHeightRacket, float playerX, float botX);

    void movePlayerUp(racket* player);
    void movePlayerDown(racket* player);

    // setters & getters
    bool getIsEnd() const;
    bool checkPlayerWinner() const;
};