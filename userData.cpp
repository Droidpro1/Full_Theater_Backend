//Ritvik Divanji RXD170003

#include "userData.h"

void userData::addOrder(orderData* order) {
    orders.push_back(order);
}

void userData::cancelOrder(orderData* order) {
    for(auto seat : order->getOrderedSeats()){
        seat->setReserved(false);
        seat->setTicketType('.');
    }
    for(int i=0;i<static_cast<int>(orders.size());i++){
        if(orders[static_cast<size_t>(i)]==order){
            orders.erase(orders.begin()+i);
            break;
        }
    }
}