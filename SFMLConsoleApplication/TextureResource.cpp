#include "TextureResource.h"
#include <iostream>

using namespace sf;
using namespace std;

TextureResource::TextureResource(string filename, Texture texture):
	mFilename(filename),
	mTexture(texture){
	texture.loadFromFile("Bullet.psd");
	texture.loadFromFile("Explosion.psd");
	texture.loadFromFile("Invader.psd");
	texture.loadFromFile("Ship.psd");
}

string TextureResource::getFilename() {
	return mFilename;
}

Texture& TextureResource::getTexture() {
	return mTexture;
}
