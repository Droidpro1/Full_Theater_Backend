//Ritvik Divanji RXD170003

#ifndef FULL_THEATER_BACKEND_THEATERSEAT_H
#define FULL_THEATER_BACKEND_THEATERSEAT_H


#include "baseNode.h"
#include <string>

class theaterSeat: public baseNode {
private:
    int auditoriumNumber=0;
    theaterSeat* up=nullptr;
    theaterSeat* down=nullptr;
    theaterSeat* left=nullptr;
    theaterSeat* right=nullptr;
public:
    theaterSeat();
    theaterSeat(int,char,bool,char);
    void setAuditoriumNumber(int a){auditoriumNumber=a;}
    void setUp(theaterSeat *up);
    theaterSeat *getDown() const;
    void setDown(theaterSeat *down);
    void setLeft(theaterSeat *left);
    theaterSeat *getRight() const;
    void setRight(theaterSeat *right);
};


#endif //FULL_THEATER_BACKEND_THEATERSEAT_H
