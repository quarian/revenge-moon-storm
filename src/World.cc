#include <SFML/Graphics.hpp>
#include <algorithm>
#include "World.hh"
#include "Enemies.hh"
#include "GlobalGameInterface.hh"


World::World(
        GameState* parent,
        Map& map,
        std::vector<Player*> players)
        : GameState(parent),
          map_(map),
          players_(players),
          interface_(new GlobalGameInterface(this))
{
    status_text_ = new sf::Text("", game_.graphicsManager_.fonts_["batman"], 16u);
}
          //gui_(WorldGUI(*map.getGame(), 0, 704))  {}

World::World(
        Game& game,
        GameState*& stack,
        Map& map,
        std::vector<Player*> players)
        : GameState(game, stack),
          map_(map),
          players_(players),
          interface_(new GlobalGameInterface(this))
{
    status_text_ = new sf::Text("", game_.graphicsManager_.fonts_["batman"]);
}
          //gui_(WorldGUI(*map.getGame()))  {}


World::~World() {
    delete interface_;
}


void World::init() {
    //interface_ = new GlobalGameInterface(this);
    initKeyboard();
    drawMapObjects();
    for (auto p : map_.players)
        map_.getLOS(p->getActor()->getLocation());
}


void World::resume() {
    initKeyboard();
    drawMapObjects();
    for (auto p : map_.players)
        map_.getLOS(p->getActor()->getLocation());
}


void World::pause() {
    // spawn(new PauseMenu());
}


void World::initKeyboard() {
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(interface_);

    for (Player* p : map_.players)
        game_.eventManager_.registerInterface(p->getInterface());
}


void World::update(float dt) {
    updateAll(dt);
    cull();
    drawMapObjects();
}


void World::cull() {
    // Remove dead items
    std::vector<Item*> deadItems;
    for (Item* i : map_.items)
        if (!i->getAlive())
            deadItems.push_back(i);
    for (Item* i : deadItems) {
        delete i;
        map_.popItem(i);
    }

    // Kill dead monsters
    std::vector<Walker*> deadMonsters;
    for (Walker* w : map_.monsters)
        if (!w->isAlive())
            deadMonsters.push_back(w);
    for (Walker* w : deadMonsters) {
        w->splatter();
        map_.monsters.erase(w);
        delete w;
    }

    // Kill dead Players
    std::vector<Player*> deadPlayers;
    for (Player* p : map_.players) {
        Actor* a = p->getActor();
        if (a && !a->isAlive())
            deadPlayers.push_back(p);
    }
    for (Player* p : deadPlayers) {
        p->getActor()->splatter();
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
    for (Walker* m : map_.monsters)
        m->update(dt);

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
            if (map_.getBlock(x,y)->visible_ || x == 0 || y == 0 || x == mapWidth - 1 || y == mapHeight - 1)
            	blockSprite.setTexture(map_.getBlock(x,y)->getTexture());
            else
                blockSprite.setTexture(game_.graphicsManager_.getTexture("unexplored.png"));
            blockSprite.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
            game_.draw(blockSprite);
        }
    }
    
    drawGUI();

    for (Item* i : map_.items)
        if (i->getLocation()->visible_)
            game_.draw(i->getSprite());
    for (Player* p : map_.players) {
        Actor* avatar = p->getActor();
        if (avatar) {
            game_.draw(avatar->getSprite());
            map_.getLOS(avatar->getLocation());
        }
    }
    for (Walker* m : map_.monsters)
        if (m->getLocation()->visible_)
            game_.draw(m->getSprite());
}


void World::drawGUI() {
    //gui_.clear();
    //
    int y = 44;
    int x = 3;
    std::vector<std::string> item_names = Item::names();
    sf::Sprite icon;
    for (size_t i=0; i < players_.size(); i++) {
        status_text_->setString(players_[i]->getName());
        status_text_->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
        status_text_->setColor(sf::Color::White);
        game_.draw(*status_text_);
        y++;
        for (auto iter = item_names.begin(); iter != item_names.end(); iter++) {
            icon.setTexture(game_.graphicsManager_.getTexture(*iter + "_icon.png"));
            icon.setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
            icon.setScale(0.3, 0.3);
            game_.draw(icon);
            y++;
            std::ostringstream ostr;
            ostr << players_[i]->getInventory().getItemCount(*iter);
            if (!(*iter).compare(players_[i]->getCurrentItem()))
                status_text_->setColor(sf::Color::Red);
            else
                status_text_->setColor(sf::Color::White);
            status_text_->setString(ostr.str());
            status_text_->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
            game_.draw(*status_text_);
            x += 2;
            y--;
        }
        y--;
        status_text_->setColor(sf::Color::White);
        status_text_->setString("Health");
        status_text_->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
        game_.draw(*status_text_);
        y++;
        x++;
        std::ostringstream ostr;
        if (players_[i]->getActor())
            ostr << players_[i]->getActor()->getHealth();
        else
            ostr << 0;
        status_text_->setString(ostr.str());
        status_text_->setColor(sf::Color::White);
        status_text_->setPosition(x*game_.blockSize_.x, y*game_.blockSize_.y);
        game_.draw(*status_text_);
        y--;
        x += 15;
    }

    //    gui_.makePlayerInfo(players_[i], i);
    //gui_.draw();
}
