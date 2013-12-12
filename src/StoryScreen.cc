#include "StoryScreen.hh"

#include <vector>

StoryInterface::StoryInterface(StoryScreen* story) : story_(story) {

}

bool StoryInterface::parse(sf::Event& evt) {
    if (evt.type == sf::Event::KeyPressed) {
        if (story_->passed_) {
            story_->kill();
            return true;
        }
    }
    return false;
}

StoryScreen::StoryScreen(
        GameState* parent,
        std::vector<std::string> story) :
        GameState(parent),
        story_(story),
        storyfont_(parent->getGame().graphicsManager_.fonts_["batman"]) {
    passed_ = false;
}


StoryScreen::StoryScreen(
        Game& game,
        GameState*& stack,
        std::vector<std::string> story ) :
        GameState(game, stack),
        story_(story),
        storyfont_(game.graphicsManager_.fonts_["batman"]) {
    passed_ = false;
}

StoryScreen::~StoryScreen() {
    //No text belongs here
}

void StoryScreen::init() {
    initKeyboard();

    storytext_ = new sf::Text();
    storytext_->setFont(storyfont_);
    storytext_->setCharacterSize(20);
    game_.graphicsManager_.texts_["storytext"] = storytext_;
}

void StoryScreen::update(float dt) {
    if (!passed_)
        timer_ += dt;
    if (timer_ > 1.0f) 
        passed_ = true;

    draw();
}

void StoryScreen::draw() {

    //The story, line by line, lines centered
    storytext_->setCharacterSize(18);
    int y = 0;
    for (auto line : story_) {
        storytext_->setString(line);
        storytext_->setPosition(1024/2 - storytext_->getGlobalBounds().width/2, 120 + y*26);

        game_.draw(*storytext_);
        y++;
    }


    //Press any key...
    if (passed_) {
        storytext_->setCharacterSize(14);
        storytext_->setString("Press any key...");
        storytext_->setPosition(1024/2 - storytext_->getGlobalBounds().width/2, 768 - 100);
        game_.draw(*storytext_);
    }

}

void StoryScreen::initKeyboard() {
    game_.eventManager_.clearInterfaces();
    game_.eventManager_.registerInterface(new StoryInterface(this));
}
