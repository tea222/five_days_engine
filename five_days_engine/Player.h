#pragma once

#include "SFML/Graphics.hpp"

#include "Entity.h"

class Player
    : public Entity
{
private:
    

public:
    virtual void update(float delta) override;
};

