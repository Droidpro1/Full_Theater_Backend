//Ritvik Divanji RXD170003

#include "auditorium.h"
#include "theaterSeat.h"
#include "orderData.h"
#include <iostream>
#include <cctype>
#include <cmath>


void auditorium::setRows(){
    //the function calculates how many rows the auditorium will have

    std::ifstream inData(fileName);
    std::string line;

    /*Gets the number of rows by counting line by line,
      taking empty newlines into account*/

    while (!inData.eof()) {
        getline(inData,line);
        if (!line.empty())
            auditorium::rows++;
    }
    inData.close();
}

void auditorium::setCols() {
    //the function calculates how many columns the auditorium will have

    std::ifstream inData(fileName);
    std::string line;

    /*This gets the length of the first line in the
    file, which is equal to the amount of columns for
    the array*/

    getline(inData,line);
    inData.close();
    auditorium::cols= static_cast<int>(line.length());
    columnHeader.resize(static_cast<size_t>(auditorium::cols));
}

auditorium::auditorium(std::string fileName) {
    auditorium::fileName=fileName;
    std::ifstream inData(fileName);
    if (inData.is_open()) {
        auditorium::setRows();
        auditorium::setCols();
        std::string line;

        theaterSeat *previousRow = nullptr;
        theaterSeat *firstInRow = nullptr;
        theaterSeat *seat = nullptr;
        theaterSeat *next = nullptr;

        for (int y = 0; y < (auditorium::rows); y++) { //iterate through the rows
            getline(inData, line);
            for (int x = 0; x < ((auditorium::cols) - 1); x++) { //iterate through the columns
                if (x == 0) { //if you are on the first seat of the row
                    seat = new theaterSeat(y + 1, auditorium::columnHeader.at(static_cast<size_t>(x)), isalpha(line.at(static_cast<size_t>(x))), line.at(static_cast<size_t>(x)));
                    setSeatAuditorium(seat);
                    firstInRow = seat;
                    if (y == 0) { //if you are at the first seat in the auditorium (x and y are both 0)
                        auditorium::setFirst(seat);
                        previousRow = seat;
                    }
                } else
                    seat = seat->getRight();
                next = new theaterSeat(y + 1, auditorium::columnHeader.at(static_cast<size_t>(x)+1), isalpha(line.at(static_cast<size_t>(x) + 1)), line.at(static_cast<size_t>(x) + 1));
                setSeatAuditorium(next);
                if (y > 0) { //if you are not on the first row, set the up and down "links"
                    seat->setUp(previousRow);
                    previousRow->setDown(seat);
                    previousRow = previousRow->getRight();
                }
                //create the right and left "links"
                seat->setRight(next);
                next->setLeft(seat);
            }
            previousRow = firstInRow;
        }
    }
}

int auditorium::getRows() const{
    return auditorium::rows;
}

int auditorium::getCols() const{
    return auditorium::cols;
}

std::string auditorium::getColumnHeader() const {
    return auditorium::columnHeader;
}

theaterSeat *auditorium::getFirst() const {
    return first;
}

void auditorium::setFirst(theaterSeat *first) {
    auditorium::first = first;
}

