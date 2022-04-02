#pragma once
#include "Entity.h"
#include "Game.h"
class BulletEntity : public Entity {
public:
	BulletEntity(Game *game, EntityFaction category, sf::Vector2f position, sf::Vector2f direction);
	virtual float getRadius() override;
	virtual sf::Vector2f getPosition() override;
	virtual void draw() override;
	virtual void update(float deltaTime) override;
	virtual EntityType getType() override;
	virtual EntityFaction getFaction() override;
	virtual void collide(Entity *otherEntity) override;
private:
	void handleMovement(float deltaTime);
	sf::Sprite mSprite;
	float mRadius;
	float mFireDelta;
	float mFireTime;
	sf::Vector2f mDirection;
float mVelocity;
EntityFaction mBulletFaction;
};