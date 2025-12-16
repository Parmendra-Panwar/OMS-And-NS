#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*============================ Decorators ===========================*/
class INotification{
    public:
    virtual string getContent() const = 0;

    virtual ~INotification() {}
};

class SimpleNotification: public INotification{
    private:
    string text;
    public:
    SimpleNotification(const string& text){
        this->text = text;
    }
    string getContent() const override {
        return text;
    }
};

class INotification_decorator: public INotification{
    protected:
    INotification* notification;
    public:
    INotification_decorator(INotification* n){
        notification = n;
    }
    virtual ~INotification_decorator() {
        delete notification;
    }
};

class TimeStemp_Decorator: public INotification_decorator{
    public:
    // injection (getting and setting) of INotification 
    TimeStemp_Decorator(INotification* n): INotification_decorator(n) {}

    string getContent() const override {
        return notification->getContent() + "13/12/2025";
    }
};

class Signature_Decorator: public INotification_decorator{
    private:
    string signature = "";
    public:
    Signature_Decorator(INotification* n, const string& str): INotification_decorator(n) {
        signature = str;
    }

    string getContent() const override {
        return notification->getContent() + signature;
    }
};

/*============================ Observer ===========================*/

class IObserver{
    public:
    virtual void update() = 0;
    virtual ~IObserver(){}
};

class IObservable{
    public:
    virtual void add(IObserver * obs) = 0;
    virtual void removeObs(IObserver * obs) = 0;
    virtual void notify() = 0;
    
    virtual ~IObservable(){}
};

class NotificationObservable: public IObservable{
    private:
        vector<IObserver *> observers;
        INotification* cNotification;
    public:
        void add(IObserver * obs) override {
            observers.push_back(obs);
        };
        void removeObs(IObserver *obs) override{
            observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
        }
        void notify() override{
            for(int i=0; i<observers.size(); i++){
                observers[i]->update();
            }
        };
        
        void setNotification(INotification* n){
            if(cNotification != NULL){
                delete cNotification;
            }
            cNotification = n;
            notify();
        }

        INotification* getNotification(){
            return cNotification;
        }

        string getNotificationContent(){
            return cNotification->getContent();
        }
        ~NotificationObservable(){
            if(cNotification != NULL){
                delete cNotification;
            }
        }
};

// Singleton class
class NotificationService{
    private:
    NotificationObservable* observable;
    static NotificationService* instance;
    vector<INotification*> notification;
    NotificationService(){
        observable = new NotificationObservable();
    }
    public:
    static NotificationService* getInstance(){
        if(instance == nullptr){
            instance = new NotificationService();
        }
        return instance;
    }

    NotificationObservable* getObservable(){
        return observable;
    }

    void sendNotification(INotification* n){
        notification.push_back(n);
        observable->setNotification(n);
    }

    ~NotificationService(){
        delete observable;
    }
};

NotificationService* NotificationService::instance = nullptr;

class Logger: public IObserver{
    private:
    NotificationObservable* notificationObservable;
    public:
    Logger(){
        this->notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->add(this);
    }
    Logger(NotificationObservable* nbsable) {
        this->notificationObservable = nbsable;
        notificationObservable->add(this);
    }
    void update(){
        cout << "Logging New Notification : \n" << notificationObservable->getNotificationContent();
    }
};

class INotificationStrategy {
    public:
    virtual void sendNotification(string content) = 0;
};

class EmailStrategy : public INotificationStrategy {
private:
    string emailId;
public:

    EmailStrategy(string emailId) {
        this->emailId = emailId;
    }

    void sendNotification(string content) override {
        cout << "Sending email Notification to: " << emailId << "\n" << content;
    }
};

class SMSStrategy : public INotificationStrategy {
private:
    string mobileNumber;
public:

    SMSStrategy(string mobileNumber) {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override {
        cout << "Sending SMS Notification to: " << mobileNumber << "\n" << content;
    }
};

class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        cout << "Sending Popup Notification: \n" << content;
    }
};

class NotificationEngine: public IObserver{
    private:
    NotificationObservable* notiOable;
    vector<INotificationStrategy*> notiStgs;

    public:
    NotificationEngine(){
        this->notiOable = NotificationService::getInstance()->getObservable();
        notiOable->add(this);
    }

    NotificationEngine(NotificationObservable* nbsable){
        this->notiOable = nbsable;
    }

    void addNotificationStrategy(INotificationStrategy* ns){
        this->notiStgs.push_back(ns);
    }

    void update(){
        string notificationContent = notiOable->getNotificationContent();
        for(const auto notificationStrategy: notiStgs){
            notificationStrategy->sendNotification(notificationContent);
        }
    }
};

int main(){
    NotificationService* NS = NotificationService::getInstance();
    Logger* logger = new Logger();
    NotificationEngine* NE = new NotificationEngine();
    
    NE->addNotificationStrategy(new EmailStrategy("paras@gail.com"));
    NE->addNotificationStrategy(new SMSStrategy("+91 65686557"));
    NE->addNotificationStrategy(new PopUpStrategy());

    INotification* N = new SimpleNotification("HI Dear How Are You");
    N = new TimeStemp_Decorator(N);
    N = new Signature_Decorator(N, "Manavi");

    NS->sendNotification(N);
    delete logger;
    delete NE;
    return 0;
}