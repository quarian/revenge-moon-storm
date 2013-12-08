#include "MapObjectManager.hh"
#include "Map.hh"
#include "MapBlock.hh"

bool MapObjectManager::place(char signifier, Map& map, MapBlock* mb) {
    switch (signifier) {
        /* MONSTERS */
        case 'x': {
            auto bug = new TinyBug(map, mb);
            map.monsters.insert(bug);
            mb->enter(bug);
            return true;
        }

        /* TREASURES */


        /* DEFAULT */
        default: {
            return false;
        }
    }
}


bool MapObjectManager::contains(char c) {
    return (
            c == 'x'
           );
}
