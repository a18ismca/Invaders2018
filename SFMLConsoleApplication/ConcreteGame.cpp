#include "ConcreteGame.h"

using namespace sf;
using namespace std;

namespace {
	const string windowTitle = "The Ismeters";
	const VideoMode videoMode = VideoMode(1325, 650);
	const Color backgroundColor = Color::Black;
	const int FRAMERATE_LIMIT = 60;

	const float SPAWN_DELTA = 1.0f;
	const float SPAWN_BASE = 1.0f;
	const float SPAWN_INCREMENT = 0.0f;
}

ConcreteGame::ConcreteGame() :
	mGenerator(createGenerator()),
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close),
	mTextureResources(),
	mEntities(),
	mNewEntities(),
	mOldEntities(),
	mTime(0.0f),
	mSpawnTime(0.0f),
	mGameOver(false) {
	mEntities.push_back(new ShipEntity(mGame, Vector2f()));
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);
}

void ConcreteGame::run(){
	Clock clock;
	while (mRenderWindow.isOpen() && !mGameOver) {
		float deltaTime = clock.restart().asSeconds();
		handleWindowEvents();
		clearWindow();
		updateTime(deltaTime);
		updateEntities(deltaTime);
		spawnInvaders(deltaTime);
		collideEntities();
		destroyOldEntities();
		destroyDistantEnemies();
		integrateNewEntities();
		drawEntities();
		displayWindow();
	}
}

ConcreteGame::~ConcreteGame(){}

sf::RenderWindow& ConcreteGame::getRenderWindow() {
	return mRenderWindow;
}

void ConcreteGame::updateTime(float deltaTime) {
mTime += deltaTime;
}

void ConcreteGame::updateEntities(float deltaTime) {
for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
mEntities[i]->update(deltaTime);
}
}

bool ConcreteGame::isVisible(Entity *entity) {
	float minX = 0;
	float minY = 0;
	float maxX = getRenderWindow().getSize().x + entity->getRadius();
	float maxY = getRenderWindow().getSize().y + entity->getRadius();
	if (entity->getPosition().x < maxX && entity->getPosition().y < maxY && entity->getPosition().x > minX && entity->getPosition().y > minY) {
		return true;
	}
	else {
		return false;
	}
}


Sprite ConcreteGame::createSprite(string filename, Vector2f position){
	Sprite sprite(getTexture(filename));
	float originX = 0.5f * sprite.getLocalBounds().width;
	float originY = 0.5f * sprite.getLocalBounds().height;
	Vector2f origin(originX, originY);
	sprite.setOrigin(origin);
	sprite.setPosition(position);
	return sprite;
}

sf::Texture& ConcreteGame::getTexture(string filename) {
	for (TextureResources::size_type i = 0; i < mTextureResources.size(); i++) {
		if (filename == mTextureResources[i]->getFilename()) {
			return mTextureResources[i]->getTexture();
		}
	}
	Texture texture;
	texture.loadFromFile(filename);
	TextureResource *textureResource = new TextureResource(filename, texture);
	mTextureResources.push_back(textureResource);
	return textureResource->getTexture();
}

void ConcreteGame::draw(Sprite &sprite){
	mRenderWindow.draw(sprite);
}

void ConcreteGame::add(Entity *entity){
	mEntities.push_back(entity);
}

void ConcreteGame::remove(Entity *entity){
	mOldEntities.push_back(entity);
}

void ConcreteGame::shipHit() {
	mGameOver = true;
}    

void ConcreteGame::drawEntities(EntityType type) {
for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
Entity *entity = mEntities[i];
if (entity->getType() == type) {
	entity->draw();
		}
	}
}

void ConcreteGame::drawEntities() {
drawEntities(EntityType::PROJECTILE);
drawEntities(EntityType::SHIP);
drawEntities(EntityType::EFFECT);
}void ConcreteGame::spawnInvader() {	Vector2f position = getSpawnPosition();	Vector2f direction = getSpawnDirection();	InvaderEntity *invader = new InvaderEntity(this, position, direction);	mNewEntities.push_back(invader);}void ConcreteGame::spawnInvaders(float deltaTime) {
	mSpawnTime += deltaTime;
	if (SPAWN_DELTA < mSpawnTime) {
		int spawnCount = int(SPAWN_BASE + mTime * SPAWN_INCREMENT);
		for (int i = 0; i < spawnCount; i++) {
			spawnInvader();
		}
		mSpawnTime = 0.0f;
	}
}Vector2f ConcreteGame::getSpawnPosition(){	float x = getRandomFloat(0, getRenderWindow().getSize().x);
	float y = 0;
	return Vector2f(x, y);
}Vector2f ConcreteGame::getSpawnDirection(){	if (getRandomBoolean(0.5)) {		return Vector2f(-1.0f, 0.25f);	}	else {		return Vector2f(1.0f, 0.25f);	}}

