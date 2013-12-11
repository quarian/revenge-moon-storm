#ifndef MB2_MAP_EDITOR_HH
#define MB2_MAP_EDITOR_HH

#include "GameState.hh"
#include "Map.hh"
#include "EditorInterface.hh"


class MapEditor : public GameState {
friend class EditorInterface;
public:
     MapEditor(GameState*);
     MapEditor(Game&, GameState*&);

    void update(float);
    void init();
    void resume();

    void handleInput(unsigned x, unsigned y);
    void setBrush(char b) { brush_ = b; }
    void saveMap();
    char getBrush() { return brush_; }

private:
    Map map_;
    void draw();
    EditorInterface interface_;
    char brush_;
    sf::Text* t1;
    sf::Text* t2;
    sf::Text* t3;
    sf::Text* t4;
    sf::Text* t5;
    sf::Font font;

};


#endif
