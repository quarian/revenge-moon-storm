#include "Walker.hh"

// Impelementation shell for Walker - makes the code compile

Walker::Walker(Map const& map, MapBlock* location, float speed) : map_(map),
                                                                  location_(location), dir_(Direction::NORTH),
                                                                  entering_(false),
                                                                  walking_(false),
                                                                  speed_(speed),
                                                                  dx_(0.0f),
                                                                  dy_(0.0f)
{
}
