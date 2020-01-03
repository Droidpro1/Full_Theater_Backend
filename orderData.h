//Ritvik Divanji RXD170003

#ifndef FULL_THEATER_BACKEND_ORDERDATA_H
#define FULL_THEATER_BACKEND_ORDERDATA_H

#include <fstream>
#include "theaterSeat.h"
#include <vector>

class orderData {
private:
    int auditoriumNumber=0;
    std::vector<theaterSeat*> orderedSeats = std::vector<theaterSeat*>();
    int adultSeats=0;
    int seniorSeats=0;
    int childSeats=0;
public:

    orderData() = default;

    int getAuditoriumNumber(){return auditoriumNumber;}

    void setAuditoriumNumber(int a){auditoriumNumber=a;}

    void addSeat(theaterSeat*);

    bool removeSeat(char,int);

    bool removeSeat(theaterSeat*);

    int getAdultSeats() const;

    void setAdultSeats(int adultSeats);

    int getSeniorSeats() const;

    void setSeniorSeats(int seniorSeats);

    int getChildSeats() const;

    void setChildSeats(int childSeats);

    int getNumSeats(){return static_cast<int>(orderedSeats.size());}

    std::vector<theaterSeat*> getOrderedSeats(){return orderedSeats;}
};


#endif //FULL_THEATER_BACKEND_ORDERDATA_H
