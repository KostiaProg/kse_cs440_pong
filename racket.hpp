#include <vector>
#include <memory>
#include "effect.hpp"
#include "object.hpp"

using namespace std;

class racket : public object {
protected:
    float bottomY;

    bool isMoving = false;
    const float maxSpeed = 4.0f;
    float acceleration = 0.2f;
    float currentSpeed = 0.0f;

    vector<unique_ptr<effect>> effects;

    void updateEffectTimers();
public:
    racket(float x, float y, float initBottomY) : object(x, y), bottomY(initBottomY) {}
    racket(pair<float, float> initCoors, float initBottomY) : object(initCoors), bottomY(initBottomY) {}
    racket(float x, float y, float initBottomY, float initMaxSpeed, float initAcceleration) : object(x, y), bottomY(initBottomY), maxSpeed(initMaxSpeed), acceleration(initAcceleration) {}
    racket(pair<float, float> initCoors, float initBottomY, float initMaxSpeed, float initAcceleration) : object(initCoors), bottomY(initBottomY), maxSpeed(initMaxSpeed), acceleration(initAcceleration) {}
    virtual ~racket() = default;

    void update() override;

    void moveUp();
    void moveDown();

    // setters and getters
    float getBottomY() const;
    float getMiddle() const;
    float getMaxSpeed() const;
    float getAcceleration() const;
    float getCurrentSpeed() const;
    vector<unique_ptr<effect>>& getEffects(); // engine can set to nullptr

    void setBottomY(float y);
    void addEffect(unique_ptr<effect> e);
};