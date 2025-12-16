#ifndef USER_H
#define USER_H

#include <string>
#include "Cart.h"

using namespace std;

class User {
    private:
        int userId;
        string name;
        string address;
        Cart* cart;
    
    public: 
        User(int userId, const string& name, const string& address){
            this->userId = userId;
            this->address = address;
            this->name = name;
            cart = new Cart();
        }

        ~User(){
            delete cart;
        }

        // Getter and Setter
        string getName() const{
            return name;
        }

        void setName(const string &n){
            name = n;
        }

        string getAddress() const{
            return address;
        }

        void setAddress(const string &s) {
            address = s;
        }

        Cart* getCart() const{
            return cart;
        }
};

#endif