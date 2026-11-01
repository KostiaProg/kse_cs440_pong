#include "referee.hpp"

using namespace std;

bool referee::updateScore(bool isBot) {
    if (isBot) ++botScore;
    else ++playerScore;
    return playerScore == winScore || botScore == winScore;
}


int referee::getPlayerScore() const {
    return playerScore;
}

int referee::getBotScore() const {
    return botScore;
}

int referee::getWinScore() const {
    return winScore;
}