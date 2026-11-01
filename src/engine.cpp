#include "engine.hpp"

#include <iostream>

#include "biggerRacketEffect.hpp"
#include "pickup.hpp"
#include "speedBallEffect.hpp"

using namespace std;

engine::engine(int maxScore) : refe(maxScore), gen(rd()), dist(100, 400) {
    timeToSpawnPickup = dist(gen);
}

void engine::startRound(vector<unique_ptr<object>>& objs, unique_ptr<racket>& player,unique_ptr<racketBot>& bot, pair<float, float> boardSize, float halfHeightRacket, float playerX, float botX) {
    objs.clear();

    player = make_unique<racket>(playerX, boardSize.second / 2.0f - halfHeightRacket, boardSize.second / 2.0f + halfHeightRacket);

    auto ballPtr = make_unique<ball>(boardSize.first / 2.0f, boardSize.second / 2.0f);
    ball* rawBall = ballPtr.get();
    objs.push_back(move(ballPtr));

    bot = make_unique<racketBot>(botX, boardSize.second / 2.0f - halfHeightRacket, boardSize.second / 2.0f + halfHeightRacket, rawBall);

    timeToSpawnPickup = dist(gen);
}

void engine::spawnPickup(vector<unique_ptr<object>>& objs, pair<float, float> boardSize) {
    if (--timeToSpawnPickup <= 0) {
        uniform_int_distribution<int> rndPickup(1, 2);

        switch (rndPickup(gen)) {
            case 1:
                objs.push_back(make_unique<pickup>(boardSize.first / 2.0f, boardSize.second / 2.0f, EffectType::SpeedBall));
                break;
            case 2:
                objs.push_back(make_unique<pickup>(boardSize.first / 2.0f, boardSize.second / 2.0f, EffectType::BiggerRacket));
                break;
            default:
                break;
        }

        timeToSpawnPickup = dist(gen);
    }
}

bool engine::checkEndGame() {
    if (refe.getBotScore() == refe.getWinScore() || refe.getPlayerScore() == refe.getWinScore()) isEnd = true;
    return isEnd;
}

void engine::giveScore(bool isBot, vector<unique_ptr<object>>& objs, unique_ptr<racket>& player, unique_ptr<racketBot>& bot, pair<float, float> boardSize, float halfHeightRacket, float playerX, float botX) {
    if (refe.updateScore(isBot)) {
        checkEndGame();
    } else {
        startRound(objs, player, bot, boardSize, halfHeightRacket, playerX, botX);
    }
}

void engine::checkRacketBorders(racket* r, float boardHeight) {
    if (!r) return;
    
    float height = r->getDiff();

    if (r->getY() <= 0.0f) {
        r->setCoors(r->getX(), 0.0f);
        if (r->getCurrentSpeed() < 0.0f) r->resetSpeed();
        r->setIsUpperBorder(true);
    } else {
        r->setIsUpperBorder(false);
    }

    if (r->getBottomY() >= boardHeight) {
        r->setCoors(r->getX(), boardHeight - height);
        if (r->getCurrentSpeed() > 0.0f) r->resetSpeed();
        r->setIsLowerBorder(true);
    } else {
        r->setIsLowerBorder(false);
    }
}

float engine::calculateHitFactor(ball* b, racket* r) {
    if (b->getY() > r->getMiddle()) {
        return (b->getY() - r->getBottomY()) / (r->getY() - r->getBottomY());
    } else {
        return 1.0f - (b->getY() - r->getBottomY()) / (r->getMiddle() - r->getBottomY());
    }
}

bool engine::ballAndRacket(ball* b, racket* r, bool isBot, bool& scored) {
    if (!r || !b) return false;

    bool onEdge = (!isBot && b->getX() - b->getRadius() <= r->getX() + r->getWidth()) || (isBot && b->getX() + b->getRadius() >= r->getX());
    if (!onEdge) return false;

    if (auto* p = dynamic_cast<pickup*>(b)) {
        if (p->getY() >= r->getBottomY() && p->getY() <= r->getY()) {
            if (p->checkCount()) {
                switch (p->getEffectType()) {
                    case EffectType::BiggerRacket:
                        r->addEffect(make_unique<biggerRacketEffect>());
                        break;
                    case EffectType::SpeedBall:
                        r->addEffect(make_unique<speedBallEffect>());
                        break;
                    default:
                        break;
                }
                return true;
            }
        }
        else return true;
    }

    if (b->getY() <= r->getBottomY() && b->getY() >= r->getY()) {
        b->bounceRacket(calculateHitFactor(b, r));
        for (auto& e : r->getEffects()) {
            if (speedBallEffect* sbe = dynamic_cast<speedBallEffect*>(e.get())) {
                b->setCurrentSpeed(sbe->getRandomIncreaseSpeed());
                e = nullptr;
            }
        }
    }
    else scored = true;

    return false;
}

void engine::update(vector<unique_ptr<object>>& objs, unique_ptr<racket>& player, unique_ptr<racketBot>& bot, pair<float, float> boardSize, float halfHeightRacket, float playerX, float botX) {
    if (isEnd) return;

    if (player) {
        checkRacketBorders(player.get(), boardSize.second);
        checkRacketBorders(player.get(), boardSize.second);
        player->update();
    }

    if (bot) {
        checkRacketBorders(bot.get(), boardSize.second);
        checkRacketBorders(bot.get(), boardSize.second);
        bot->update();
    }

    vector<object*> toDestroy;

    for (auto& obj : objs) {
        if (!obj) continue;

        obj->update();

        if (auto* b = dynamic_cast<ball*>(obj.get())) {
            bool shouldRemovePlayer = false;
            bool shouldRemoveBot = false;
            bool scoredPlayer = false;
            bool scoredBot = false;

            shouldRemovePlayer = ballAndRacket(b, player.get(), false, scoredBot);
            if (scoredBot) {
                giveScore(true, objs, player, bot, boardSize, halfHeightRacket, playerX, botX);
                return;
            }

            shouldRemoveBot = ballAndRacket(b, bot.get(), true, scoredPlayer);
            if (scoredPlayer) {
                giveScore(false, objs, player, bot, boardSize, halfHeightRacket, playerX, botX);
                return;
            }

            if (b->getEdgeY() >= boardSize.second || b->getEdgeY() <= 0.0f) {
                b->bounceWall();
            }

            if (shouldRemovePlayer || shouldRemoveBot) {
                toDestroy.push_back(b);
            }
        }
    }

    for (auto* target : toDestroy) {
        erase_if(objs, [target](const unique_ptr<object>& obj) {
            return obj.get() == target;
        });
    }

    spawnPickup(objs, boardSize);
}

void engine::movePlayerUp(racket* player) {
    if (player) player->moveUp();
}

void engine::movePlayerDown(racket* player) {
    if (player) player->moveDown();
}

// setters & getters
bool engine::getIsEnd() const {
    return isEnd;
}

bool engine::checkPlayerWinner() const {
    return refe.getPlayerScore() > refe.getBotScore();
}