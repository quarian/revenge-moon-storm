#include "GameState.hh"

GameState::GameState(Game& game, GameState*& stack)
        : game_(game), stack_(stack), parent_(stack) {}


GameState::GameState(GameState* parent)
        : game_(parent->game_), stack_(parent->stack_), parent_(parent) {}


void GameState::spawn(GameState* state) {
    stack_ = state;
    state->init();
}


void GameState::terminate() {
    stack_ = parent_;
    if (parent_)
        parent_->resume();
}


void GameState::kill() {
    stack_ = parent_;
}
