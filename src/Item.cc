#include "Item.hh"
#include "Game.hh"
#include <vector>
#include <string>
#include <algorithm>

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
            "Large Crucifix Bomb",
            "Flamer"
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
		power_ = 25;
		fusetime_ = 1.0f;

		buildSprite(5, "bomb_anim_small.png", fusetime_);    
	} else if (name == "Large Bomb") {
		radius_ = 2;
		power_ = 60;
		fusetime_ = 1.0f;

		buildSprite(5, "bomb_anim.png", fusetime_);
	}
}

CrucifixBomb::CrucifixBomb(Map& map, MapBlock* location, std::string name) : Weapon(map, location, name, false, Direction::NULLDIR) {
	if (name == "Crucifix Bomb") {
		radius_ = 5;
		power_ = 40;
		fusetime_ = 1.5f;

		buildSprite(4, "crucifix_anim_small.png", fusetime_);
	} else if (name == "Large Crucifix Bomb") {
		radius_ = 64;
		power_ = 80;
		fusetime_ = 2.0f;

		buildSprite(4, "crucifix_anim.png", fusetime_);
	}
}


Flamer::Flamer(Map& map, MapBlock* mb, Direction dir, int damage, int spreadChance, size_t telomere, float spreadSpeed) :
        Item(map, mb, "Flamer", true, false, dir),
        spreadChance_(spreadChance),
        telomere_(telomere),
        spreadSpeed_(spreadSpeed),
        damage_(damage),
        lifetime_(spreadSpeed) {
    new Flame(map, mb);
    mb->takeDamage(damage);
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

void Flamer::update(float dt) {
    lifetime_ -= dt;
    if (lifetime_ < 0) {
        alive_ = false;
        if (location_->isPassable() && telomere_ > 0) {
            new Flamer(map_, location_->getBlock(direction_),
                    direction_, damage_, spreadChance_, telomere_-1, spreadSpeed_);

            if (rand() % 100 <= spreadChance_) {
                new Flamer(map_, location_->getBlock(direction_)->getBlock(direction_.cw()),
                    direction_, damage_, spreadChance_, telomere_-1, spreadSpeed_);
            }
            if (rand() % 100 <= spreadChance_) {
                new Flamer(map_, location_->getBlock(direction_)->getBlock(direction_.ccw()),
                    direction_, damage_, spreadChance_, telomere_-1, spreadSpeed_);
            }
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

Weaponbox::Weaponbox(Map& map, MapBlock* location) : Item(map, location, "weapon box", true, true, Direction::NULLDIR) {
	buildSprite(1, "weaponbox.png", 1.0f);
}
void Weaponbox::update(float) {
	sprite_.update(sf::seconds(0.0f));
}

std::string Weaponbox::generateItem() const {
	return Item::names()[rand() % Item::names().size()];
}

//Item derivates

Explosion::Explosion(Map& map, MapBlock* location, float fuse) :
        Item(map, location, "explosion", true, false, Direction::NULLDIR), fusetime_(fuse) {
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

BloodSplatter::BloodSplatter(Map& map, MapBlock* location, std::string imagefile) :
        Item(map, location, "blood splatter", true, false, Direction::NULLDIR) {
    buildSprite(1, imagefile, 1.0f);
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

Flame::Flame(Map& map, MapBlock* location) : Item(map, location, "flame", true, false, Direction::NULLDIR) {
	fusetime_ = 0.2f;
	anim_counter = 0;
	power_ = 1; //one tick per fusetime_, the flame will be up for 1 second

	buildSprite(4, "flame.png", fusetime_);
	sprite_.setLooped(true);
}

void Flame::update(float dt) {
	sprite_.update(sf::seconds(dt));
    if (alive_) {
        fusetime_ -= dt;
        if (fusetime_ <= 0) {
        	fusetime_ = 0.2f;
        	if (anim_counter++ > 4) {
	            alive_ = false;
	        }
	       	location_->takeDamage(power_);
	    }
    }
}
