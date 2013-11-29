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

    /* SECTION 2 */
    os << "TEST 2: straight lines...";

    st = AStar::find(map.getBlock(8,6), map.getBlock(19,6));
    assert(st.size() == 12);
    assert(st.top() == map.getBlock(8,6)); st.pop();
    assert(st.top() == map.getBlock(9,6)); st.pop();
    assert(st.top() == map.getBlock(10,6)); st.pop();
    assert(st.top() == map.getBlock(11,6)); st.pop();
    assert(st.top() == map.getBlock(12,6)); st.pop();
    assert(st.top() == map.getBlock(13,6)); st.pop();
    assert(st.top() == map.getBlock(14,6)); st.pop();
    assert(st.top() == map.getBlock(15,6)); st.pop();
    assert(st.top() == map.getBlock(16,6)); st.pop();
    assert(st.top() == map.getBlock(17,6)); st.pop();
    assert(st.top() == map.getBlock(18,6)); st.pop();
    assert(st.top() == map.getBlock(19,6)); st.pop();

    st = AStar::find(map.getBlock(28,10), map.getBlock(28,20));
    assert(st.size() == 11);
    assert(st.top() == map.getBlock(28,10)); st.pop();
    assert(st.top() == map.getBlock(28,11)); st.pop();
    assert(st.top() == map.getBlock(28,12)); st.pop();
    assert(st.top() == map.getBlock(28,13)); st.pop();
    assert(st.top() == map.getBlock(28,14)); st.pop();
    assert(st.top() == map.getBlock(28,15)); st.pop();
    assert(st.top() == map.getBlock(28,16)); st.pop();
    assert(st.top() == map.getBlock(28,17)); st.pop();
    assert(st.top() == map.getBlock(28,18)); st.pop();
    assert(st.top() == map.getBlock(28,19)); st.pop();
    assert(st.top() == map.getBlock(28,20)); st.pop();

    os << " OK" << std::endl;

    /* SECTION 3 */
    os << "TEST 3: an unambiguous solution to a partially-blocked path...";

    st = AStar::find(map.getBlock(21,17), map.getBlock(23,17));
    assert(st.size() == 5);
    assert(st.top() == map.getBlock(21,17)); st.pop();
    assert(st.top() == map.getBlock(21,18)); st.pop();
    assert(st.top() == map.getBlock(22,18)); st.pop();
    assert(st.top() == map.getBlock(23,18)); st.pop();
    assert(st.top() == map.getBlock(23,17)); st.pop();

    st = AStar::find(map.getBlock(43,13), map.getBlock(35,9));
    assert(st.size() == 13);
    assert(st.top() == map.getBlock(43,13)); st.pop();
    assert(st.top() == map.getBlock(43,12)); st.pop();
    assert(st.top() == map.getBlock(43,11)); st.pop();
    assert(st.top() == map.getBlock(43,10)); st.pop();
    assert(st.top() == map.getBlock(43,9)); st.pop();
    assert(st.top() == map.getBlock(42,9)); st.pop();
    assert(st.top() == map.getBlock(41,9)); st.pop();
    assert(st.top() == map.getBlock(40,9)); st.pop();
    assert(st.top() == map.getBlock(39,9)); st.pop();
    assert(st.top() == map.getBlock(38,9)); st.pop();
    assert(st.top() == map.getBlock(37,9)); st.pop();
    assert(st.top() == map.getBlock(36,9)); st.pop();
    assert(st.top() == map.getBlock(35,9)); st.pop();

    os << " OK" << std::endl;

    /* SECTION 4 */
    os << "TEST 4: not including start or finish...";

    st = AStar::find(map.getBlock(21,17), map.getBlock(23,17), AStar::SimpleCostFunction(), true, false);
    assert(st.size() == 4);
    assert(st.top() == map.getBlock(21,17)); st.pop();
    assert(st.top() == map.getBlock(21,18)); st.pop();
    assert(st.top() == map.getBlock(22,18)); st.pop();
    assert(st.top() == map.getBlock(23,18)); st.pop();

    st = AStar::find(map.getBlock(21,17), map.getBlock(23,17), AStar::SimpleCostFunction(), false, true);
    assert(st.size() == 4);
    assert(st.top() == map.getBlock(21,18)); st.pop();
    assert(st.top() == map.getBlock(22,18)); st.pop();
    assert(st.top() == map.getBlock(23,18)); st.pop();
    assert(st.top() == map.getBlock(23,17)); st.pop();

    st = AStar::find(map.getBlock(21,17), map.getBlock(23,17), AStar::SimpleCostFunction(), false, false);
    assert(st.size() == 3);
    assert(st.top() == map.getBlock(21,18)); st.pop();
    assert(st.top() == map.getBlock(22,18)); st.pop();
    assert(st.top() == map.getBlock(23,18)); st.pop();

    os << " OK" << std::endl;

    /* SECTION 5 */
    os << "TEST 5: edge cases...";

    st = AStar::find(map.getBlock(21,17), map.getBlock(21,17), AStar::SimpleCostFunction(), false, false);
    assert(st.size() == 0);

    st = AStar::find(map.getBlock(21,17), map.getBlock(21,18), AStar::SimpleCostFunction(), false, false);
    assert(st.size() == 0);

    os << " OK" << std::endl;

    return true;
}
