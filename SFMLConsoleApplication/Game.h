#pragma once

#include "ShipEntity.h"
#include "InvaderEntity.h"
#include <vector>

class Entity;
#include <string>
#include "SFML/Graphics.hpp"

class Game {
public:
	Game();
	virtual ~Game();
virtual bool isVisible(Entity *entity) = 0;
	virtual sf::RenderWindow& getRenderWindow() = 0;
	virtual sf::Sprite createSprite(std::string filename, sf::Vector2f position = sf::Vector2f()) = 0;
	virtual void run() = 0;
	virtual void draw(sf::Sprite &sprite) = 0;
	virtual void add(Entity *entity) = 0;
	virtual void remove(Entity *entity) = 0;
	virtual void shipHit() = 0;
protected:
	Game *mGame = this;
};