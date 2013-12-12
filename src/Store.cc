#include "Store.hh"
#include "StoreInterface.hh"
#include "Item.hh"

#include <map>
#include <climits>
#include <iostream>

//The constructors for the store. The store will handle one player at a time
//and the parent state will call the store again for the next player etc.

Store::Store(
        GameState* parent,
        Player* player ) :
      GameState(parent),
      player_(player),
      storefont_(parent->getGame().graphicsManager_.fonts_["batman"]) {}


Store::Store(
        Game& game,
        GameState*& stack,
        Player* player ) :
      GameState(game, stack),
      player_(player),
      storefont_(game.graphicsManager_.fonts_["batman"]) {}

Store::~Store() {
    //The text CAN NOT be deleted here, because it will segfault (bug in SFML)
}

void Store::init() {
    initKeyboard();

    selection_ = 0;
    selx_ = 0;
    sely_ = 0;
    selmax_ = Item::names().size();
    selxmax_ = 2;
    selymax_ = selmax_ / selxmax_;

    storetext_ = new sf::Text();
    storetext_->setFont(storefont_);
    storetext_->setCharacterSize(20);
    //GM assumes ownership of sf::Text pointers
    //because they cant be so easily destructed :C
    game_.graphicsManager_.texts_["storetext"] = storetext_;
}

void Store::update(float) {
    //if (selection_ != -1) {
        selx_ = selection_ % selxmax_;
        sely_ = selection_ / selxmax_;
    //}
    draw();
}

void Store::draw() {
    //SPRITES

    sf::Sprite storetitle;
    storetitle.setTexture(game_.graphicsManager_.getTexture("workshop_title.png"));
    storetitle.setPosition(1024/2 - storetitle.getGlobalBounds().width/2, 40);
    game_.draw(storetitle);

    //Draw red rectangle at selection
    sf::RectangleShape sel_rect(sf::Vector2f(64, 64));
    sel_rect.setFillColor(sf::Color::Transparent);
    sel_rect.setOutlineColor(sf::Color::Red);
    sel_rect.setOutlineThickness(1.0f);
    if (selection_ != -1) {
        sel_rect.setSize(sf::Vector2f(64, 64));
        sel_rect.setPosition(3*64 + selx_*64, 260 + sely_*64);
    } else {
        sel_rect.setSize(sf::Vector2f(156, 48));
        sel_rect.setPosition(1024/2 - 160/2, 160);
    }
    game_.draw(sel_rect);

    sf::Sprite icon;
    auto items = Item::names();
    for (unsigned int i = 0; i < items.size(); i++) {
        icon.setTexture(game_.graphicsManager_.getTexture(items[i] + "_icon.png"));
        icon.setPosition(3*64 + (i%selxmax_)*64 + 8, 260+(i/selxmax_)*64 + 8);
        game_.draw(icon);
    }

    sf::Sprite done;
    done.setTexture(game_.graphicsManager_.getTexture("done_button.png"));
    done.setPosition(1024/2 - done.getGlobalBounds().width/2, 160);
    game_.draw(done);

    //TEXT

    //player scrap amount
    storetext_->setCharacterSize(20);
    std::stringstream convert;
    convert << player_->getInventory().getGold();
    storetext_->setString("Scrap: " + convert.str());
    storetext_->setPosition(590, 400);
    storetext_->setColor(sf::Color::White);
    game_.draw(*storetext_);

    //clear the string stream for reuse
    convert.str(std::string());
    convert.clear();

    convert << getPrice(getSelection());
    storetext_->setString("Cost: " + convert.str());
    storetext_->setPosition(590, 450);
    game_.draw(*storetext_);

    convert.str(std::string());
    convert.clear();

    convert << player_->getName();
    storetext_->setString("Player: " + convert.str());
    storetext_->setPosition(590, 330);
    game_.draw(*storetext_);
}

void Store::initKeyboard() {
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(new StoreInterface(this));
}

void Store::keyDown(Direction dir) {
    if (dir == Direction::EAST) {
        selection_++;
        if (selection_ == selmax_) {
            selection_ = selmax_ - 1;
        }
    } else if (dir == Direction::WEST) {
        selection_--;
        if (selection_ < 0) {
            selection_ = 0;
        }
    } else if (dir == Direction::NORTH) {
        selection_ = -1;
    } else if (dir == Direction::SOUTH) {
        selection_ = 0;
    }

}

void Store::buyItem() {
    if (selection_ != -1) {
        if (player_->getInventory().getGold() >= getPrice(getSelection())) {
            player_->getInventory().decreaseGold(getPrice(getSelection()));
            player_->getInventory().addItem(getSelection());
        }
    } else {
        terminate(); //Exit the store
    }
}

void Store::sellItem() {
    if (selection_ != -1) {
        if (player_->getInventory().getItemCount(getSelection()) > 0) {
            player_->getInventory().increaseGold(getPrice(getSelection()));
            player_->getInventory().sellItem(getSelection());
        }
    } else {
        //Nothing
    }
}

int Store::getPrice(std::string item) const {
    std::map<std::string, int> prices;
    prices[""] = 0;
    prices["Small Bomb"] = 100; //TODO CHANGE THESE
    prices["Large Bomb"] = 100;
    prices["Crucifix Bomb"] = 100;
    prices["Large Crucifix Bomb"] = 100;
    prices["Flamer"] = 100;
    prices["Mine"] = 100;

    return prices[item];
}

std::string Store::getSelection() const {
    if (selection_ >= 0)
        return Item::names()[selection_];
    return "";
}