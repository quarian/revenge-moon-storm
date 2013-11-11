#include "Item.hh"
#include <vector>
#include <string>

/*
 * Contains item implementations
*/

std::vector<std::string> Item::names() {
	return std::vector<std::string> {
		"Small Bomb",
		"Gold Bar"
	};
}

//Class declarations here or in Items.hh?
/*class SmallBomb : public Weapon {
public:*/
	SmallBomb::SmallBomb(Map& map) : Weapon(map, "Small Bomb", false) {
		radius_ = 3;
		power_ = 1;
		fusetime_ = 2;
	}

	void SmallBomb::update(float dt) {
		fusetime_ -= dt;

		if (fusetime_ <= 0) {
			//Explode with radius_ and power_
			//Make surrounding map blocks take damage. 
		}

	}
/*private:
};*/

Treasure::Treasure(Map& map, std::string name, int worth) : Item(map, name, true), worth_(worth) {
	//possibly some texture loading etc.
}
void Treasure::update(float) {
	//Nothing really happens here, possibly some animations, shining etc?

	//Player checks the collision with the treasure.
}
