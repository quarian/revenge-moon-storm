#ifndef __Minebombers__Drawable__
#define __Minebombers__Drawable__

#include "AnimatedSprite.hpp"
#include "MapBlock.cc"
#include "GraphicsManager.hh"
#include "Walker.hh"
#include "Item.hh"

// Non animated drawables
class staticDrawable {
public:
    staticDrawable(std::string content, sf::Sprite* ptr) : blockContent_(content), spritePtr_(ptr)  {}
    sf::Sprite* getSpritePtr() {return spritePtr_;}
    
private:
    std::string blockContent_;
    sf::Sprite* spritePtr_;
    
};

class animatedWalker {
public:
    animatedWalker(Walker* w, AnimatedSprite* s) : walkerPtr_(w), spritePtr_(s) { }
    AnimatedSprite* getSpritePtr() {return spritePtr_;}

private:
    Walker* walkerPtr_;
    AnimatedSprite* spritePtr_;
    
};

class animatedItem {
public:
    animatedItem(Item* i, AnimatedSprite* s) : itemPtr_(i), spritePtr_(s)  {}
    AnimatedSprite* getSpritePtr() {return spritePtr_;}

private:
    Item* itemPtr_;
    AnimatedSprite* spritePtr_;
    
};



#endif
