#include "ExplosionEntity.h"

using namespace sf;
using namespace std;

namespace {
	const string textureFilename = "Explosion.psd";
	const float RADIUS = 32.0f;
	const float FIRE_RATE = 0.0f;
	const float VELOCITY = 0.0f;
}

ExplosionEntity::ExplosionEntity(Game *game, Vector2f position):
Entity(game),
mSprite(game->createSprite(textureFilename, position)),
mRadius(RADIUS){}

float ExplosionEntity::getRadius() {
	return mRadius;
}

Vector2f ExplosionEntity::getPosition() {
	return mSprite.getPosition();
}
EntityType ExplosionEntity::getType() {
	return EntityType::EFFECT;
}
EntityFaction ExplosionEntity::getFaction() {
	return EntityFaction::NEUTRAL;
}

void ExplosionEntity::draw() {
	mGame->draw(mSprite);
}

void ExplosionEntity::update(float deltaTime) {
	mSprite.getPosition();
	mGame->remove(this);
}

void ExplosionEntity::collide(Entity *otherEntity){}