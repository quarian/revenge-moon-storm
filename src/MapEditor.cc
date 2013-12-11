#include "MapEditor.hh"
#include <cstring>

MapEditor::MapEditor(
        GameState* parent ) :
      GameState(parent),
      map_(&game_),
      interface_(*this),
      brush_('s'),
      filename_("new.map")
{
    char n = 'z';
    char s = 'x';
    char S = 'c';
    char w = 'v';
    char I = 'b';
    std::string save = "Press s to save the map (saves to /maps folder)";
    std::string items = "Press i to add items";
    if (!font.loadFromFile("./graphics/fonts/sansation.ttf"))
        std::cout << "FAIL!" << std::endl;
    std::cout << "SUCCESS" << std::endl;
    t1 = new sf::Text(n, font, 16u);
    t2 = new sf::Text(s, font, 16u);
    t3 = new sf::Text(S, font, 16u);
    t4 = new sf::Text(w, font, 16u);
    t5 = new sf::Text(I, font, 16u);
    t6 = new sf::Text(save, font, 16u);
    t7 = new sf::Text(items, font, 16u);
}


MapEditor::MapEditor(
        Game& game,
        GameState*& stack,
        std::string map_filename) :
      GameState(game, stack),
      map_(&game_),
      interface_(*this),
      brush_('s'),
      filename_(map_filename)
{
    char n = 'z';
    char s = 'x';
    char S = 'c';
    char w = 'v';
    char I = 'b';
    std::string save = "Press s to save the map (saves to /maps folder)";
    std::string items = "Press i to add items";
    if (!font.loadFromFile("./graphics/fonts/sansation.ttf"))
        std::cout << "FAIL!" << std::endl;
    std::cout << "SUCCESS" << std::endl;
    t1 = new sf::Text(n, font, 16u);
    t2 = new sf::Text(s, font, 16u);
    t3 = new sf::Text(S, font, 16u);
    t4 = new sf::Text(w, font, 16u);
    t5 = new sf::Text(I, font, 16u);
    t6 = new sf::Text(save, font, 16u);
    t7 = new sf::Text(items, font, 16u);
}


void MapEditor::init() {
    std::string path = "./maps/" + filename_;
    if (!map_.loadFromFile(path, game_.terrainManager_))
        map_.loadFromFile("./maps/blank.map", game_.terrainManager_);
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(&interface_);
    draw();
}


void MapEditor::resume() {
    draw();
}

void MapEditor::handleInput(unsigned x, unsigned y) {
    unsigned x_scaled = x / 16u;
    unsigned y_scaled = y / 16u;
    if (x_scaled == 0u || y_scaled == 0u || x_scaled > map_.getWidth() - 2u || y_scaled > map_.getHeight() - 2u)
        return;
    Terrain t(game_.terrainManager_[brush_]);
    map_.setBlock(x_scaled, y_scaled, brush_, t);
}

void MapEditor::update(float) {
    draw();
}

void MapEditor::draw() {
    size_t mapWidth = map_.getWidth();
    size_t mapHeight = map_.getHeight();

    sf::Sprite blockSprite;
    for (size_t x=0; x!=mapWidth; x++) {
        for (size_t y=0; y!=mapHeight; y++) {
            blockSprite.setTexture(map_.getBlock(x,y)->getTexture());
            blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
            game_.draw(blockSprite);
        }
    }

    size_t y = 45;
    size_t x = 3;

    char n = ' ';
    char s = 's';
    char S = 'S';
    char w = 'W';
    char I = '#';
    
    blockSprite.setTexture(game_.terrainManager_[n].texture);
    blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(blockSprite);
    x+=2;
    blockSprite.setTexture(game_.terrainManager_[s].texture);
    blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(blockSprite);
    x+=2;
    blockSprite.setTexture(game_.terrainManager_[S].texture);
    blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(blockSprite);
    x+=2;
    blockSprite.setTexture(game_.terrainManager_[w].texture);
    blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(blockSprite);
    x+=2;
    blockSprite.setTexture(game_.terrainManager_[I].texture);
    blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(blockSprite);

    y++;
    x = 3;

    
    if (!strncmp(&brush_, &n, 1))
        t1->setColor(sf::Color::Red);
    else
        t1->setColor(sf::Color::White);
    t1->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(*t1);
    x+=2;
    if (!strncmp(&brush_, &s, 1))
        t2->setColor(sf::Color::Red);
    else
        t2->setColor(sf::Color::White);
    t2->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(*t2);
    x+=2;
    if (!strncmp(&brush_, &S, 1))
        t3->setColor(sf::Color::Red);
    else
        t3->setColor(sf::Color::White);
    t3->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(*t3);
    x+=2;
    if (!strncmp(&brush_, &w, 1))
        t4->setColor(sf::Color::Red);
    else
        t4->setColor(sf::Color::White);
    t4->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(*t4);
    x+=2;
    if (!strncmp(&brush_, &I, 1))
        t5->setColor(sf::Color::Red);
    else
        t5->setColor(sf::Color::White);
    t5->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(*t5);

    x += 10;
    y--;
    t6->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(*t6);
    y++;
    t7->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
    game_.draw(*t7);

    for (Item* i : map_.items)
        game_.draw(i->getSprite());
}

void MapEditor::saveMap() {
    std::string path = "./maps/" + filename_;
    map_.save(path);
}
