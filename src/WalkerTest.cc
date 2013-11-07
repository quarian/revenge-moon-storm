#include "tests.hh"

#include <cmath>

bool WalkerTest1(std::ostream& os) {
    float EPSILON = 0.00001f;
    Map map;
    MapBlock mb(1, 1, "#");
    Walker w(map, &mb, 2.0f);

    /* SECTION 0 */
    os << "SECTION 0...";
    /* Initialization */
    if (w.getdX() != 0.0f) {
        os << "\nWalker initialization error: dx_ should be 0" << std::endl;
        return false;
    }
    if (w.getdY() != 0.0f) {
        os << "\nWalker initialization error: dy_ should be 0" << std::endl;
        return false;
    }
    if (!w.isCentered()) {
        os << "\nWalker initialization error: should be centered" << std::endl;
        return false;
    }
    if (w.isWalking()) {
        os << "\nWalker initialization error: should not be walking right away" << std::endl;
        return false;
    }
    os << " OK" << std::endl;

    /* SECTION 1 */
    os << "SECTION 1...";
    /* Updating when not in motion should not do anything */
    w.update(0.1);

    if (w.getdX() != 0.0f) {
        os << "\nWalker should not be moving when walking_ is false" << std::endl;
        return false;
    }
    if (w.getdY() != 0.0f) {
        os << "\nWalker should not be moving when walking_ is false" << std::endl;
        return false;
    }
    os << " OK" << std::endl;

    /* SECTION 2 */
    os << "SECTION 2...";
    /* Walking and stopping without changing direction */
    w.walk();
    w.update(0.1);
    if (w.getdX() != 0.0) {
        os << "\nAfter 0.1 seconds the walker's dx_ should be 0.0 (but it's " << w.getdY() << ")" << std::endl;
        return false;
    }
    if (fdim(w.getdY(), -0.2) > EPSILON) {
        os << "\nAfter 0.1 seconds the walker's dy_ should be -0.2 (but it's " << w.getdY() << ")" << std::endl;
        return false;
    }
    w.stop();
    if (!w.isCentered()) {
        os << "\nWalker should be centered after stopping" << std::endl;
        return false;
    }
    w.update(0.1);
    if (!w.isCentered()) {
        os << "\nWalker should not move when walking_ is false" << std::endl;
        return false;
    }
    w.walk();
    w.update(0.05);
    if (fdim(w.getdY(), -0.1) > EPSILON) {
        os << "\nAfter 0.05 seconds the walker's dy_ should be -0.1 (but it's " << w.getdY() << ")" << std::endl;
        return false;
    }
    if (w.getdX() != 0.0) {
        os << "\nAfter 0.05 seconds the walker's dx_ should be 0.0 (but it's " << w.getdY() << ")" << std::endl;
        return false;
    }
    w.update(0.12);
    if (fdim(w.getdY(), -0.34) > EPSILON) {
        os << "\nAfter 0.17 seconds the walker's dy_ should be -0.34 (but it's " << w.getdY() << ")" << std::endl;
        return false;
    }
    if (w.getdX() != 0.0) {
        os << "\nAfter 0.17 seconds the walker's dx_ should be 0.0 (but it's " << w.getdY() << ")" << std::endl;
        return false;
    }
    os << " OK" << std::endl;


    return true;
}
