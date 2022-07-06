#pragma once

#include "SFML/Graphics.hpp"

#include "Entity.h"

class Player
    : public Entity
{
private:
    virtual void updateVelocity() override;
    virtual void updateFrame() override;

public:
    Player();
    virtual ~Player();
    void init();

    virtual void update(float delta) override;

    virtual void onEvent(EventType eType, std::vector<void*> params) override;
};