EntityVector ConcreteGame::getVisibleEntities() {
	EntityVector visibleEntities;
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity = mEntities[i];
		if (isVisible(entity)) {
			visibleEntities.push_back(entity);
		}
	}
	return visibleEntities;
}

void ConcreteGame::collideEntities() {
	EntityVector visibleEntities = getVisibleEntities();
	for (EntityVector::size_type i = 0; i < visibleEntities.size(); i++) {
		Entity *entity0 = visibleEntities[i];
		for (EntityVector::size_type j = i + 1; j < visibleEntities.size(); j++) {
			Entity *entity1 = visibleEntities[j];
			if (overlap(entity0, entity1)) {
				entity1->collide(entity0);
				entity0->collide(entity1);
			}
		}
	}
}

void ConcreteGame::destroyDistantEnemies(){
	float maxX = getRenderWindow().getSize().x;
	float maxY = getRenderWindow().getSize().y;
	float minX = -100.0f;
	float minY = -100.0f;
		EntityVector remainingEnemies;
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity = mEntities[i];
		if (entity->getPosition().x < maxX && entity->getPosition().y < maxY && entity->getPosition().x > minX && entity->getPosition().y > minY){
			remainingEnemies.push_back(entity);
		}
		else {
			mOldEntities.push_back(entity);
		}
	}
}

bool ConcreteGame::overlap(sf::Vector2f position0, float radius0, sf::Vector2f position1, float radius1){
float deltaX = position0.x - position1.x;
float deltaY = position0.y - position1.y;
float radiusSum = radius0 + radius1;
return deltaX * deltaX + deltaY * deltaY < radiusSum * radiusSum;
}


bool ConcreteGame::overlap(Entity *entity0, Entity *entity1){
	Vector2f shipPosition = entity0->getPosition();
	float shipRadius = entity0->getRadius();
	Vector2f invaderPosition = entity1->getPosition();
	float invaderRadius = entity1->getRadius();
	return overlap(shipPosition, shipRadius, invaderPosition, invaderRadius);
}

void ConcreteGame::destroyOldEntities() {
	EntityVector remainingEntities;
	for (EntityVector::size_type i = 0; i < mEntities.size(); i++) {
		Entity *entity = mEntities[i];
		if (isOld(entity)) {
			delete entity;
		}
		else {
			remainingEntities.push_back(entity);
		}
	}
	mOldEntities.clear();
	mEntities = remainingEntities;
}
bool ConcreteGame::isOld(Entity *entity) {
	for (EntityVector::size_type i = 0; i < mOldEntities.size(); i++) {
		if (entity == mOldEntities[i]) {
			return true;
		}
		else {
		}
	}
	return false;
}

	void ConcreteGame::integrateNewEntities() {
		for (EntityVector::size_type i = 0; i < mNewEntities.size(); i++) {
			mEntities.push_back(mNewEntities[i]);
		}
		mNewEntities.clear();
	}
float ConcreteGame::getRandomFloat(float min, float max) {
	uniform_real_distribution<float> distribution(min, max);
	return distribution(mGenerator);
}
bool ConcreteGame::getRandomBoolean(float probability) {
	float value = getRandomFloat(0.0f, 1.0f);
	if (value < probability) {
		return true;
	}
	else {
		return false;
	}
}
mt19937 ConcreteGame::createGenerator() {
	random_device randomDevice;
	mt19937 generator(randomDevice());
	return generator;
}

void ConcreteGame::handleWindowEvents() {
	Event event;
	while (mRenderWindow.pollEvent(event)) {
		if (event.type == Event::Closed) {
			mRenderWindow.close();
		}
	}
}

void ConcreteGame::clearWindow() {
	mRenderWindow.clear(backgroundColor);
}

void ConcreteGame::displayWindow() {
	mRenderWindow.display();
}

float ConcreteGame::getWindowHeight(){
	Vector2f windowSize = Vector2f(mRenderWindow.getSize());
	float height = windowSize.y;
	return height;
}
