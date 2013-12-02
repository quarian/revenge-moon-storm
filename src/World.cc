#include "World.hh"


World::World(GameState* parent, Map& map, std::vector<Player*> players)
        : GameState(parent), map_(map), players_(players) {}


World::World(Game& game, GameState*& stack, Map& map, std::vector<Player*> players)
        : GameState(game, stack), map_(map), players_(players) {}


void World::init() {
    initKeyboard();

    for (Player* p : players_) {
        p->spawn(map_, map_.getBlock(1,1)); // TODO: spawn points
        p->getActor()->initSprite(
            game_.graphicsManager_.getAnimation("walking_player"),
            game_.graphicsManager_.getAnimation("digging_player"),
            game_.graphicsManager_.getPlayerColor());
    }
    drawAll();
}


void World::resume() {
    initKeyboard();
    drawAll();
}


void World::pause() {
    // spawn(new PauseMenu());
}


void World::initKeyboard() {
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(new GlobalGameInterface(this));
    for (Player* p : players_)
        game_.eventManager_.registerInterface(p->getInterface());
}


void World::update(float dt) {
    updateAll(dt);
    drawAll();
}


void World::updateAll(float dt) {
    for (Player* p : players_) {
        Actor* avatar = p->getActor();
        if (avatar) avatar->update(dt);
    }
    for (Actor* m : monsters_) m->update(dt);
    for (Item* i : items_) i->update(dt);
}


void World::drawAll() {
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

    // for (Item* i : items_)
    //     game_.draw(i->getSprite());
    for (Actor* m : monsters_)
        game_.draw(m->getSprite());
    for (Player* p : players_) {
        Actor* avatar = p->getActor();
        if (avatar) game_.draw(avatar->getSprite());
    }
}
