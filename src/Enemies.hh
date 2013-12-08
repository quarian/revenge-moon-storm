#ifndef MB2_ENEMIES_HH
#define MB2_ENEMIES_HH

#include <SFML/Graphics.hpp>
#include "AIPlayerSeeker.hh"
#include "GraphicsManager.hh"
#include "Game.hh"
#include "Map.hh"

/* Tiny Bug
 *
 * Agile little pests with low damage and health. */
class TinyBug : public AIPlayerSeeker {
public:
    TinyBug(Map&, MapBlock*);
    void splatter();
};

class GreenBug : public AIPlayerSeeker {
public:
    GreenBug(Map&, MapBlock*);
    void splatter();
};


#endif
