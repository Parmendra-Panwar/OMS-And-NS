#pragma once

#include <iostream>
#include <vector>

using namespace std;

class PaymentRequest{
    private:
    string sender;
    string reciver;
    double amount;
    string courncy;
    public:
    PaymentRequest(string sender, string reciver, double amount, string courncy){
        this->sender = sender;
        this->reciver = reciver;
        this->amount = amount;
        this->courncy = courncy;
    }
    string getSender(){
        return sender;
    }
    string getReciver(){
        return reciver;
    }
    double getAmount(){
        return amount;
    }
    string getCourncy(){
        return courncy;
    }
};