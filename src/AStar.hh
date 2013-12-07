#ifndef MB2_ASTAR_HH
#define MB2_ASTAR_HH

#include "MapBlock.hh"

#include <functional>
#include <deque>

/* A* pathfinding algorithm
 *
 * as per: https://en.wikipedia.org/wiki/A*_search_algorithm
 *
 * This class is meant to be instantiated whenever a query gets made.
 */

namespace AStar {
    /* A constant to represent "Infinity" -- just a constant to signify that
     * some path is not allowed (blocked). */
    const float INF = 1e12f;


    /* A class for function objects that act as cost functions for the search
     * algorithm.
     *
     * The base class CostFunction finds a path that minimizes the Manhattan
     * distance traveled, ignoring passability and everything else.
     *
     * The inheriting SimpleCostFunction class is the default cost function,
     * which simply ranks all passable squares as 1 and non-passable squares
     * as INF.
     *
     * The inheriting WalkingDiggingCostFunction class assigns some fixed cost
     * to walking into a square if it is passable, or if it is not passable
     * but is diggable, assigns the cost to digCostBase + digCost * block str.
     */
    class CostFunction {
    public:
        virtual float operator()(MapBlock const* const) const {
            return 1;
        }
    };

    class SimpleCostFunction : public CostFunction {
    public:
        float operator()(MapBlock const* const) const;
    };

    class WalkingDiggingCostFunction : public CostFunction {
    public:
        const float walkCost, digCostBase, digCost;
        const std::function<bool(MapBlock const* const)> pred;
        WalkingDiggingCostFunction(
                float walkCost,
                float digCostBase,
                float digCost,
                std::function<bool(MapBlock const* const)> pred =
                        [](MapBlock const* const mb){ return true; }
                ) :
            walkCost(walkCost),
            digCostBase(digCostBase),
            digCost(digCost),
            pred(pred) {}

        float operator()(MapBlock const* const) const;
    };

    
    /* The A* search algorithm itself. Parameters:
     *
     *  MapBlock const*     start
     *  MapBlock const*     finish
     *  CostFunction const  cost function
     *  bool                include `start` in the returned stack?
     *  bool                include `finish` in the returned stack?
     *  float               a maximum cost -- if this is exceeded, aborts
     *
     * Return value: stack of MapBlock pointers.
     */
    std::deque<MapBlock*> find(
            MapBlock* const,
            MapBlock* const,
            CostFunction const& =SimpleCostFunction(),
            bool=true,
            bool=true,
            float=INF);


    /* A struct to represent one search node. */
    struct Node {
        Node* previous;
        MapBlock* const block;
        float pastCost, futureCost, totalCost;

        Node(Node*, MapBlock* const, float, MapBlock* const);

        bool operator< (Node const&);
    };


    /* A function pointer to compare nodes from pointers in the
     * std::priority_queue. */
    class cmpNodes {
    public:
        bool operator()(Node* const& a, Node* const& b) const {
            return a->totalCost > b->totalCost;
        }
    };
}

#endif
