#ifndef MB2_TERRAIN_HH
#define MB2_TERRAIN_HH

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "GraphicsManager.hh"


/* A manager class that keeps track of all the different TerrainTypes. */
class TerrainManager {
public:
    class InvalidFilenameException;
    class NoSuchTerrainException;

    struct TerrainType;

    /* Constructor: reads terrain data from a file. */
    TerrainManager(GraphicsManager& gfxmgr) : gfxmgr_(gfxmgr) {}

    void init(std::string const&);
    void init(std::istream&);

    ~TerrainManager();

    void parse(std::string&, std::ostream& =std::cerr);

    /* indexing operator, for accessing TerrainType data by character */
    TerrainType const& operator[] (char) const;
    TerrainType const& random() const;

private:
    std::map<char, TerrainType*> terrains_;
    GraphicsManager& gfxmgr_;
};



/* These structs contain information about each different type of terrain. Each
 * individual Terrain struct (which represents a particular terrain instance)
 * holds a reference to the relevant TerrainType.
 */
struct TerrainManager::TerrainType {
    TerrainType(char signifier,
                sf::Texture& texture,
                float initStr,
                float degStr,
                TerrainType const* target
          ) : signifier(signifier),
              texture(texture),
              initialToughness(initStr),
              degenerationToughness(degStr),
              degenerationTarget(target),
              diggable(degenerationTarget != nullptr),
              passable(initialToughness == 0) {
}

    const char signifier;
    const sf::Texture& texture;
    const float initialToughness;
    const float degenerationToughness;
    TerrainType const* degenerationTarget;

    const bool diggable;
    const bool passable;
};


/* Every MapBlock will hold one of these structs to keep track of the diggable
 * terrain.
 */
struct Terrain {
    Terrain(TerrainManager::TerrainType const& tt) :
            type(&tt), toughness(tt.initialToughness) {}
    
    TerrainManager::TerrainType const* type;
    float toughness;

    /* Take "digging-type" damage. raze() "digs out" the square, that is,
     * degenerates the terrain type until it can't be degenerated any further.
     */
    float takeDamage(float);
    void raze();
};


/* An exception to signal that opening the terrain.cfg (or equivalent) file
 * failed.
 */
class TerrainManager::InvalidFilenameException {
public:
    InvalidFilenameException(std::string s)
            : e("could not open terrain cfg file " + s) {}
    std::string e;
};


/* An exception to signal that the program tried to access a terrain-type sign
 * that does not exist.
 */
class TerrainManager::NoSuchTerrainException {
public:
    NoSuchTerrainException(char c)
            : e("attempted to access nonexisting terrain specifier " + c) {}
    std::string e;
};

#endif
