#pragma once
#include "Entity.h"
#include "ExplosionEntity.h"
#include "BulletEntity.h"
#include "Game.h"
class InvaderEntity : public Entity {
public:
	InvaderEntity(Game *game, sf::Vector2f position, sf::Vector2f direction);
	virtual float getRadius() override;
	virtual sf::Vector2f getPosition() override;
	virtual EntityType getType() override;
	virtual EntityFaction getFaction() override;
	virtual void update(float deltaTime) override;
	virtual void collide(Entity *otherEntity) override;
	virtual void draw() override;
private:
	void handleMovement(float deltaTime);
	void handleFire(float deltaTime);
	sf::Sprite mSprite;
	float mRadius;
	float mFireDelta;
	float mFireTime;
	sf::Vector2f mDirection;
	float mVelocity;
	float mTime;
};