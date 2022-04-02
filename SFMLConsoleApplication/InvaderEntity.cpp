#include "InvaderEntity.h"
#include "Game.h"
#include <string>

using namespace sf;
using namespace std;

namespace {
	const string textureFilename = "Invader.psd";
	const float RADIUS = 32.0f;
	const float FIRE_RATE = 2.0f;
	const float VELOCITY = 500.0f;
}

InvaderEntity::InvaderEntity(Game *game, Vector2f position, Vector2f direction):
	Entity(game),
	mSprite(game->createSprite(textureFilename, position)),
	mRadius(RADIUS),
	mFireDelta(1.0f / FIRE_RATE),
	mFireTime(0.0f),
	mDirection(direction),
	mVelocity(VELOCITY){}

float InvaderEntity::getRadius() {
	return mRadius;
}
Vector2f InvaderEntity::getPosition() {
	return mSprite.getPosition();
}
EntityType InvaderEntity::getType() {
	return EntityType::SHIP;
}
EntityFaction InvaderEntity::getFaction() {
	return EntityFaction::ENEMY;
}

void InvaderEntity::draw() {
	mGame->draw(mSprite);
}

void InvaderEntity::update(float deltaTime) {
	handleMovement(deltaTime);
	handleFire(deltaTime);
}

void InvaderEntity::handleMovement(float deltaTime) {
	float minX = mRadius;
	float maxX = mGame->getRenderWindow().getSize().x - mRadius;
	Vector2f position = mSprite.getPosition();
	position += deltaTime * mVelocity * mDirection;
	if (position.x < minX) {
		position.x = minX;
		mDirection.x = -mDirection.x;
	}
	else if (maxX < position.x) {
		position.x = maxX;
		mDirection.x = -mDirection.x;
	}
	mSprite.setPosition(position);
}

void InvaderEntity::handleFire(float deltaTime) {
	mFireTime += deltaTime;
	if (mFireDelta < mFireTime && mGame->isVisible(this)) {
		EntityFaction category = EntityFaction::ENEMY;
		Vector2f position = mSprite.getPosition();
		Vector2f direction = Vector2f(0.0f, 20.0f);
		mGame->add(new BulletEntity(mGame, category, position, direction));
		mFireTime = 0.0f;
	}
}

void InvaderEntity::collide(Entity *otherEntity) {
	if (otherEntity->getFaction() == EntityFaction::FRIEND) {
		mGame->add(new ExplosionEntity(mGame, mSprite.getPosition()));
		mGame->remove(this);
	}
}