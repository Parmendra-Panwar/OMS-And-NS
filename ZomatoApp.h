#ifndef ZOMATO_APP_H
#define ZOMATO_APP_H

#include <vector>
#include <string>
#include "models/User.h"
#include "models/Restaurant.h"
#include "models/Cart.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "strategies/PaymentStrategy.h"
#include "strategies/UpiPaymentStrategy.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduledOrderFactory.h"
#include "services/NotificationService.h"
#include "utils/TimeUtils.h"
#include "./services/PaymentService/PaymentService.h"

using namespace std;

class ZomatoApp {
    public: 
        ZomatoApp() {
            initializeRestaurants();
        }

        void initializeRestaurants(){
            Restaurant* restaurant1 = new Restaurant("RAJARAM", "BHOPAL");
            restaurant1->addMenuItem(MenuItem("P1", "Chola Bhatura", 60));
            restaurant1->addMenuItem(MenuItem("P2", "Chola Rice", 80));

            Restaurant* restaurant2 = new Restaurant("Chai wala", "INDORE");
            restaurant2->addMenuItem(MenuItem("P1", "Samosa", 40));
            restaurant2->addMenuItem(MenuItem("P2", "Chai Masala", 80));

            RestaurantManager* restaurantManager = RestaurantManager::getInstance();
            restaurantManager->addRestaurant(restaurant1);
            restaurantManager->addRestaurant(restaurant1);
        }

        vector<Restaurant*> searchReastaruants(const string& location) {
            return RestaurantManager::getInstance()->searchByLocation(location);
        } 

        void selectRestaurant(User* user, Restaurant* restaurant) {
            Cart* cart = user->getCart();
            cart->setRestaurant(restaurant);
        }

        void addToCart(User* user, const string& itemCode) {
            Restaurant* restaurant = user->getCart()->getRestaurant();
            if (!restaurant) {
                cout << "Please select a restaurant first" << endl;
                return;
            }
            for (const auto& item : restaurant->getMenu()){
                if (item.getcode() == itemCode) {
                    user->getCart() ->addItem(item);
                    break;
                }
            }
        }

        Order* checkoutNow(User* user, const string& orderType, const string paymentStrategy, GatewayType paymentWith) {
            string PaymentWith;
            if(paymentWith == GatewayType::RAZOREPAY){
                PaymentWith = "RAZOREPAY";
            }else{
                PaymentWith = "PAYTM";
            }
            return checkout(user, orderType, paymentStrategy,  PaymentWith, new NowOrderFactory());
        }
        Order* checkoutScheduled(User* user, const string& orderType, const string paymentStrategy, const string& scheduleTime, GatewayType paymentWith) {
            string PaymentWith;
            if(paymentWith == GatewayType::RAZOREPAY){
                PaymentWith = "RAZOREPAY";
            }else{
                PaymentWith = "PAYTM";
            }
            return checkout(user, orderType, paymentStrategy, PaymentWith, new ScheduledOrderFactory(scheduleTime));
        }

        Order* checkout(User* user, const string& orderType, const string paymentStrategy, const string paymentWith, OrderFactory* orderFactory) {
            if(user->getCart()->isEmpty())
            return nullptr;

            Cart* userCart = user->getCart();
            Restaurant* orderedRestaurant = userCart->getRestaurant();
            vector<MenuItem> itemsOrdered = userCart->getItems();
            double totalCost = userCart->getTotalCost();

            Order* order = orderFactory->createOrder(user, userCart, orderedRestaurant, itemsOrdered, paymentStrategy, paymentWith, totalCost, orderType);

            return order;
        }

        void payForOrder(User* user, Order* order) {
            PaymentRequest* req1 = new PaymentRequest(user->getName(), order->getRestaurant()->getName(), order->getTotal(), "INR");

            bool isPaymentSuccess;
            if(order->getPaymentWith() == "RAZOREPAY"){
                cout << "Processing via RAZOREPAY and "<< ((order->getPaymentStrategy() == "UPI") ? "UPI" : "CraditCard") << endl;
                cout << "------------------------------\n";
                isPaymentSuccess = PaymentController::getInstance().handdlePayment(GatewayType::RAZOREPAY, req1);
                cout << "Result: " << (isPaymentSuccess ? "SUCCESS" : "FAIL") << "\n";
                cout << "------------------------------\n\n";
            }else{
                cout << "Processing via Paytmand "<< ((order->getPaymentStrategy() == "UPI") ? "UPI" : "CraditCard") << endl;
                cout << "------------------------------\n";
                isPaymentSuccess = PaymentController::getInstance().handdlePayment(GatewayType::PAYTM, req1);
                cout << "Result: " << (isPaymentSuccess ? "SUCCESS" : "FAIL") << "\n";
                cout << "------------------------------\n\n";
            }
            

            // bool isPaymentSuccess = order->processPayment();

            if(isPaymentSuccess) {
                NotificationFacade* notification = new NotificationFacade();
                notification->notify(order);
                user->getCart()->clear();
            }
        }

        void printUserCart(User* user) {
            cout << "Items in cart:" << endl;
            cout << "----------------------------------" << endl;
            for (const auto& item : user->getCart()->getItems()){
                cout << item.getcode() << " : " << item.getName() << " : $" << item.getPrice() << endl;
            }
            cout << "----------------------------------" << endl;
            cout << "Grand total : $" << user->getCart()->getTotalCost() << endl;
        }
};

#endif