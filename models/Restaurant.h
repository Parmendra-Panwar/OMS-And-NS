#ifndef RESTAURANT_H 
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"
using namespace std;

class Restaurant {
    private:
        static int nextRestaurantId;
        int restaurantId;
        string name;
        string location;
        vector<MenuItem> menu;

    public: 
        Restaurant(const string& name, const string& location) {
            this->name = name;
            this->location = location;
            this->restaurantId = nextRestaurantId;
        } // constructor 
        ~Restaurant(){
            cout<<"Destroying Restaurant: "<< name << ", and clearing its memory"<<endl;
            menu.clear();
        }

        // getter and setter
        string getName() const {
            return name;
        }

        void setName(const string &n){
            name  = n;
        }

        string getLocation() const{
            return location;
        }

        void setLocation(const string &l){
            location = l;
        }

        void addMenuItem(const MenuItem &Item){
            menu.push_back(Item);
        }

        const vector<MenuItem>& getMenu() const{
            return menu;
        }
};

int Restaurant::nextRestaurantId = 0;
#endif 