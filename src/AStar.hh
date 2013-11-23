#ifndef MB2_ASTAR_HH
#define MB2_ASTAR_HH

#include "MapBlock.hh"
#include "Direction.hh"

#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <set>

/* A* pathfinding algorithm
 *
 * as per: https://en.wikipedia.org/wiki/A*_search_algorithm
 *
 * This class is meant to be instantiated whenever a query gets made.
 */
class AStar {
public:
    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  MapBlock* const     starting MapBlock
     *  MapBlock* const     target, or final MapBlock
     *  bool                include the starting block in the path trace?
     *  bool                include the target block in the path trace?
     *  int                 distance limit; search-no-farther-than (-1 if unlimited)
     */
    AStar(MapBlock* const, MapBlock* const, bool=true, bool=true, int=-1);

    std::stack<MapBlock*> trace();

private:
    bool push(std::priority_queue<Node>, MapBlock*, MapBlock*);

    class Node;

    MapBlock const* start_;
    MapBlock const* finish_;

    const bool front_inclusive_;
    const bool back_inclusive_;
    int limit_;

    std::map<MapBlock*, Node> nodes_;
};


class AStar::Node {
public:
    MapBlock* previous;  // preceding node
    MapBlock* current;   // corresponding block

    const int d; // expected total cost
    const int g; // past path-cost 
    const int h; // expected future path-cost

    /* Constructor
     *
     * PARAMETERS
     * ==========
     *  std::map<Node>&     a container of Nodes that have been processed
     *  MapBlock*           the preceding MapBlock
     *  MapBlock*           the MapBlock that this node corresponds to
     *  MapBlock*           target, or final MapBlock
     */
    Node(std::map<Node>&, MapBlock*, MapBlock*, MapBlock*);
    
    bool operator<(Node const&) const;

private:
    int manhattanDistance(MapBlock*, MapBlock*);

    std::map<Node>& nodes;
};

#endif
