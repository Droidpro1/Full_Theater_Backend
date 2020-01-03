//Ritvik Divanji RXD170003

#ifndef PROJECT4_AUDITORIUM_H
#define PROJECT4_AUDITORIUM_H

#include <unordered_map>
#include <string>
#include "theaterSeat.h"
#include "userData.h"

class auditorium {
private:
    std::string fileName;
    theaterSeat* first;
    int rows=0;
    int cols=0;
    void setRows();
    void setCols();
    std::string columnHeader="ABCDEFGHIJKLMNOPQRSTUVWXYZ";

public:
    auditorium(std::string);
    int getRows() const;
    int getCols() const;
    theaterSeat *getFirst() const;
    void setFirst(theaterSeat *first);
    void deleteCol(theaterSeat *ptr);
    void deleteRow(theaterSeat *ptr);

    theaterSeat* bestAvailable(int);
    orderData* reserveSeats(int, char, int, int, int,orderData*);
    std::string getColumnHeader() const ;
    void writeBack();
    void displayAuditorium();
    bool checkAvailable(int, char, int);
    int getNumOpenSeats();
    int getNumReservedSeats();
    int getNumSeatType(char);
    //Added for REGRADE
    std::string getFileName(){return fileName;};
    double getTotalSales();
    void setSeatAuditorium(theaterSeat*);
    ~auditorium();
};


#endif //PROJECT4_AUDITORIUM_H
