#include "Item.hh"
#include "Game.hh"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

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
        direction_(direction),
        trap_(false) {
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
	static std::vector<std::string> a = {
            "Small Bomb",
            "Large Bomb",
            "Crucifix Bomb",
            "Large Crucifix Bomb",
            "Flamer",
            "Mine",
            "Carpet Bomb",
            "Rocket Launcher",
            "Health Pack",
            "Nuclear Bomb"
	};
	return a;
}

std::vector<std::string> Item::passiveNames() {
	static std::vector<std::string> a = {
		"Pickaxe"
	};
	return a;
}
//Used mostly in the store.
std::vector<std::string> Item::allNames() {
	std::vector<std::string> a = Item::names();
	std::vector<std::string> b = Item::passiveNames();
	a.insert(a.end(), b.begin(), b.end());
	return a;
}

std::map<std::string, std::string> Item::descriptions() {
	std::map<std::string, std::string> d;
	d["Small Bomb"] = "The most minor piece of weaponry you\nhave to defeat the evil forces.\nHas a low range, low power and low cost!";
	d["Large Bomb"] = "More powerful than its baby brother.\nEfficient at clearing moonstone.";
	d["Crucifix Bomb"] = "Explodes in a + shape, extending\nto a small distance and with moderately\nlow power. Stops at metal blocks.";
	d["Large Crucifix Bomb"] = "Extremely powerful bomb that works\njust like the normal version,\nbut extends into infinity.";
	d["Flamer"] = "The best ranged weapon for fighting small\nbugs. Leaves burning ground for a while.";
	d["Mine"] = "Anti-organism trap that arms shortly\nafter being deployed. Deals high\ndamage to close proximity.";
    d["Carpet Bomb"] = "A bomb that jumps unexpectedly around\nwhen it explodes. Can deal high damage\nwith luck.";
    d["Rocket Launcher"] = "A devastating projectile weapon.\nRockets explode on impact.\nNo rocket jumping allowed.";
    d["Health Pack"] = "Restores your health by 40 points.";
    d["Nuclear Bomb"] = "The mother of all bombs. Devastates anything\ncaught in its radius. Can not be defused\neven with a kit.";
	d["Pickaxe"] = "The moonminers' best tool! Allows you\nto mine blocks faster. Effect stacks.";

	return d;
}

//Weapon constructors

NormalBomb::NormalBomb(Map& map, MapBlock* location, std::string name) : 
		Weapon(map, location, name, false, false, Direction::NULLDIR) {
	if (name == "Small Bomb") {
		radius_ = 1;
		power_ = 25.0f;
		fusetime_ = 1.0f;

		buildSprite(5, "bomb_anim_small.png", fusetime_);    
	} else if (name == "Large Bomb") {
		radius_ = 2;
		power_ = 60.0f;
		fusetime_ = 1.0f;

		buildSprite(5, "bomb_anim.png", fusetime_);
	} else if (name == "Nuclear Bomb") {
        radius_ = 10;
        power_ = 200.0f;
        fusetime_ = 3.0f;

        buildSprite(3, "nuclear_anim.png", fusetime_);
    }
}

CrucifixBomb::CrucifixBomb(Map& map, MapBlock* location, std::string name) : 
		Weapon(map, location, name, false, false, Direction::NULLDIR) {
	if (name == "Crucifix Bomb") {
		radius_ = 5;
		power_ = 40.0f;
		fusetime_ = 1.5f;

		buildSprite(4, "crucifix_anim_small.png", fusetime_);
	} else if (name == "Large Crucifix Bomb") {
		radius_ = 64;
		power_ = 80.0f;
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


Mine::Mine(Map& map, MapBlock* mb) : 
        Weapon(map, mb, "Mine", true, false, Direction::NULLDIR),
        armed_(false) {
    radius_ = 1;
    power_ = 65.0f;
    fusetime_ = 0.3f;

    buildSprite(2, "mine_anim.png", 1.0f); //1 second blink time
    sprite_.update(sf::seconds(0.0f)); //Just to make sure...
    sprite_.setLooped(true);
}

CarpetBomb::CarpetBomb(Map& map, MapBlock* mb, int iteration, bool first) : 
        Weapon(map, mb, "Carpet Bomb", true, false, Direction::NULLDIR),
        iteration_(iteration),
        first_(first) {

    radius_ = 1;
    power_ = 25.0f;
    fusetime_ = first ? 1.5f : 0.2f;

    if (first)
        buildSprite(3, "carpet_anim.png", fusetime_);
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

void Mine::update(float dt) {
	if (armed_) { //The mine will blink when it is active
		sprite_.update(sf::seconds(dt));

		if (location_->hasWalkers()) {
			takeDamage(1);
		}

	} else {
		fusetime_ -= dt;
		if (fusetime_ <= 0) {
			armed_ = true;
		}
	}
}

void CarpetBomb::update(float dt) {
    sprite_.update(sf::seconds(dt));
    if (alive_) {
        fusetime_ -= dt;

        if (fusetime_ <= 0) {
            explode();
        }
    }
}

//Weapon takeDamages

bool NormalBomb::takeDamage(float) {
	if (alive_) {
		alive_ = false;
		map_.blast(this);
	}
	return true;
}

bool CrucifixBomb::takeDamage(float) {
	if (alive_) {
		alive_ = false;
		map_.crossblast(this);
	}
	return true;
}

bool Mine::takeDamage(float) {
	if (alive_) {
		alive_ = false;
		map_.blast(this);
	}
	return true;
}

bool CarpetBomb::takeDamage(float) {
    if (first_ && alive_) {
        alive_ = false;
        explode();
    }
    return true;
}

//Non-weapons

Treasure::Treasure(Map& map, MapBlock* location, std::string name, int worth) : Item(map, location, name, true, true, Direction::NULLDIR), worth_(worth) {
	if (name == "Metal Scrap")
        buildSprite(1, "scrap_treasure.png", 1.0f);
    else if (name == "Gunpowder")
        buildSprite(1, "gunpowder_treasure.png", 1.0f);
    else if (name == "Explosives")
        buildSprite(1, "explosives_treasure.png", 1.0f);
    else if (name == "Crate of IEDs") 
        buildSprite(1, "idebox_treasure.png", 1.0f);
    else if (name == "Military Box")
        buildSprite(1, "armybox_treasure.png", 1.0f);
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
	power_ = 2; //one tick per fusetime_, the flame will be up for 1 second
    dps_ = 8.0f;

	buildSprite(4, "flame.png", fusetime_);
	sprite_.setLooped(true);
}

void Flame::update(float dt) {
	sprite_.update(sf::seconds(dt));

    location_->takeDamage(dps_*dt);
    if (alive_) {
        fusetime_ -= dt;
        if (fusetime_ <= 0) {
        	fusetime_ = 0.2f;
        	if (anim_counter++ > 4) {
	            alive_ = false;
	        }
	    }
    }
}

//Other methods

void CarpetBomb::explode() {
    if (alive_) {
        alive_ = false;
        map_.blast(this);
    }
    if (iteration_ > 0) {

        int rx, ry = -1;
        while (map_.getBlock(rx, ry) == nullptr) {
            rx = rand()%8 + location_->x_ - 4;
            ry = rand()%8 + location_->y_ - 4;
        }


        new CarpetBomb(map_, map_.getBlock(rx, ry), iteration_ - 1, false);
    }
}
