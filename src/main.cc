#include "Map.hh"
#include "Walker.hh"

int main() {
    Map map;
    MapBlock mb(1,1, "#");
    map.loadFromFile("map.txt");
    map.printMap();
}
