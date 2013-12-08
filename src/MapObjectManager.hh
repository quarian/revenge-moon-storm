#ifndef MB2_MAPOBJECTMANAGER_HH
#define MB2_MAPOBJECTMANAGER_HH

#include "Item.hh"
#include "Enemies.hh"

class Map;
class MapBlock;

namespace MapObjectManager {
    bool place(char, Map&, MapBlock*);
    bool contains(char);
}

#endif
