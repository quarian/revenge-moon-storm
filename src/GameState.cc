#include "GameState.hh"

GameState::GameState(Game& game, GameState*& stack)
        : game_(game),
        stack_(stack),
        parent_(stack),
        alive_(true) {}


GameState::GameState(GameState* parent)
        : game_(parent->game_),
        stack_(parent->stack_),
        parent_(parent),
        alive_(true) {}


GameState::~GameState() {
    stack_ = parent_;
}


void GameState::spawn(GameState* state) {
    stack_ = state;
    state->init();
}


void GameState::terminate() {
    alive_ = false;
}
