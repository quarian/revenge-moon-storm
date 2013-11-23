#include "AStar.hh"
#include <cmath>

AStar::AStar(
        MapBlock* const start,
        MapBlock* const finish,
        bool frontinc=true,
        bool backinc=true,
        int limit=-1) :
        start_(start),
        finish_(finish),
        front_inclusive_(frontinc),
        back_inclusive_(backinc),
        limit_(limit) {
    std::priority_queue<Node> pq;
    push(pq, null, start);

    MapBlock* current;
    do {
        if (pq.empty()) break;
        current = pq.top().current;
        pq.pop();
        push(pq, current, current->getBlock(Direction::NORTH));
        push(pq, current, current->getBlock(Direction::EAST));
        push(pq, current, current->getBlock(Direction::SOUTH));
        push(pq, current, current->getBlock(Direction::WEST));
    } while (current != finish_);
}


void AStar::push(std::priority_queue<Node> pq, MapBlock* previous, MapBlock* current) {
    if (!current->isPassable()) return;
    auto it = nodes_.find(current);
    if (it == nodes_.end()) {
        Node n(nodes_, previous, current, finish_);
        nodes_[current] = n;
        pq.push(n);
    }
}


std::stack<MapBlock*> AStar::trace() {
    std::stack<MapBlock*> path;
    
    auto it = nodes_.find(finish_);
    if (it == nodes_.end()) return path;
    
    Node current = *it;
    if (back_inclusive_) path.push_back(finish_);
    while (current = current.previous)
        path.push_back(current.current);
    if (!front_inclusive_) path.pop();
}


AStar::Node::Node(
        std::map<Node>& nodes,
        MapBlock* previous,
        MapBlock* current,
        MapBlock* goal) :
        nodes(nodes),
        previous(previous),
        current(current) {

    g = nodes[previous].g + 1;
    h = manhattanDistance(current, previous);
    d = g + h;
}


int AStar::Node::manhattanDistance(MapBlock* a, mapBlock* b) {
    return fdim(a->x_, b->x_) + fdim(a->y_, b->y_);
}

    
bool AStar::Node::operator<(Node const& other) const {
    return d > other.d;
}