bool auditorium::checkAvailable(int r, char s, int q){
    theaterSeat* iterator=nullptr;
    theaterSeat* firstInRow=auditorium::getFirst();

    /*find where the character of the column is in the alphabet,
    that will be the column of the array to start the loop that iterates
    to find if there is a reserved seat, where the character is anything
    but a '.' If the character is a letter, then return false*/

    int col= static_cast<int>(auditorium::columnHeader.find(static_cast<char>(toupper(s)))); //finds the row character in the alphabet and returns the position

    //iterate through the auditorium
    for(int y=0;y<r;y++){
        iterator=firstInRow;
        for(int x=0;x<=col;x++){
            if(iterator->getRow()==r && iterator->getSeat()==s) {
                /*if this is the seat we want to check is available,
                  see if it, plus any other seats we want to reserve,
                  are reserved. If they are, return false, if not
                  return true*/
                for (int c = 0; c < q; c++) {
                    if (iterator->isReserved())
                        return false;
                    iterator = iterator->getRight();
                }
                return true;
            }
            else
                iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
    }
}

void auditorium::displayAuditorium(){
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator=nullptr;

    std::cout<<"   "<<auditorium::columnHeader<<std::endl; //prints the column header
    for(int y=0;y<auditorium::rows;y++){
        iterator=firstInRow;
        //this if else is just for formatting
        if(y+1>=10)
            std::cout<<y+1<<" "; //adds the header for the rows, y starts at 0 thats why add 1
        else
            std::cout<<y+1<<"  ";
        for(int x=0;x<auditorium::cols;x++){
            if(iterator->isReserved())
                std::cout<<'#';
            else
                std::cout<<'.';
            iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
        std::cout<<std::endl; //when the row ends, start a new one
    }
    std::cout<<std::endl;
}

void auditorium::writeBack(){
    std::ofstream outData(auditorium::fileName);
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator=nullptr;
    //clears the file and starts putting stuff from the auditorium into the file
    for(int y=0;y<auditorium::rows;y++){
        iterator=firstInRow;
        for(int x=0;x<auditorium::cols;x++) {
            outData << iterator->getTicketType();
            iterator=iterator->getRight();
        }
        //to prevent a trailing newline character from being added to the file
        if(y!=auditorium::rows-1)
            outData<<"\n";
        firstInRow=firstInRow->getDown();
    }
    outData.close();
}

orderData* auditorium::reserveSeats(int r, char s, int aq, int cq, int sq, orderData* order){
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator=nullptr;
    /*iterate through the auditorium until
      we find the seat we want to start reserving
      at */
    int col= static_cast<int>(auditorium::columnHeader.find(static_cast<char>(toupper(s))));
    for(int y=0;y<r;y++){
        iterator=firstInRow;
        for(int x=0;x<col;x++){
            iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
    }

    //iterates through the row, setting the desired 'box' as the proper character
    for(int c=0;c<aq;c++) {
        iterator->setTicketType('A');
        iterator->setReserved(true);
        //add the seat to the order then increment the respective counter
        if(order) {
            order->addSeat(iterator);
            order->setAdultSeats(order->getAdultSeats() + 1);
        }
        iterator=iterator->getRight();
    }
    for(int c=0;c<cq;c++) {
        iterator->setTicketType('C');
        iterator->setReserved(true);
        //add the seat to the order then increment the respective counter
        if(order) {
            order->addSeat(iterator);
            order->setChildSeats(order->getChildSeats() + 1);
        }
        iterator=iterator->getRight();
    }
    for(int c=0;c<sq;c++) {
        iterator->setTicketType('S');
        iterator->setReserved(true);
        //add the seat to the order then increment the respective counter
        if(order) {
            order->addSeat(iterator);
            order->setSeniorSeats(order->getSeniorSeats() + 1);
        }
        iterator=iterator->getRight();
    }
    std::cout<<"\nYour seats have been reserved!"<<std::endl;
    return order;
}

theaterSeat* auditorium::bestAvailable(int q){
    theaterSeat* bestSeat=nullptr;
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator=nullptr;

    double middleSelection=0.0;
    double middleX= (auditorium::cols-1)/2.0;
    double middleY= (auditorium::rows-1)/2.0;

    double dist=40000000.00; //an arbitrary number that every distance calculated will be shorter than

    /*iterates through the auditorium, checks
      if the seats are available, calculates the
      middle of the selection of seats, sets the
      seat based on the conditions, then returns
      the seat*/

    for(int y=0;y<auditorium::rows;y++) {
        iterator=firstInRow;
        for(int x=0;x<auditorium::cols-q+1;x++) {
            if(auditorium::checkAvailable(y+1, auditorium::columnHeader.at(static_cast<size_t>(x)), q)){
                //find the middle of the quantity desired, then offset that by x
                middleSelection = ((q-1)/2.0)+x;
                /*if the seat is available and the new distance is strictly less than the previous
                set the new distance as the distance and set the current seat as the startingSeat */
                if (sqrt(pow(middleX-middleSelection,2)+pow(middleY-y,2)) < dist) {
                    dist = sqrt(pow(middleX-middleSelection,2)+pow(middleY-y,2));
                    bestSeat = iterator;
                }
                /*otherwise if the distances are strictly equal, calculate the vertical distance
                  to the center and assign the new seat accordingly */
                else if (sqrt(pow(middleX-middleSelection,2)+pow(middleY-y,2)) == dist){
                    if((abs(static_cast<int>((bestSeat->getRow() - 1) - middleY))) > (abs(static_cast<int>((iterator->getRow() - 1) - middleY))))
                        bestSeat=iterator;
                }
            }
            iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
    }
    return bestSeat;
}

int auditorium::getNumOpenSeats(){
    int num=0;
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator;
    for(int y=0;y<(auditorium::rows);y++){
        iterator=firstInRow;
        for(int x=0;x<(auditorium::cols);x++){
            if(iterator->getTicketType()=='.')
                num++;
            iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
    }
    return num;
}

int auditorium::getNumReservedSeats(){
    int num=0;
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator;
    for(int y=0;y<(auditorium::rows);y++){
        iterator=firstInRow;
        for(int x=0;x<(auditorium::cols);x++){
            if(iterator->getTicketType()!='.')
                num++;
            iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
    }
    return num;
}

int auditorium::getNumSeatType(char ticketType){
    int num=0;
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator;
    ticketType=static_cast<char>(toupper(ticketType));
    for(int y=0;y<(auditorium::rows);y++){
        iterator=firstInRow;
        for(int x=0;x<(auditorium::cols);x++){
            if(iterator->getTicketType()==ticketType)
                num++;
            iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
    }
    return num;
}

double auditorium::getTotalSales(){
    int adult=0;
    int child=0;
    int senior=0;
    theaterSeat* firstInRow=auditorium::getFirst();
    theaterSeat* iterator;

    for(int y=0;y<(auditorium::rows);y++){
        iterator=firstInRow;
        for(int x=0;x<(auditorium::cols);x++){
            if(iterator->getTicketType()=='A')
                adult++;
            else if(iterator->getTicketType()=='C')
                child++;
            else if(iterator->getTicketType()=='S')
                senior++;
            iterator=iterator->getRight();
        }
        firstInRow=firstInRow->getDown();
    }
    return (adult*10.0)+(child*5.0)+(senior*7.5);
}

void auditorium::setSeatAuditorium(theaterSeat * seat) {
    if(fileName=="A1.txt")
        seat->setAuditoriumNumber(1);
    else if (fileName=="A2.txt")
        seat->setAuditoriumNumber(2);
    else
        seat->setAuditoriumNumber(3);
}

void auditorium::deleteCol(theaterSeat *ptr) {
    if(ptr==nullptr)
        return;
    deleteCol(ptr->getDown());
    deleteRow(ptr);
}

void auditorium::deleteRow(theaterSeat *ptr) {
    if(ptr==nullptr)
        return;
    deleteRow(ptr->getRight());
    delete ptr;
}

auditorium::~auditorium() {
    /*call the recursive delete functions because
      this is complicated */
    auditorium::deleteCol(auditorium::first);
}