#pragma once

#include "Game.h"
#include "TextureResource.h"
#include "ShipEntity.h"
#include "InvaderEntity.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>

typedef std::vector<Entity*> EntityVector;

class ConcreteGame : public Game {
public:
	ConcreteGame();
	~ConcreteGame();
	virtual void run() override;
	virtual bool isVisible(Entity *entity) override;
	virtual sf::RenderWindow& getRenderWindow() override;
	virtual sf::Sprite createSprite(std::string filename, sf::Vector2f position = sf::Vector2f()) override;
	virtual void draw(sf::Sprite &sprite) override;
	virtual void add(Entity *entity) override;
	virtual void remove(Entity *entity) override;
	virtual void shipHit() override;
private:
	void handleWindowEvents();
	void clearWindow();
	void displayWindow();
	float getWindowHeight();

	void updateTime(float deltaTime);
	void updateEntities(float deltaTime);
	void drawEntities();
	void drawEntities(EntityType type);

	void spawnInvader();
	void spawnInvaders(float deltaTime);
	void collideEntities();
	void destroyOldEntities();
	void destroyDistantEnemies();
	void integrateNewEntities();

	float getRandomFloat(float min, float max);

	sf::Vector2f getSpawnPosition();
	sf::Vector2f getSpawnDirection();

	std::mt19937 mGenerator;
	std::mt19937 createGenerator();

	sf::Texture& getTexture(std::string filename);
	sf::Clock mClock;

	sf::RenderWindow mRenderWindow;

	typedef std::vector<TextureResource*> TextureResources;
	TextureResources mTextureResources;

	
	EntityVector mEntities;
	EntityVector mOldEntities;
	EntityVector mNewEntities;

	EntityVector getVisibleEntities();

	float mTime;
	float mSpawnTime;

	bool isOld(Entity *entity);

	bool overlap(sf::Vector2f position0, float radius0, sf::Vector2f position1, float radius1);
	bool overlap(Entity *entity0, Entity *entity1);

	bool getRandomBoolean (float probability);
	bool mGameOver;
};