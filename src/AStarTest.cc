#include "tests.hh"
#include "Direction.hh"

#include <cmath>
#include <cassert>
#include <stack>

bool AStarTest1(std::ostream& os) {
    os << "UNIT TEST: namespace AStar" << std::endl;

    Map map;
    map.loadFromFile("map.txt");
    MapBlock* mb = map.getBlock(1,1);

    /* SECTION 0 */
    os << "TEST 0: self to self should include exactly self...";

    std::stack<MapBlock*> st = AStar::find(mb, mb);
    assert(st.size() == 1);
    assert(st.top() == mb);

    os << " OK" << std::endl;

    /* SECTION 1 */
    os << "TEST 1: adjacent MapBlocks should return simple 1,2's...";

    // EAST
    st = AStar::find(map.getBlock(1,1), map.getBlock(1,2));
    assert(st.size() == 2);
    assert(st.top() == map.getBlock(1,1)); st.pop();
    assert(st.top() == map.getBlock(1,2));

    // WEST
    st = AStar::find(map.getBlock(1,2), map.getBlock(1,1));
    assert(st.size() == 2);
    assert(st.top() == map.getBlock(1,2)); st.pop();
    assert(st.top() == map.getBlock(1,1));

    // NORTH
    st = AStar::find(map.getBlock(2,1), map.getBlock(1,1));
    assert(st.size() == 2);
    assert(st.top() == map.getBlock(2,1)); st.pop();
    assert(st.top() == map.getBlock(1,1));

    // SOUTH
    st = AStar::find(map.getBlock(1,1), map.getBlock(2,1));
    assert(st.size() == 2);
    assert(st.top() == map.getBlock(1,1)); st.pop();
    assert(st.top() == map.getBlock(2,1));

    os << " OK" << std::endl;

    return true;
}
