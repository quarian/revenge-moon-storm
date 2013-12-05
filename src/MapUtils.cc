#include "Map.hh"

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
    if (inclusive)
        for (int i = xmin; i <= xmax; i++)
            for (int j = ymin; j <= ymax; j++)
                if (((x-i)*(x-i) + (y-j)*(y-j)) <= r2)
                    results.push_back(getBlock(i,j));
    else
        for (int i = xmin; i <= xmax; i++)
            for (int j = ymin; j <= ymax; j++)
                if (((x-i)*(x-i) + (y-j)*(y-j)) <= r2)
                    if ((i != x) || (j != y))
                        results.push_back(getBlock(i,j));

    return results;
}


std::vector<MapBlock*> Map::getLOS(MapBlock*) {
    std::vector<MapBlock*> results;

    // TODO

    return results;
}
