#ifndef MB2_DUMMYGAMESTATE_HH
#define MB2_DUMMYGAMESTATE_HH

#include "GameState.hh"


class DummyGameState : public GameState {
public:
    DummyGameState(GameState* parent) :
            GameState(parent) {}

    DummyGameState(Game& game, GameState*& stack) :
            GameState(game, stack) {}

    void update(float) {}

    void init() { terminate(); }
    void resume() {}
};

#endif
