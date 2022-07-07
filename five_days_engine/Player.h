#pragma once

#include "SFML/Graphics.hpp"

#include "Entity.h"

class Player
    : public Entity
{
private:
    const int _animStandBegin = 0;
    const int _animWalkBegin = 4;
    const int _animHitBegin = 12;
    const int _animDefenceBegin = 16;
    const int _animDieBegin = 18;

    const int _animStandEnd = 3;
    const int _animWalkEnd = 11;
    const int _animHitEnd = 15;
    const int _animDefenceEnd = 17;
    const int _animDieEnd = 23;

    virtual void updateVelocity() override;
    virtual void updateFrame() override;
    void updateControl();

public:
    Player();
    virtual ~Player();
    void init();

    virtual void update(float delta) override;

    virtual void onEvent(EventType eType, std::vector<void*> params) override;
};

