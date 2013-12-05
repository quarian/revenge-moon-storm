#include "WorldGUI.hh"

WorldGUI::WorldGUI(
        Game& game,
        int x,
        int y) :
    game_(game),
    xCoord_(x),
    yCoord_(y) {
    guiFont_.loadFromFile("./graphics/fonts/sansation.ttf");
}
                

void WorldGUI::clear() {
    for (auto d : drawables_)
        delete d;
    drawables_.clear();
}


void WorldGUI::draw() {
    for (auto d : drawables_)
        game_.draw(*d);
}


void WorldGUI::makePlayerInfo(Player* player, int n) {
    int xPos = xCoord_ + (n-1) * (PLAYER_INFO_WIDTH + PLAYER_INFO_SPACING);
    int yPos = yCoord_ + 30;
    //sf::RectangleShape rect(sf::Vector2f(PLAYER_INFO_WIDTH, PLAYER_INFO_HEIGHT));
    //rect.setFillColor(sf::Color(200,200,200));
    //rect.setPosition(xPos, yPos);
    //game_.draw(rect);
    sf::Text* playerName = new sf::Text;
    playerName->setFont(guiFont_);
    playerName->setString("HEEEEEE");
    playerName->setCharacterSize(24);
    playerName->setColor(sf::Color::Red);
    playerName->setPosition(0, 0);
    playerName->setStyle(sf::Text::Bold);
    drawables_.push_back(playerName);
}
