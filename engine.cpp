#include <iostream>
#include <memory>

#include "engine.hpp"
#include "racketBot.hpp"
#include "pickup.hpp"
#include "biggerRacketEffect.hpp"
#include "speedBallEffect.hpp"

using namespace std;

engine::engine(float width, float height, int maxScore, float initHalfHeightRacket, float initPlayerX, float initBotX) : boardSize(width, height),
    halfHeightRacket(initHalfHeightRacket),
    playerX(initPlayerX),
    botX(initBotX),
    refe(maxScore),
    gen(rd()),
    dist(1, 6)
{
    startRound();
}

engine::engine(pair<float, float> size, int maxScore, float initHalfHeightRacket, float initPlayerX, float initBotX) : boardSize(size),
    halfHeightRacket(initHalfHeightRacket),
    playerX(initPlayerX),
    botX(initBotX),
    refe(maxScore),
    gen(rd()),
    dist(1, 6)
{
    startRound();
}


void engine::spawnPickup() {
    if (--timeToSpawnPickup <= 0) {
        uniform_int_distribution<int> rndPickup(1, 2);

        switch (rndPickup(gen)) {
            case 1:
                objs.push_back(make_unique<pickup>(pickup(boardSize.first / 2, boardSize.second / 2, EffectType::SpeedBall)));
                break;
            case 2:
                objs.push_back(make_unique<pickup>(pickup(boardSize.first / 2, boardSize.second / 2, EffectType::BiggerRacket)));
                break;
            default:
                break;
        }

        timeToSpawnPickup = dist(gen);
    }
}


void engine::giveScore(bool isBot) {
    if (refe.updateScore(isBot)) endGame();
    else startRound();
}


void engine::startRound() {
    objs.clear();

    player = std::make_unique<racket>(playerX, boardSize.second / 2 - halfHeightRacket, boardSize.second / 2 + halfHeightRacket);

    auto ballPtr = std::make_unique<ball>(boardSize.first / 2, boardSize.second / 2);
    ball* rawBall = ballPtr.get();
    objs.push_back(std::move(ballPtr));

    bot = std::make_unique<racketBot>(botX, boardSize.second / 2 - halfHeightRacket, boardSize.second / 2 + halfHeightRacket, rawBall);

    timeToSpawnPickup = dist(gen);
}

void engine::endGame() {
    // add visuals?
    if (refe.getBotScore() == refe.getWinScore()) {
        cout << "The game is over! Bot wins!" << endl;
        isEnd = true;
    }
    else if (refe.getPlayerScore() == refe.getWinScore()) {
        cout << "The game is over! Player wins!" << endl;
        isEnd = true;
    }
    else startRound();
}


float engine::calculateHitFactor(ball* b, racket* r) {
    if (b->getY() > r->getMiddle()) return (b->getY() - r->getBottomY()) / (r->getY() - r->getBottomY());
    else return 1 - (b->getY() - r->getBottomY()) / (r->getMiddle() - r->getBottomY());
}

bool engine::ballAndRacket(ball* b, racket* r, bool isBot) {
    bool onEdge = (!isBot && b->getX() <= r->getX()) || (isBot && b->getX() >= r->getX());
    if (!onEdge) return false;

    if (auto* p = dynamic_cast<pickup*>(b)) {
        if (p->getY() >= r->getBottomY() && p->getY() <= r->getY()) {
            if (p->checkCount()) {
                switch (p->getEffectType()) {
                    case EffectType::BiggerRacket:
                        r->addEffect(std::make_unique<biggerRacketEffect>());
                        break;
                    case EffectType::SpeedBall:
                        r->addEffect(std::make_unique<speedBallEffect>());
                        break;
                    default:
                        break;
                }

                return true;
            }
        }
        else return true;
    }

    // bounce or end round
    if (b->getY() >= r->getBottomY() && b->getY() <= r->getY()) {
        b->bounceRacket(calculateHitFactor(b, r));
        for (auto& e : r->getEffects()) {
            if (speedBallEffect* sbe = dynamic_cast<speedBallEffect*>(e.get())) {
                b->setCurrentSpeed(sbe->getIncreaseSpeed());
                e = nullptr;
            }
        }
    }
    else giveScore(isBot);

    return false;
}


void engine::update() {
    if (player) player->update();
    if (bot) bot->update();

    for (auto& obj : objs) {
        if (!obj) continue;

        obj->update();

        if (auto* b = dynamic_cast<ball*>(obj.get())) {
            bool shouldRemove = false;
            shouldRemove |= ballAndRacket(b, player.get(), false);
            shouldRemove |= ballAndRacket(b, bot.get(), true);

            if (b->getY() >= boardSize.second || b->getY() <= 0.0f) b->bounceWall();
            if (shouldRemove) obj = nullptr;
        }
    }
    erase_if(objs, [](const std::unique_ptr<object>& obj) { return obj == nullptr; });

    spawnPickup();
}


void engine::movePlayerUp() {
    player->moveUp();
}

void engine::movePlayerDown() {
    player->moveDown();
}


bool engine::getIsEnd() const {
    return isEnd;
}