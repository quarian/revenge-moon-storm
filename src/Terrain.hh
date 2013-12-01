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
    struct Terrain;

    /* Constructor: reads terrain data from a file. */
    TerrainManager(std::string const&, GraphicsManager*);
    TerrainManager(std::istream&, GraphicsManager*);

    void parse(std::string&, std::ostream& =std::cerr);

    /* indexing operator, for accessing TerrainType data by character */
    TerrainType& operator[] (char);

private:
    std::map<char, TerrainType> terrains_;
    GraphicsManager* gfxmgr_;
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
              degenerationTarget(target) {
}

    char signifier;
    sf::Texture& texture;
    float initialToughness;
    float degenerationToughness;
    TerrainType const* degenerationTarget;
};


/* Every MapBlock will hold one of these structs to keep track of the diggable
 * terrain.
 */
struct TerrainManager::Terrain {
    Terrain(TerrainType const& tt) :
            type(tt), toughness(tt.initialToughness) {}
    
    TerrainType const& type;
    float toughness;

    float takeDamage(float);
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
