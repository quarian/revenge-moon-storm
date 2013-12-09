#include "Map.hh"
#include "AStar.hh"


std::deque<MapBlock*> Map::randomWalk(
        MapBlock* mb, size_t length, bool frontInclusive) {
    return randomWalk(mb, length, frontInclusive,
            [](MapBlock* mb){ return mb->isPassable(); });
}

std::deque<MapBlock*> Map::randomWalk(
        MapBlock* mb, size_t length, bool frontInclusive,
        std::function<bool(MapBlock*)> pred) {
    std::deque<MapBlock*> result;
    if (length < 1) return result;
    if (frontInclusive) {
        result.push_back(mb);
        length -= 1;
    }
    while (length --> 0) {
        mb = mb->getRandomNeighbor(pred);
        if (!mb) break;
        result.push_back(mb);
    }
    return result;
}

std::deque<MapBlock*> Map::randomDestinationWalk(
        MapBlock* mb, size_t length, bool frontInclusive) {
    return randomDestinationWalk(mb, length, frontInclusive,
            [](MapBlock* mb){ return mb->isPassable(); });
}

std::deque<MapBlock*> Map::randomDestinationWalk(
        MapBlock* mb, size_t length, bool frontInclusive,
        std::function<bool(MapBlock*)> pred) {

    // TODO: Properly handle the predicate in A* !!
    
    MapBlock* destination = randomWalk(mb, length, frontInclusive, pred).back();
    return AStar::find(mb, destination, AStar::SimpleCostFunction(), frontInclusive);
}

std::vector<MapBlock*> Map::getInRadius(MapBlock* ref, float r, bool inclusive) {
    std::vector<MapBlock*> results;

    // Make life easier
    int x = ref->x_;
    int y = ref->y_;
    float r2 = r*r;

    // Find the maximal bounding box of blocks -- no sense to search outside it
    int xmin = fmax(0, x-ceil(r));
    int xmax = fmin(getWidth()-1, x+ceil(r));
    int ymin = fmax(0, y-ceil(r));
    int ymax = fmin(getHeight()-1, y+ceil(r));

    // If I look at these for too long, I get the feeling that they're about to 
    // fall over
    if (inclusive) {
        for (int i = xmin; i <= xmax; i++) {
            for (int j = ymin; j <= ymax; j++) {
                if (((x-i)*(x-i) + (y-j)*(y-j)) <= r2) {
                    results.push_back(getBlock(i,j));
                }
            }
        }
    } else {
        for (int i = xmin; i <= xmax; i++) {
            for (int j = ymin; j <= ymax; j++) {
                if (((x-i)*(x-i) + (y-j)*(y-j)) <= r2) {
                    if ((i != x) || (j != y)) {
                        results.push_back(getBlock(i,j));
                    }
                }
            }
        }
    }


    return results;
}


std::vector<MapBlock*> Map::getLOS(MapBlock* mb, bool reveal) {
    std::vector<MapBlock*> results;
    results.push_back(mb);
    if (reveal) mb->visible_ = true;

    // Bresenham fails on straight lines, so handle them separately
    MapBlock* current_block = mb;
    Direction current_dir = Direction::NORTH;
    while (current_block->isPassable()) {
        current_block = current_block->getBlock(current_dir);
        results.push_back(current_block);
        if (reveal) current_block->visible_ = true;
    }
    current_block = mb;
    current_dir = Direction::EAST;
    while (current_block->isPassable()) {
        current_block = current_block->getBlock(current_dir);
        results.push_back(current_block);
        if (reveal) current_block->visible_ = true;
    }
    current_block = mb;
    current_dir = Direction::SOUTH;
    while (current_block->isPassable()) {
        current_block = current_block->getBlock(current_dir);
        results.push_back(current_block);
        if (reveal) current_block->visible_ = true;
    }
    current_block = mb;
    current_dir = Direction::WEST;
    while (current_block->isPassable()) {
        current_block = current_block->getBlock(current_dir);
        results.push_back(current_block);
        if (reveal) current_block->visible_ = true;
    }
    for (unsigned y = 1; y < grid_.size() - 1; y++) {
        for (unsigned x = 1; x < grid_[y].size() - 1; x++) {
            if ((y == 1u || x == 1u || y == grid_.size() - 2 || x == grid_[y].size() - 2))
                bresenham(mb->x_, x, mb->y_, y, results);
        }
    }
    return results;
}

// Slightly modified version of the Bresenham line drawing algorithm,
// fitted for the line of sight calculation.

void Map::bresenham(int x0, int x1, int y0, int y1, std::vector<MapBlock*>& results, bool reveal) {
    bool steep = (fabs(y1 - y0) >= fabs(x1 - x0));
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        //std::swap(x0, x1);
        //std::swap(y0, y1);
    }
    int dx = abs(x1 - x0);
    float dy = fabs(float(y1) - float(y0));
    float error = float(dx) / 2.0f;
    int y_step = (y0 < y1) ? 1 : -1;
    int x_step = (x0 < x1) ? 1 : -1;
    int y = y0;
    int x = x0;
    for (x = x0; x != x1; x += x_step) {
        if (steep) {
            if (!getBlock(y, x)->isPassable()) {
                break;
            } else {
                if (reveal) getBlock(y, x)->visible_ = true;
                results.push_back(getBlock(y, x));
            }
        } else {
            if (!getBlock(x, y)->isPassable()) {
                break;
            } else {
                if (reveal) getBlock(x, y)->visible_ = true;
                results.push_back(getBlock(x, y));
            }
        }
        error -= dy;
        if (error < 0.0f) {
            y += y_step;
            error += float(dx);
        }
    }
    if (steep) {
        if (reveal) getBlock(y, x)->visible_ = true;
	results.push_back(getBlock(y, x));
    } else {
        if (reveal) grid_[y][x]->visible_ = true;
	results.push_back(getBlock(x, y));
    }
}
