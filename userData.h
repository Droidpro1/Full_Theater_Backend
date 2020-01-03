//Ritvik Divanji RXD170003

#ifndef FULL_THEATER_BACKEND_USERDATA_H
#define FULL_THEATER_BACKEND_USERDATA_H

#include <string>
#include <vector>
#include "orderData.h"

class userData {
private:
    std::string password;
    std::vector<orderData*> orders = std::vector<orderData*>();
public:
    userData() = default;
    userData(std::string p) {password=p;}
    void addOrder(orderData*);
    std::string getPassword() {return password;}
    int getNumOrders(){return static_cast<int>(orders.size());}
    std::vector<orderData*> getOrders(){return orders;}
    void cancelOrder(orderData*);
};


#endif //FULL_THEATER_BACKEND_USERDATA_H
