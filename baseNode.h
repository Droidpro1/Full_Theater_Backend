//Ritvik Divanji RXD170003

#ifndef FULL_THEATER_BACKEND_BASENODE_H
#define FULL_THEATER_BACKEND_BASENODE_H


class baseNode {
private:
    int row=0;
    char seat;
    bool reserved=false;
    char ticketType;
public:
    baseNode();
    baseNode(int,char,bool,char);
    int getRow() const;
    char getSeat() const;
    bool isReserved() const;
    void setReserved(bool reserved);
    char getTicketType() const;
    void setTicketType(char ticketType);
};


#endif //FULL_THEATER_BACKEND_BASENODE_H
