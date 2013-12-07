#include <SFML/Graphics.hpp>
#include <algorithm>
#include "World.hh"
#include "Enemies.hh"


World::World(GameState* parent, Map& map, std::vector<Player*> players)
        : GameState(parent),
          map_(map),
          players_(players),
          gui_(WorldGUI(*map.getGame(), 0, 704))  {
    map.players.clear();
    for (auto p : players)
        map.players.insert(p);
}

World::World(Game& game, GameState*& stack, Map& map, std::vector<Player*> players)
        : GameState(game, stack),
          map_(map),
          players_(players),
          gui_(WorldGUI(*map.getGame()))  {
    map.players.clear();
    for (auto p : players)
        map.players.insert(p);
}


void World::init() {
    initKeyboard();

    for (Player* p : map_.players) {
        p->spawn(map_, map_.getBlock(1,1)); // TODO: spawn points
        p->getActor()->initSprite(
            game_.graphicsManager_.getAnimation("walking_player"),
            game_.graphicsManager_.getAnimation("digging_player"),
            game_.graphicsManager_.getPlayerColor());
    }

    AIPlayerSeeker* monster = new TinyBug(map_, map_.getBlock(30,30));
    map_.getBlock(30,30)->enter(monster);
    map_.monsters.insert(monster);

    drawMapObjects();
}


void World::resume() {
    initKeyboard();
    drawMapObjects();
}


void World::pause() {
    // spawn(new PauseMenu());
}


void World::terminate() {
    for (auto i : map_.items) delete i;
}


void World::initKeyboard() {
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(new GlobalGameInterface(this));
    for (Player* p : map_.players)
        game_.eventManager_.registerInterface(p->getInterface());
}


void World::update(float dt) {
    cull();
    updateAll(dt);
    drawMapObjects();
}


void World::cull() {
    // Remove dead items
    std::vector<Item*> deadItems;
    for (Item* i : map_.items)
        if (!i->getAlive())
            deadItems.push_back(i);
    for (Item* i : deadItems) delete i;

    // Kill dead monsters
    std::vector<Walker*> deadMonsters;
    for (Walker* w : map_.monsters)
        if (!w->isAlive())
            deadMonsters.push_back(w);
    for (Walker* w : deadMonsters) {
        new BloodSplatter(map_, w->getLocation());
        map_.monsters.erase(w);
        delete w;
    }

    // Kill dead Players
    std::vector<Player*> deadPlayers;
    for (Player* p : map_.players)
        if (!p->getActor()->isAlive())
            deadPlayers.push_back(p);
    for (Player* p : deadPlayers) {
        new BloodSplatter(map_, p->getActor()->getLocation());
        map_.players.erase(p);
        p->die();
    }
}


void World::updateAll(float dt) {
    // Update players
    for (Player* p : map_.players) {
        Actor* avatar = p->getActor();
        if (avatar) avatar->update(dt);
    }

    // Update monsters
    for (Walker* m : map_.monsters) m->update(dt);

    // Update items
    for (Item* i : map_.items)
        i->update(dt);
}


void World::drawMapObjects() {
    size_t mapWidth = map_.getWidth();
    size_t mapHeight = map_.getHeight();

    sf::Sprite blockSprite;
    for (size_t x=0; x!=mapWidth; x++) {
        for (size_t y=0; y!=mapHeight; y++) {
            if (map_.getBlock(x,y)->visible_)
            	blockSprite.setTexture(map_.getBlock(x,y)->getTexture());
            else
                blockSprite.setTexture(game_.graphicsManager_.getTexture("fow.png"));
            blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
            game_.draw(blockSprite);
        }
    }

    for (Item* i : map_.items)
        if (i->getLocation()->visible_)
            game_.draw(i->getSprite());
    for (Walker* m : map_.monsters)
        if (m->getLocation()->visible_)
            game_.draw(m->getSprite());
    for (Player* p : map_.players) {
        Actor* avatar = p->getActor();
        if (avatar) game_.draw(avatar->getSprite());
    }
}


void World::drawGUI() {
    gui_.clear();
    for (size_t i=0; i < players_.size(); i++)
        gui_.makePlayerInfo(players_[i], i);
    gui_.draw();
}
