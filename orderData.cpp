//Ritvik Divanji RXD170003

#include "orderData.h"

int orderData::getAdultSeats() const {
    return adultSeats;
}

void orderData::setAdultSeats(int adultSeats) {
    orderData::adultSeats = adultSeats;
}

int orderData::getSeniorSeats() const {
    return seniorSeats;
}

void orderData::setSeniorSeats(int seniorSeats) {
    orderData::seniorSeats = seniorSeats;
}

int orderData::getChildSeats() const {
    return childSeats;
}

void orderData::setChildSeats(int childSeats) {
    orderData::childSeats = childSeats;
}

void orderData::addSeat(theaterSeat * t) {
    orderedSeats.push_back(t);
}

bool orderData::removeSeat(char col,int row) {
    bool inSeats=false;
    int i =0;
    while(i< static_cast<int>(orderedSeats.size())){
        if(orderedSeats.at(static_cast<size_t>(i))->getSeat()==toupper(col) && orderedSeats.at(static_cast<size_t>(i))->getRow()==row) {
            inSeats = true;
            break;
        }
        i++;
    }
    if(!inSeats)
        return false;
    else{
        orderedSeats.at(static_cast<size_t>(i))->setReserved(false);
        switch(orderedSeats.at(static_cast<size_t>(i))->getTicketType()){
            case('A'):
                this->setAdultSeats(this->getAdultSeats()-1);
                break;
            case('C'):
                this->setChildSeats(this->getChildSeats()-1);
                break;
            case('S'):
                this->setSeniorSeats(this->getSeniorSeats()-1);
                break;
        }
        orderedSeats.at(static_cast<size_t>(i))->setTicketType('.');
        orderedSeats.erase(orderedSeats.begin()+i);
        return true;
    }
}

bool orderData::removeSeat(theaterSeat* seat) {
    for(auto seats: orderedSeats){
        if(seats==seat) {
            seats->setTicketType('.');
            seats->setReserved(false);
            return true;
        }
    }
    return false;
}