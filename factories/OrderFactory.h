#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include "../models/Order.h"
#include "../models/Cart.h"
#include "../models/Restaurant.h"
#include "../strategies/PaymentStrategy.h"
#include <vector>
#include <string>
using namespace std;

class OrderFactory {
    public:
        virtual Order* createOrder(User* user, Cart* cart, Restaurant* restaurant, const vector<MenuItem>& menuItems,
        const string paymentStrategy, const string paymentWith, double totalCost, const string& orderType) = 0;

        virtual ~OrderFactory() {}
};

#endif