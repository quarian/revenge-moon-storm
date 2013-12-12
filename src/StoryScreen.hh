#ifndef MB2_STORYSCREEN_HH
#define MB2_STORYSCREEN_HH

#include "GameState.hh"
#include "KeyInterface.hh"

/*
 * Contains the definition of the store
*/
class StoryScreen;

class StoryInterface : public KeyInterface {
public:
	StoryInterface(StoryScreen*);
	bool parse(sf::Event&);

	bool operator==(KeyInterface const& other) const {
	    if (StoryInterface const* pi = dynamic_cast<StoryInterface const*>(&other)) {
	        return story_ == pi->story_;
	    } else return false;
	}
private:
	StoryScreen* story_;
};

class StoryScreen : public GameState {
public:
	//The constructor wants to know who is buying items. 
	//Only one player accesses the store at a time
	StoryScreen(GameState*, std::vector<std::string>g);
	StoryScreen(Game&, GameState*&, std::vector<std::string>);

	~StoryScreen();

	void init();
	void resume() {} //Wont spawn child states
	void update(float);
	void draw();

	bool passed_;

	void kill() { terminate(); }
	
private:

	float timer_;

	std::vector<std::string> story_;

	sf::Font& storyfont_;
	sf::Text* storytext_;

	void initKeyboard();

};

#endif