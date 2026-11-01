#pragma once

using namespace std;

class referee {
private:
    int playerScore = 0;
    int botScore = 0;
    int winScore = 3;
public:
    referee() {}
    referee(int initWinScore) : winScore(initWinScore) {}

    bool updateScore(bool isBot);

    // getters
    int getPlayerScore() const;
    int getBotScore() const;
    int getWinScore() const;
};