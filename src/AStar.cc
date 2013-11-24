#include "AStar.hh"
#include "Direction.hh"

#include <cmath>
#include <queue>
#include <map>
#include <vector>


float AStar::SimpleCostFunction::operator()(MapBlock const* const mb) const {
    if (mb->isPassable()) return 1.0f;
    return AStar::INF;
}


AStar::Node::Node(
        Node* previous,
        MapBlock* const block,
        float cost,
        MapBlock* const target) :
        previous(previous),
        block(block) {
    pastCost = (previous ? previous->pastCost : 0.0f) + cost;
    futureCost = fdim(target->x_, block->x_) + fdim(target->y_, block->y_);
    totalCost = pastCost + futureCost;
}


std::stack<MapBlock*> AStar::find(
        MapBlock* const start,
        MapBlock* const finish,
        CostFunction const costFn,
        bool includeStart, // TODO
        bool includeFinish, // TODO
        float maxCost
) {
    /* Initialization */
    std::priority_queue<Node*, std::vector<Node*>, cmpNodes> pq;
    std::map<MapBlock*, Node*> nodes;
    nodes[start] = new Node(nullptr, start, 0.0, finish);
    pq.push(nodes[start]);

    /* The main loop */
    Node* current;

    while (!pq.empty()) {
        current = pq.top();
        pq.pop();

        /* If we've reached our goal, exit the loop */
        if (current->block == finish) break;

        /* If we've exceeded our allowed cost or there is no path to be found
         * (in which case totalCost >= AStar::INF), exit the loop */
        if (current->totalCost > maxCost) break;

        for (Direction dir : {Direction::NORTH,
                              Direction::EAST,
                              Direction::SOUTH,
                              Direction::WEST}
        ) {
            MapBlock* neighbor = current->block->getBlock(dir);
            auto it = nodes.find(neighbor);
            if (it != nodes.end()) continue; // If already processed, pass
            nodes[neighbor] =
                new Node(current, neighbor, costFn(neighbor), finish);
            pq.push(nodes[neighbor]);
        }
    } // while (!pq.empty())

    std::stack<MapBlock*> solution;

    /* If the search was successful, trace back the path */
    if (current->block == finish) {
        while (current != nullptr) {
            solution.push(current->block);
            current = current->previous;
        }
    }

    /* Cleanup */
    for (auto n : nodes) delete n.second;

    return solution;
}
