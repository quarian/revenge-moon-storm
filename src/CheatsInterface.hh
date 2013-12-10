#ifndef MB2_CHEATSINTERFACE_HH
#define MB2_CHEATSINTERFACE_HH

#include "KeyInterface.hh"

class CheatsInterface : public KeyInterface {
public:
    CheatsInterface(bool&);
    virtual bool operator==(KeyInterface const& other) const = 0;
    virtual bool parse(sf::Event&);
private:
    bool& flagVictory_;
};

#endif
