#include "BulletEntity.h"

using namespace sf;
using namespace std;

namespace {
	const string textureFilename = "Bullet.psd";
	const float RADIUS = 10.0f;
	const float FIRE_RATE = 0.0f;
	const float VELOCITY = 0.0f;
}

BulletEntity::BulletEntity(Game *game, EntityFaction category, Vector2f position, Vector2f direction) :
	Entity(game),
	mSprite(game->createSprite(textureFilename, position)),
	mRadius(RADIUS),
	mDirection(direction),
	mVelocity(VELOCITY),
mBulletFaction(category){}

float BulletEntity::getRadius() {
	return mRadius;
}
Vector2f BulletEntity::getPosition() {
	return mSprite.getPosition();
}
EntityType BulletEntity::getType() {
	return EntityType::PROJECTILE;
}
EntityFaction BulletEntity::getFaction() {
	return mBulletFaction;
}

void BulletEntity::draw() {
	mGame->draw(mSprite);
}

void BulletEntity::update(float deltaTime) {
	mSprite.move(mDirection);
}

void BulletEntity::handleMovement(float deltaTime) {
}

void BulletEntity::collide(Entity *otherEntity) {
	if (otherEntity->getFaction() != mBulletFaction && otherEntity->getType() != EntityType::EFFECT) {
		mGame->add(new ExplosionEntity(mGame, mSprite.getPosition()));
	}
}