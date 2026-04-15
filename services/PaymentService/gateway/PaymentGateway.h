#pragma once

#include <iostream>
#include <vector>

#include "../services/BankingSystem.h"

using namespace std;

class IPaymentGateway{
    protected:
    IBankingSystem* bs;
    public:
    IPaymentGateway(){
        bs = nullptr;
    }
    virtual ~IPaymentGateway(){
        delete bs;
    }

    virtual bool processPayment(PaymentRequest* request) {
        if (!validatePayment(request)) {
            cout << "[PaymentGateway] Validation failed for " << request->getSender() << ".\n";
            return false;
        }
        if (!initiatePayment(request)) {
            cout << "[PaymentGateway] Initiation failed for " << request->getSender() << ".\n";
            return false;
        }
        if (!confirmPayment(request)) {
            cout << "[PaymentGateway] Confirmation failed for " << request->getSender() << ".\n";
            return false;
        }
        
        return true;
    }

    virtual bool validatePayment(PaymentRequest* pr) = 0;
    virtual bool initiatePayment(PaymentRequest* pr)= 0;
    virtual bool confirmPayment(PaymentRequest* pr)= 0;
};

class PaytmGateway : public IPaymentGateway{
    public:
    PaytmGateway(){
        bs = new PaytmBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout << "[Paytm] Validating payment form " << request->getSender() << " To " << request->getReciver() << ".\n";

        if (request->getAmount() <= 0 || request->getCourncy() != "INR") {
            return false;
        }
        return true;
    }
    bool initiatePayment(PaymentRequest* request) override {
        cout << "[Paytm] Initiating payment of " << request->getAmount() << " " << request->getCourncy() << " form " << request->getSender() << " To " << request->getReciver() << ".\n";

        return bs->processPayment(request);
    }
    bool confirmPayment(PaymentRequest* request) override {
        cout << "[Paytm] Confirming payment form " << request->getSender() << " To " << request->getReciver() << ".\n";
        return true;
    }
};

class RazorPayGateway : public IPaymentGateway{
    public:
    RazorPayGateway() {
        bs = new RazorpayBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout << "[RazorPay] Validating payment form " << request->getSender() << " To " << request->getReciver() << ".\n";

        if (request->getAmount() <= 0) return false;
        return true;
    }
    bool initiatePayment(PaymentRequest* request) override {
        cout << "[RazorPay] Initiating payment of " << request->getAmount() << " " << request->getCourncy() << " form " << request->getSender() << " To " << request->getReciver() << ".\n";

        return bs->processPayment(request);
    }
    bool confirmPayment(PaymentRequest* request) override {
        cout << "[RazorPay] Confirming payment form " << request->getSender() << " To " << request->getReciver() << ".\n";
        return true;
    }
};

class PaymentGatewayProxy : public IPaymentGateway{
    private:
    IPaymentGateway* realGateway;
    int retries;
    public:
    PaymentGatewayProxy(IPaymentGateway* p, int r){
        realGateway = p;
        retries = r;
    }
    ~PaymentGatewayProxy(){
        delete realGateway;
    }

    bool processPayment(PaymentRequest* request) override {
        bool result = false;
        for (int attempt = 0; attempt < retries; ++attempt) {
            if (attempt > 0) cout << "[Proxy] Retrying payment (attempt " << (attempt+1) << ") for " << request->getSender() << ".\n";
            
            result = realGateway->processPayment(request);
            if (result) break;
        }
        if (!result) cout << "[Proxy] Payment failed after " << (retries) << " attempts for " << request->getSender() << ".\n";
        
        return result;
    }

    bool validatePayment(PaymentRequest* request) override {
        return realGateway->validatePayment(request);
    }
    bool initiatePayment(PaymentRequest* request) override {
        return realGateway->initiatePayment(request);
    }
    bool confirmPayment(PaymentRequest* request) override {
        return realGateway->confirmPayment(request);
    }
};

enum class GatewayType{
    PAYTM,
    RAZOREPAY
};

class GatewayFactory{
    static GatewayFactory instance;
    GatewayFactory(){}
    GatewayFactory(const GatewayFactory&) = delete;
    GatewayFactory& operator=(const GatewayFactory&) = delete;

    public:
    static GatewayFactory& getInstance() {
        return instance;
    }
    IPaymentGateway* getGateway(GatewayType type) {
        if (type == GatewayType::PAYTM) {
            IPaymentGateway* paymentGateway = new PaytmGateway();
            return new PaymentGatewayProxy(paymentGateway, 3);
        } else {
            IPaymentGateway* paymentGateway = new RazorPayGateway();
            return new PaymentGatewayProxy(paymentGateway, 1);
        }
    }
};

GatewayFactory GatewayFactory::instance;