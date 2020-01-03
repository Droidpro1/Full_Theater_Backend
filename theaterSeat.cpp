//Ritvik Divanji RXD170003

#include "theaterSeat.h"

theaterSeat::theaterSeat():baseNode() {}

theaterSeat::theaterSeat(int row,char seat,bool reserved,char ticketType):baseNode(row,seat,reserved,ticketType) {}

void theaterSeat::setUp(theaterSeat *up) {
    theaterSeat::up = up;
}

theaterSeat *theaterSeat::getDown() const {
    return down;
}

void theaterSeat::setDown(theaterSeat *down) {
    theaterSeat::down = down;
}

void theaterSeat::setLeft(theaterSeat *left) {
    theaterSeat::left = left;
}

theaterSeat *theaterSeat::getRight() const {
    return right;
}

void theaterSeat::setRight(theaterSeat *right) {
    theaterSeat::right = right;
}
