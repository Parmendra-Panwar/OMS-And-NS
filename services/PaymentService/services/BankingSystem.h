#pragma once

#include "../models/PaymentRequest.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class IBankingSystem{
    public:
    virtual ~IBankingSystem() {};
    virtual bool processPayment(PaymentRequest* pr) = 0;
};

class PaytmBankingSystem : public IBankingSystem {
public:
    PaytmBankingSystem() {}
    bool processPayment(PaymentRequest* pr) override {
        cout << "[BankingSystem-Paytm] Processing payment of " << pr->getAmount() << "...\n";
        // Simulate 80% success
            int r = rand() % 100;
            return r < 80;
    }
};

class RazorpayBankingSystem : public IBankingSystem {
public:
    RazorpayBankingSystem() {}
    bool processPayment(PaymentRequest* pr) override {
        cout << "[BankingSystem-Razorpay] Processing payment of " << pr->getAmount() << "...\n";
        // Simulate 90% success
        int r = rand() % 100;
        return r < 90;
    }
};