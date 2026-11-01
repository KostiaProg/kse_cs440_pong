#include <SFML/Graphics.hpp>
#include <iostream>
#include "renderer.hpp"
#include "pickup.hpp"

using namespace std;

renderer::renderer(float width, float height, int maxScore, float initRacketWidth, float initHalfHeightRacket, float initPlayerX, float initBotX) 
    : boardSize(width, height),
      racketWidth(initRacketWidth),
      halfHeightRacket(initHalfHeightRacket),
      playerX(initPlayerX),
      botX(initBotX),
      engi(maxScore)
{   
    loadDefaultAssets();
    engi.startRound(objs, player, bot, boardSize, halfHeightRacket, playerX, botX);
}

renderer::renderer(std::pair<float, float> size, int maxScore, float initRacketWidth, float initHalfHeightRacket, float initPlayerX, float initBotX) 
    : boardSize(size),
      racketWidth(initRacketWidth),    
      halfHeightRacket(initHalfHeightRacket),
      playerX(initPlayerX),
      botX(initBotX),
      engi(maxScore)
{
    loadDefaultAssets();
    engi.startRound(objs, player, bot, boardSize, halfHeightRacket, playerX, botX);
}


void renderer::loadDefaultAssets() {
    try {
        if (!texBiggerRacket.loadFromFile("resources/BiggerRacketIcon.png")) {
            cout << "Warning: Could not load BiggerRacketIcon.png" << endl;
        }
    } catch (const std::exception& e) {
        cout << "Texture Exception (BiggerRacket): " << e.what() << endl;
    }

    try {
        if (!texSpeedBall.loadFromFile("resources/SpeedBallIcon.png")) {
            cout << "Warning: Could not load SpeedBallIcon.png" << endl;
        }
    } catch (const std::exception& e) {
        cout << "Texture Exception (SpeedBall): " << e.what() << endl;
    }

    try {
        if (font.openFromFile("resources/FUTRFW.ttf")) {
            fontLoaded = true;
        }
        else cout << "Warning: Could not load FUTRFW.ttf" << endl;
    } catch (const std::exception& e) {
        cout << "Font Exception: " << e.what() << endl;
        fontLoaded = false;
    }    
}

void renderer::draw(sf::RenderWindow& window) {
    if (player) {
        sf::RectangleShape playerShape;
        playerShape.setSize(sf::Vector2f(racketWidth, player->getDiff()));
        playerShape.setPosition(sf::Vector2f(player->getX(), player->getY()));
        playerShape.setFillColor(sf::Color::Green);
        window.draw(playerShape);
    }

    if (bot) {
        sf::RectangleShape botShape;
        botShape.setSize(sf::Vector2f(racketWidth, bot->getDiff()));
        botShape.setPosition(sf::Vector2f(bot->getX(), bot->getY()));
        botShape.setFillColor(sf::Color::Red);
        window.draw(botShape);
    }

    for (const auto& obj : objs) {
        if (auto* b = dynamic_cast<ball*>(obj.get())) {
            bool shouldDraw = true;
            
            sf::CircleShape ballShape(b->getRadius());

            ballShape.setOrigin(sf::Vector2f(b->getRadius(), b->getRadius()));
            ballShape.setPosition(sf::Vector2f(b->getX(), b->getY()));
            ballShape.setFillColor(sf::Color::White);
            
            if (auto* p = dynamic_cast<pickup*>(b)) {
                switch (p->getEffectType()) {
                    case EffectType::BiggerRacket: {
                        ballShape.setTexture(&texBiggerRacket);
                        break;
                    }
                    case EffectType::SpeedBall: {
                        ballShape.setTexture(&texSpeedBall);
                        break;
                    }
                    default:
                        break;
                }

                if (p->getCountToPickup() <= p->getCountToBlinking()) {
                    int interval = blinkClock.getElapsedTime().asMilliseconds() / blinkMs; // every 500 ms
                    if (interval % 2 == 0) shouldDraw = false;
                }
            }

            if (shouldDraw) window.draw(ballShape);
        }
    }
}

void renderer::drawEnd(sf::RenderWindow& window) {
    if (fontLoaded) {
        string winText = engi.checkPlayerWinner() ? "PLAYER WINS!" : "BOT WINS!";

        sf::Text text(font, winText, 36);
        text.setFillColor(sf::Color::Yellow);

        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f));

        text.setPosition(sf::Vector2f(boardSize.first / 2.0f, boardSize.second / 2.0f));

        window.draw(text);
    }
    else {
        cout << "No font - iostream" << endl;
        cout << (engi.checkPlayerWinner() ? "PLAYER WINS!" : "BOT WINS!") << endl;
    }
}


void renderer::update(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    if (!engi.getIsEnd()) {
        engi.update(objs, player, bot, boardSize, halfHeightRacket, playerX, botX);
        draw(window);
    }
    else drawEnd(window);

    window.display();
}

void renderer::movePlayerUp() {
    engi.movePlayerUp(player.get());
}

void renderer::movePlayerDown() {
    engi.movePlayerDown(player.get());
}

bool renderer::getIsEnd() const {
    return engi.getIsEnd();
}