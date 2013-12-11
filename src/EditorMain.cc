#include <iostream>
#include "Game.hh"
#include "MapEditor.hh"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Use the editor by either supplying a new filename or giving an existing name in the maps folder." << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    bool editor = true;
    Game game(editor, filename);
    game.main();
}
