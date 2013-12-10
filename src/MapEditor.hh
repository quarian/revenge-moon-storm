#ifndef MB2_MAP_EDITOR_HH
#define MB2_MAP_EDITOR_HH

#include "GameState.hh"
#include "Map.hh"
#include "EditorInterface.hh"


class MapEditor : public GameState {
public:
     MapEditor(GameState*);
     MapEditor(Game&, GameState*&);

    void update(float);
    void init();
    void resume();

    void handleInput(unsigned x, unsigned y);
    void setBrush(char b) { brush_ = b; }
    void saveMap();

private:
    Map map_;
    void draw();
    EditorInterface interface_;
    char brush_;
};


#endif
