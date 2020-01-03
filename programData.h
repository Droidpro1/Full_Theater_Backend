//Ritvik Divanji RXD170003

#ifndef FULL_THEATER_BACKEND_PROGRAMDATA_H
#define FULL_THEATER_BACKEND_PROGRAMDATA_H

#include <string>
#include "userData.h"
#include "auditorium.h"
#include <unordered_map>

class programData {
private:
    std::string username;
    auditorium* a1 = new auditorium("A1.txt");
    auditorium* a2 = new auditorium("A2.txt");
    auditorium* a3 = new auditorium("A3.txt");
    std::unordered_map<std::string,userData*>* db = new std::unordered_map<std::string,userData*>;
public:
    programData() = default;
    programData(std::unordered_map<std::string,userData*>* db){programData::db=db;}
    std::string getUsername(){return username;}
    void clearUsername(){username.clear();}
    auditorium* getAuditorium(std::string);
    std::unordered_map<std::string,userData*>* getDB(){return db;}
    void setUsername(std::string u){username=u;}
};


#endif //FULL_THEATER_BACKEND_PROGRAMDATA_H
