#pragma once

#include "SFML/Graphics.hpp"

#include "Entity.h"

class Player
    : public Entity
{
private:
    

public:
    Player();
    virtual ~Player();

    virtual void update(float delta) override;
    virtual void updateMovement() override;

    virtual void onEvent(EventType eType, std::vector<void*> params) override;
};

