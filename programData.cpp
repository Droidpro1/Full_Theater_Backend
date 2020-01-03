//Ritvik Divanji RXD170003

#include "programData.h"

auditorium* programData::getAuditorium(std::string name){
    if(name=="a1")
        return a1;
    else if(name=="a2")
        return a2;
    else return a3;
}