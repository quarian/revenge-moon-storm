#include "Terrain.hh"


void TerrainManager::init(std::string const& filename) {
    std::ifstream ifs(filename, std::ios::in);
    if (!ifs) throw InvalidFilenameException(filename);
    init(ifs);
}


void TerrainManager::init(std::istream& is) {
    do {
        std::string s;
        std::getline(is, s);
        parse(s);
    } while (!is.eof());
}


TerrainManager::~TerrainManager() {
    for (auto t : terrains_)
        delete t.second;
}


void TerrainManager::parse(std::string& s, std::ostream& err) {
    /* Failure and skip cases */
    if (s.size() == 0) return;
    if (s.size() == 1) {
        err << "TerrainManager: line of length 1 in configuration file" << std::endl;
        return;
    }
    if (s.substr(0,2) == "##") return;

    /* Attempt to read the line */
    std::istringstream is(s);
    std::string signRaw; char signifier;
    std::string name, graphic;
    float initStr, degStr;
    std::string targetRaw; char target;
    is >> signRaw >> name >> graphic >> initStr >> degStr >> targetRaw;

    if (!is) { // if read failed
        err << "TerrainManager: could not parse line in configuration file" << std::endl;
        return;
    } else if (signRaw.size() != 1 && signRaw != "NONE") {
        err << "TerrainManager: improper character signifier " + signRaw << std::endl;
        return;
    } else if (targetRaw.size() != 1 && targetRaw != "NONE" && targetRaw != "NULL") {
        err << "TerrainManager: improper character signifier " + targetRaw << std::endl;
        return;
    }

    if (signRaw.size() == 1) signifier = signRaw[0];
    else if (signRaw == "NONE") signifier = ' ';
    else {
        err << "TerrainManager: improper character signifier " + signRaw << std::endl;
        return;
    }
    if (targetRaw.size() == 1) target = targetRaw[0];
    else if (targetRaw == "NONE") target = ' ';
    else if (targetRaw == "NULL") target = '\0';
    else {
        err << "TerrainManager: improper character signifier " + targetRaw << std::endl;
        return;
    }

    if (target != '\0') {
        auto it = terrains_.find(target);
        if (it == terrains_.end()) {
            err << "TerrainManager: terrain \"" + signRaw + "\" can't find degeneration target \"" + targetRaw + "\"" << std::endl;
            return;
        }
        terrains_[signifier] = new TerrainType(signifier, gfxmgr_.getTexture(graphic), initStr, degStr, it->second);
    } else {
        terrains_[signifier] = new TerrainType(signifier, gfxmgr_.getTexture(graphic), initStr, degStr, nullptr);
    }
}


TerrainManager::TerrainType const& TerrainManager::operator[] (char c) const {
    auto it = terrains_.find(c);
    if (it != terrains_.end()) 
        return *it->second;
    else
        throw NoSuchTerrainException(c);
}


float Terrain::takeDamage(float dmg) {
    if (type->diggable) {
        toughness -= dmg;
        while (toughness < type->degenerationToughness) {
            type = type->degenerationTarget;
            if (!type->diggable) break;
        }
    }
    return toughness;
}


void Terrain::raze() {
    while (type->diggable)
        type = type->degenerationTarget;
}
