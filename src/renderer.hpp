#pragma once

#include <SFML/Graphics.hpp>
#include "engine.hpp"
#include "object.hpp"

using namespace std;

class renderer {
private:
    pair<float, float> boardSize;
    float halfHeightRacket;
    float racketWidth;
    float playerX;
    float botX;

    vector<unique_ptr<object>> objs;
    engine engi;

    unique_ptr<racket> player;
    unique_ptr<racketBot> bot;


    sf::Font font;
    bool fontLoaded = false;

    sf::Texture texBiggerRacket;
    sf::Texture texSpeedBall;

    int blinkMs = 150;
    sf::Clock blinkClock;


    void loadDefaultAssets();
    void draw(sf::RenderWindow& window);
    void drawEnd(sf::RenderWindow& window);
public:
    renderer(float width, float height, int maxScore, float initRacketWidth, float initHalfHeightRacket, float initPlayerX, float initBotX);
    renderer(pair<float, float> size, int maxScore, float initRacketWidth, float initHalfHeightRacket, float initPlayerX, float initBotX);

    void update(sf::RenderWindow& window);

    void movePlayerUp();
    void movePlayerDown();

    bool getIsEnd() const;
};