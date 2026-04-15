#pragma once

#include <iostream>
#include <vector>

#include "./gateway/PaymentGateway.h"

using namespace std;

class PaymentService{
    private:
    static PaymentService instance;
    IPaymentGateway* paymentGateway;
    PaymentService(){
        paymentGateway = nullptr;
    }
    ~PaymentService(){
        delete paymentGateway;
    }
    PaymentService(const PaymentService&) = delete;
    PaymentService& operator = (const PaymentService&) = delete;
    public:
    static PaymentService& getInstance(){
        return instance;
    }
    void setGetway(IPaymentGateway* p){
        if(paymentGateway) delete paymentGateway;
        paymentGateway = p;
    }
    bool processPayment(PaymentRequest* pr){
        if (!paymentGateway) {
            cout << "[PaymentService] No payment gateway selected.\n";
            return false;
        }
        return paymentGateway->processPayment(pr);
    }
};

PaymentService PaymentService::instance;

class PaymentController{
    private:
    static PaymentController instance;
    PaymentController(){}
    
    PaymentController(const PaymentController&) = delete;
    PaymentController& operator = (const PaymentController&) = delete;
    public:
    static PaymentController& getInstance(){
        return instance;
    }
    
    bool handdlePayment(GatewayType type, PaymentRequest* pr){
        IPaymentGateway* py = GatewayFactory::getInstance().getGateway(type);
        PaymentService::getInstance().setGetway(py);
        return PaymentService::getInstance().processPayment(pr);
    }
};

PaymentController PaymentController::instance;