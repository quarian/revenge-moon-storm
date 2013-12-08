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
	//tell the map and the mapblock that this item is now deleted
	map_.popItem(this);
	location_->popItem(this);
}

void Item::buildSprite(int frames, std::string filename, float totaltime) {
	//Build an animated sprite from the given frame count, filename and total animation cycle time.
	anim_.setSpriteSheet(map_.getGame()->graphicsManager_.getTexture(filename));
	for (int i = 0; i < frames; ++i) {
		anim_.addFrame(sf::IntRect(i*16, 0, 16, 16)); //16x16 frames
	}
	sprite_.setFrameTime(sf::seconds(totaltime/frames));
	sprite_.setAnimation(anim_);
	sprite_.setPosition(16*location_->x_, 16*location_->y_); //Starting position of the sprite
	sprite_.setLooped(false); //this can be manually set back on after building the sprite if needed
}

//Two global use static methods for inventory and map generation

std::vector<std::string> Item::names() {
	return std::vector<std::string> {
		"Small Bomb",
        "Large Bomb",
        "Crucifix Bomb",
        "Large Crucifix Bomb"
	};
}

std::vector<std::string> Item::treasureNames() {
	return std::vector<std::string> {
		"Gold Bar"
	};
}

//Weapon constructors

NormalBomb::NormalBomb(Map& map, MapBlock* location, std::string name) : Weapon(map, location, name, false, Direction::NULLDIR) {
	if (name == "Small Bomb") {
		radius_ = 1;
		power_ = 15;
		fusetime_ = 1.0f;

		buildSprite(5, "bomb_anim_small.png", fusetime_);    
	} else if (name == "Large Bomb") {
		radius_ = 2;
		power_ = 25;
		fusetime_ = 1.0f;

		buildSprite(5, "bomb_anim.png", fusetime_);
	}
}

CrucifixBomb::CrucifixBomb(Map& map, MapBlock* location, std::string name) : Weapon(map, location, name, false, Direction::NULLDIR) {
	if (name == "Crucifix Bomb") {
		radius_ = 5;
		power_ = 26;
		fusetime_ = 1.5f;

		buildSprite(4, "crucifix_anim_small.png", fusetime_);
	} else if (name == "Large Crucifix Bomb") {
		radius_ = 64;
		power_ = 100;
		fusetime_ = 2.0f;

		buildSprite(4, "crucifix_anim.png", fusetime_);
	}
}

//Weapon updates

void NormalBomb::update(float dt) {
	sprite_.update(sf::seconds(dt));
	if (alive_) {
		fusetime_ -= dt;

		if (fusetime_ <= 0) {
			alive_ = false;
			map_.blast(this);
		}
	}
}

void CrucifixBomb::update(float dt) {
	sprite_.update(sf::seconds(dt));
	if (alive_) {
		fusetime_ -= dt;

		if (fusetime_ <= 0) {
			alive_ = false;
			map_.crossblast(this);
		}
	}
}

//Weapon takeDamages

bool NormalBomb::takeDamage(int) {
	if (alive_) {
		alive_ = false;
		map_.blast(this);
	}
	return true;
}

bool CrucifixBomb::takeDamage(int) {
	if (alive_) {
		alive_ = false;
		map_.crossblast(this);
	}
	return true;
}

//Non-weapons

Treasure::Treasure(Map& map, MapBlock* location, std::string name, int worth) : Item(map, location, name, true, true, Direction::NULLDIR), worth_(worth) {
	buildSprite(1, "Goldbar.png", 1.0f);
}
void Treasure::update(float) {
	sprite_.update(sf::seconds(0.0f));
}

//Item derivates

Explosion::Explosion(Map& map, MapBlock* location) : Item(map, location, "explosion", true, false, Direction::NULLDIR) {
    fusetime_ = 0.3f;

    buildSprite(8, "explosion.png", fusetime_);    
}


void Explosion::update(float dt) {
    sprite_.update(sf::seconds(dt));
    if (alive_) {
        fusetime_ -= dt;
        if (fusetime_ <= 0)
            alive_ = false;
    }
}

BloodSplatter::BloodSplatter(Map& map, MapBlock* location) : Item(map, location, "blood splatter", true, false, Direction::NULLDIR) {
    buildSprite(1, "blood_splatter.png", 1.0f);
}

Dustcloud::Dustcloud(Map& map, MapBlock* location) : Item(map, location, "dust cloud", true, false, Direction::NULLDIR) {
	fusetime_ = 0.2f;

	buildSprite(4, "dust.png", fusetime_);
}

void Dustcloud::update(float dt) {
	sprite_.update(sf::seconds(dt));
    if (alive_) {
        fusetime_ -= dt;
        if (fusetime_ <= 0)
            alive_ = false;
    }
}