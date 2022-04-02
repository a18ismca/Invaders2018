#include "ShipEntity.h"
#include <vector>
#include <string>

using namespace sf;
using namespace std;

namespace {
	const string textureFilename = "Ship.psd";
	const float RADIUS = 20.0f;
	const float FIRE_RATE = 2.0f;
	const float VELOCITY = 400.0f;
}

ShipEntity::ShipEntity(Game *game, Vector2f position):
Entity(game),
mSprite(game->createSprite(textureFilename, position)),
mRadius(RADIUS),
mFireDelta(1.0f / FIRE_RATE),
mFireTime(0.0f),
mVelocity(VELOCITY){
	mSprite.setPosition(400, 400);
}

void ShipEntity::draw() {
mGame->draw(mSprite);
}

float ShipEntity::getRadius() {
	return 20.0f;
}

Vector2f ShipEntity::getPosition() {
	return mSprite.getPosition();
}

EntityType ShipEntity::getType() {
	return EntityType::SHIP;
}

EntityFaction ShipEntity::getFaction() {
	return EntityFaction::FRIEND;
}

void ShipEntity::update(float deltaTime) {
	handleMovement(deltaTime);
	handleFire(deltaTime);
}

void ShipEntity::handleMovement(float deltaTime) {
	float directionX = 0.0f;
	float directionY = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		directionX -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		directionX += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		directionY += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		directionY -= 1.0f;
	}
	Vector2f direction(directionX, directionY);
	mSprite.move(deltaTime * mVelocity * direction);
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
float minY = mRadius;
float maxY = mGame->getRenderWindow().getSize().y - mRadius;
position += deltaTime * mVelocity * mDirection;
if (position.y < minY) {
	position.y = minY;
	mDirection.y = -mDirection.y;
}
else if (maxY < position.y) {
	position.y = maxY;
	mDirection.y = -mDirection.y;
}
mSprite.setPosition(position);
}

void ShipEntity::handleFire(float deltaTime) {
	mFireTime += deltaTime;
	if (mFireDelta < mFireTime && mGame->isVisible(this) && Keyboard::isKeyPressed(Keyboard::Space)) {
		EntityFaction category = EntityFaction::FRIEND;
		Vector2f position = mSprite.getPosition();
		Vector2f direction0 = Vector2f(0.0f, -15.0f);
		mGame->add(new BulletEntity(mGame, category, position, direction0));
		Vector2f direction1 = Vector2f(-3.0f, -15.0f);
		mGame->add(new BulletEntity(mGame, category, position, direction1));
		Vector2f direction2 = Vector2f(3.0f, -15.0f);
		mGame->add(new BulletEntity(mGame, category, position, direction2));
		mFireTime = 0.0f;
	}	
}

void ShipEntity::collide(Entity *otherEntity){
	if (otherEntity->getFaction() == EntityFaction::ENEMY) {
		mGame->shipHit();
	}
}