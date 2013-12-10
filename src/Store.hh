#ifndef MB2_STORE_HH
#define MB2_STORE_HH

#include "Player.hh"
#include "GameState.hh"
#include "Direction.hh"

#include <vector>

/*
 * Contains the definition of the store
*/

class Store : public GameState {
public:
	//The constructor wants to know who is buying items. 
	//Only one player accesses the store at a time
	Store(GameState*, Player*);
	Store(Game&, GameState*&, Player*);

	void init();
	void resume() {} //Wont spawn child states
	void update(float);
	void draw();

	void buyItem();
	void sellItem();
	void keyDown(Direction);

	Player* getPlayer() { return player_; }
	

private:
	Player* player_;
	//The selection in the store
	int selection_;
	int selx_;
	int sely_;
	int selmax_;
	int selxmax_;
	int selymax_;

	sf::Font storefont;


	void initKeyboard();

	int getPrice(std::string) const;
	std::string getSelection() const;
};

#endif