//Ritvik Divanji RXD170003

#include "baseNode.h"

baseNode::baseNode(){
}

baseNode::baseNode(int row,char seat,bool reserved,char ticketType){
    baseNode::row=row;
    baseNode::seat=seat;
    baseNode::reserved=reserved;
    baseNode::ticketType=ticketType;
}

int baseNode::getRow() const {
    return row;
}

char baseNode::getSeat() const {
    return seat;
}

bool baseNode::isReserved() const {
    return reserved;
}

void baseNode::setReserved(bool reserved) {
    baseNode::reserved = reserved;
}

char baseNode::getTicketType() const {
    return ticketType;
}

void baseNode::setTicketType(char ticketType) {
    baseNode::ticketType = ticketType;
}
