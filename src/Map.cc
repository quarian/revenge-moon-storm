#include "Map.hh"

Map::Map() {}

void Map::loadFromFile(std::string filename) {
    std::cout << "Loading from file: " << filename << std::endl;
    std::ifstream infile(filename);
    std::string line;
    int row = 0;
    int column = 0;
    while (std::getline(infile, line)) {
        std::string temp;
        std::istringstream iss(line);
        std::string line_as_string = iss.str();
        column = 0;
        std::vector<MapBlock> new_row;
        grid_.push_back(new_row);
        for (auto iter = line_as_string.begin(); iter != line_as_string.end(); iter++) {
            std::string content(1, *iter);
            MapBlock mb(row, column, content);
            column++;
            grid_[row].push_back(mb);
        }
        row++;
    }
}

void Map::printMap() {
    std::cout  << "Printing map" << std::endl;
    for (auto iter = grid_.begin(); iter != grid_.end(); iter++) {
        for (auto jiter = (*iter).begin(); jiter != (*iter).end(); jiter++) {
            if (!(jiter->content_).compare(""))
                std::cout << " ";
            else
                std::cout << jiter->content_;
        }
        std::cout << std::endl;
    }
}
