#include <SFML/Graphics.hpp>
#include <vector>

#include "Game.hh"
#include "Player.hh"

/*
 * WorldGUI.hh
 *
 * This class represents the GUI that's shown in World view, that is, players'
 * health, current weapon & amount, perhaps portrait, and so on. In short,
 * this class handles drawing all things that are not map objects.
 */

class WorldGUI {
public:
    WorldGUI(Game&, int=0, int=0);

    /* Draw the given player's information at the n:th position. */
    void makePlayerInfo(Player*, int);

    void clear();
    void draw();

private:
    Game& game_;
    const int xCoord_, yCoord_;
    std::vector<sf::Drawable*> drawables_;

    sf::Font guiFont_;

    const int PLAYER_INFO_WIDTH = 200;
    const int PLAYER_INFO_HEIGHT = 50;
    const int PLAYER_INFO_SPACING = 20;
};
