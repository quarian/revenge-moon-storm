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
            // mb->enter(bug);
            return true;
            break;
        }
        case 'X': {
            auto bug = new GreenBug(map, mb);
            map.monsters.insert(bug);
            // mb->enter(bug);
            return true;
            break;
        }
        case 'L': {
            auto lurker = new Lurker(map, mb);
            map.monsters.insert(lurker);
            // mb->enter(lurker);
            return true;
            break;
        }
        case 'Q': {
            auto queen = new ScarabQueen(map, mb);
            map.monsters.insert(queen);
            // mb->enter(queen);
            return true;
            break;
        }

        /* TREASURES */
        case '1': {
            new Treasure(map, mb, "Metal Scrap", 10);
            return true;
            break;
        }
        case '2':{ 
            new Treasure(map, mb, "Gunpowder", 25);
            return true;
            break;
        }
        case '3': {
            new Treasure(map, mb, "Explosives", 50);
            return true;
            break;
        }
        case '4': {
            new Treasure(map, mb, "Crate of IEDs", 100);
            return true;
            break;
        }
        case '5': {
            new Treasure(map, mb, "Military Box", 250);
            return true;
            break;
        }

        //WEAPON BOX
        case 'B': {
            new Weaponbox(map, mb);
            return true;
            break;
        }


        /* OTHER */
        case '&':
            new BloodSplatter(map, mb);
            return true;
            break;

        /* DEFAULT */
        default: {
            return false;
        }
    }

    return false;
}


bool MapObjectManager::contains(char c) {
    return (
            c == 'x' ||
            c == 'X' ||
            c == 'L' ||
            c == 'Q' ||

            c == '1' ||
            c == '2' ||
            c == '3' ||
            c == '4' ||
            c == '5' ||

            c == 'B' ||

            c == '&'
           );
}
