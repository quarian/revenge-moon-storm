#include "MapEditor.hh"

MapEditor::MapEditor(
        GameState* parent ) :
      GameState(parent),
      map_(&game_),
      interface_(*this),
      brush_('#') {}


MapEditor::MapEditor(
        Game& game,
        GameState*& stack) :
      GameState(game, stack),
      map_(&game_),
      interface_(*this),
      brush_('#'){}


void MapEditor::init() {
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

    for (Item* i : map_.items)
        game_.draw(i->getSprite());
}

void MapEditor::saveMap() {
    map_.save();
}
