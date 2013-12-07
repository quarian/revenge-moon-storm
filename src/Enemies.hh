#ifndef MB2_ENEMIES_HH
#define MB2_ENEMIES_HH

#include <SFML/Graphics.hpp>
#include "AIPlayerSeeker.hh"
#include "GraphicsManager.hh"
#include "Game.hh"
#include "Map.hh"

/* */
class TinyBug : public AIPlayerSeeker {
public:
    TinyBug(Map&, MapBlock*);
};

#endif
