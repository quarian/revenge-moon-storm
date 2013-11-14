#include "Item.hh"
#include <vector>
#include <string>

/*
 * Contains item implementations
*/



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

SmallBomb::SmallBomb(Map& map, MapBlock* location) : Weapon(map, location, "Small Bomb", false) {
	radius_ = 3;
	power_ = 1;
	fusetime_ = 2.0f;
}

void SmallBomb::update(float dt) {
	fusetime_ -= dt;

	if (fusetime_ <= 0 && alive_) {
		//Explode with radius_ and power_
		//Make surrounding map blocks take damage. 

		//map_.blast(location_, radius_, power_);
		//The map could also tell the game to draw explosion animations at each mapblock.
		//

		alive_ = false;
	}
}

Treasure::Treasure(Map& map, MapBlock* location, std::string name, int worth) : Item(map, location, name, true), worth_(worth) {
	//possibly some texture loading etc.
}
void Treasure::update(float) {
	//Animations?
}
