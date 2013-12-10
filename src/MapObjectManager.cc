#include "MapObjectManager.hh"
#include "Map.hh"
#include "MapBlock.hh"
#include "Item.hh"

bool MapObjectManager::place(char signifier, Map& map, MapBlock* mb) {
    switch (signifier) {
        /* MONSTERS */
        case 'x': {
            auto bug = new TinyBug(map, mb);
            map.monsters.insert(bug);
            mb->enter(bug);
            return true;
            break;
        }
        case 'X': {
            auto bug = new GreenBug(map, mb);
            map.monsters.insert(bug);
            mb->enter(bug);
            return true;
            break;
        }

        /* TREASURES */
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
            break; // TODO: treasueres here


        /* OTHER */
        case '&':
            new BloodSplatter(map, mb);
            break;

        /* DEFAULT */
        default: {
            return false;
        }
    }
}


bool MapObjectManager::contains(char c) {
    return (
            c == 'x' ||
            c == 'X' ||

            c == '1' ||
            c == '2' ||
            c == '3' ||
            c == '4' ||
            c == '5' ||

            c == '&'
           );
}
