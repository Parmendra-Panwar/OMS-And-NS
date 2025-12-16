#include <iostream>
#include "ZomatoApp.h"
using namespace std;

int main() {
    // create app
    ZomatoApp* zomato = new ZomatoApp();

    // Simulate a user happy flow
    User* user = new User(101, "Paras", "BHOPAL");
    cout << "User: " << user->getName() << " is active." << endl;

    vector<Restaurant*> restaurantList = zomato->searchReastaruants("BHOPAL");

    if (restaurantList.empty()){
        cout << "No restaurant found!" << endl;
        return 0;
    }

    cout << "Found Restaurants: " << endl;
    for (auto restaurant : restaurantList) {
        cout << " - " << restaurant->getName() << endl;
    }

    zomato->selectRestaurant(user, restaurantList[0]);

    cout << "Selected restaurant: " << restaurantList[0]->getName() << endl;

    zomato->addToCart(user, "P1");
    zomato->addToCart(user, "P2");

    zomato->printUserCart(user);

    Order* order = zomato->checkoutNow(user, "Delivery", new UpiPaymentStrategy("152615184121"));

    zomato->payForOrder(user, order);

    delete zomato;
    delete user;

    return 0;
}