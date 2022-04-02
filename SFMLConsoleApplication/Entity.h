#pragma once
#include <string>
class Game;
#include "SFML/Graphics.hpp"

enum class EntityType {PROJECTILE, SHIP, EFFECT};
enum class EntityFaction{FRIEND, ENEMY, NEUTRAL};

class Entity {
public:
	Entity(Game *game);
	virtual ~Entity();
	virtual float getRadius() = 0;
	virtual sf::Vector2f getPosition() = 0;
	virtual EntityType getType() = 0;
	virtual EntityFaction getFaction() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void collide(Entity *otherEntity) = 0;
	virtual void draw() = 0;
protected:
	Game *mGame;
};