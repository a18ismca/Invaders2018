#pragma once
#include "Entity.h"
#include "Game.h"
class ExplosionEntity : public Entity {
public:
	ExplosionEntity(Game *game, sf::Vector2f position);
	virtual float getRadius() override;
	virtual sf::Vector2f getPosition() override;
	virtual EntityType getType() override;
	virtual EntityFaction getFaction() override;
	virtual void update(float deltaTime) override;
	virtual void collide(Entity *otherEntity) override;
	virtual void draw() override;
private:
	sf::Sprite mSprite;
	float mRadius;
	float mVelocity;
	float mTime;
};