#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../strategies/PaymentStrategy.h"
#include "../utils/TimeUtils.h"
using namespace std;

class Order {
    protected:
        static int nextOrderId;
        int orderId;
        User* user;
        Restaurant* restaurant;
        vector<MenuItem> items;
        string paymentStrategy;
        string paymentWith;
        double total;
        string scheduled;
    
    public:
        Order() {
            user = nullptr;
            restaurant = nullptr;
            paymentStrategy = "";
            paymentWith = "";
            total = 0.0;
            scheduled = "";
            orderId = ++nextOrderId; 
        }

        // virtual ~Order(){
        //     delete paymentStrategy;
        // }

        // bool processPayment(){
        //     if(paymentStrategy) {
        //         paymentStrategy->pay(total);
        //         return true;
        //     } else {
        //         cout<< "Please choose a payment mode first" <<endl;
        //         return false;
        //     }
        // }

        virtual string getType() const =0;

        //getter setter
        int getOrderId() const{
            return orderId;
        }

        void setUser(User* u){
            user = u;
        }
        
        User* getUser() const {
            return user;
        }

        void setRestaurant(Restaurant* r){
            restaurant = r;
        }

        Restaurant* getRestaurant() const{
            return restaurant;
        }

        string getPaymentWith() const{
            return paymentWith;
        }

        string getPaymentStrategy() const{
            return paymentStrategy;
        }

        void setItems(const vector<MenuItem>& its){
            items = its;
            total = 0;
            for (auto &i : items) {
                total += i.getPrice();
            }
        }

        const vector<MenuItem>& getItems() const {
            return items;
        }

        void setPaymentStrategy(const string p) {
            paymentStrategy = p;
        }

        void setPaymentWith(const string p) {
            paymentWith = p;
        }

        void setScheduled(const string& s) {
            scheduled = s; 
        }

        string getScheduled() const {
            return scheduled;
        }

        double getTotal() const{
            return total;
        }

        void setTotal(int total) {
            this->total = total;
        }
};

int Order::nextOrderId = 0;

#endif