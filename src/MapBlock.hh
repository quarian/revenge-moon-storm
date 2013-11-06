#ifndef MB2_MAPBLOCK_HH
#define MB2_MAPBLOCK_HH

#include <string>

class MapBlock {
    public:
        MapBlock(int x, int y, std::string content);
        int x_;
        int y_;
        std::string content_;
};

#endif
