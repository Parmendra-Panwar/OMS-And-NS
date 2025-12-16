#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include "Order.h"
using namespace std;

class DeliveryOrder : public Order {
    private: 
        string userAddress;

    public: 
        DeliveryOrder(){
            userAddress = "";
        }

        string getType() const override {
            return "Delivery";
        }

        // getter and Setters 
        void setUserAddress(const string& add) {
            userAddress = add;
        }

        string getUserAddress() const {
            return userAddress;
        }
};

#endif