#include "Item.hh"
#include "Game.hh"
#include <vector>
#include <string>

/*
 * Contains item implementations
*/

Item::Item(Map& map,
     MapBlock* location,
     std::string name,
     bool passable,
     bool collectible,
     Direction direction) :
        map_(map),
        location_(location),
        name_(name),
        passable_(passable),
        collectible_(collectible),
        alive_(true),
        direction_(direction) {
    // Register the item with the map and block.
    // The map object takes care of initializing this item's sprite.
    map.pushItem(this);
    location->pushItem(this);
}

Item::~Item() {
	//tell the game and the mapblock that this item is now deleted
	map_.popItem(this);
	location_->popItem(this);
}

void Item::buildSprite(int frames, std::string filename, float totaltime) {
	anim_.setSpriteSheet(map_.getGame()->graphicsManager_.getTexture(filename));
	for (int i = 0; i < frames; ++i) {
		anim_.addFrame(sf::IntRect(i*16, 0, 16, 16));
	}
	sprite_.setFrameTime(sf::seconds(totaltime/frames));
	sprite_.setAnimation(anim_);
	sprite_.setPosition(16*location_->x_, 16*location_->y_);
	sprite_.setLooped(false);
}

std::vector<std::string> Item::names() {
	return std::vector<std::string> {
		"Small Bomb"
	};
}
std::vector<std::string> Item::treasureNames() {
	return std::vector<std::string> {
		"Gold Bar"
	};
}

SmallBomb::SmallBomb(Map& map, MapBlock* location) : Weapon(map, location, "Small Bomb", false, Direction::NULLDIR) {
	radius_ = 2;
	power_ = 12;
	fusetime_ = 2.0f;

	buildSprite(5, "bomb_anim.png", fusetime_);    
}

BigBomb::BigBomb(Map& map, MapBlock* location) : Weapon(map, location, "Small Bomb", false, Direction::NULLDIR) {
	radius_ = 6;
	power_ = 2;
	fusetime_ = 2.0f;
}

void SmallBomb::update(float dt) {
	sprite_.update(sf::seconds(dt));
	if (alive_) {
		fusetime_ -= dt;

		if (fusetime_ <= 0) {
			map_.blast(this);
			alive_ = false;
		}
	}
}


void BigBomb::update(float dt) {
	sprite_.update(sf::seconds(dt));
	if (alive_) {
		fusetime_ -= dt;

		if (fusetime_ <= 0) {
			map_.blast(this);
			alive_ = false;
		}
	}
}

Treasure::Treasure(Map& map, MapBlock* location, std::string name, int worth) : Item(map, location, name, true, true, Direction::NULLDIR), worth_(worth) {
	//possibly some texture loading etc.
}
void Treasure::update(float) {
	//Animations?
}
