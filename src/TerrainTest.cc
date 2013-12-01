#include <SFML/Graphics.hpp>
#include <cmath>
#include <cassert>
#include <map>

#include "tests.hh"
#include "Direction.hh"
#include "GraphicsManager.hh"
#include "Animation.hpp"

bool TerrainTest1(std::ostream& os) {
    os << "UNIT TEST: classes TerrainManager, TerrainType" << std::endl;

    WindowManager window;
    sf::Vector2f blockSize;
    std::map<std::string, Animation> animations;
    std::map<std::string, sf::Texture> textures;
    GraphicsManager gfxmgr(window, blockSize, textures, animations);
    gfxmgr.InitializeGraphics(".");

    /* SECTION 0 */
    os << "TEST 0: Initialization...";

    TerrainManager terramgr("terrain.cfg", &gfxmgr);

    os << " OK" << std::endl;


    /* SECTION 1 */
    os << "TEST 1: Testing that all types have been loaded correctly...";

    assert(terramgr[' '].signifier == ' ');
    assert(terramgr['W'].signifier == 'W');
    assert(terramgr['S'].signifier == 'S');
    assert(terramgr['#'].signifier == '#');
    // try { terramgr['z']; } catch (TerrainManager::NoSuchTerrainException) {}

    os << " OK" << std::endl;


    return true;
}
