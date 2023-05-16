#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

/*============ Basic classes of Factory Method ============*/

class Product {
    protected:
        Product() {}
    public:
        virtual ~Product() {}
};

class Creator {
    public:
        virtual ~Creator(){};
        virtual Product *factoryMethod() = 0;
};



/*============ Liquid ============*/

class Liquid: public Product {
    protected:
        Liquid() {}
};


/*============ CowMilk ============*/

class CowMilk: public Liquid {
    private:
        static unsigned int cost;
        static CowMilk *object;
        CowMilk() {}
    public:
        static CowMilk *make() {
            if (!object){
                object = new CowMilk();
            }
            return object;
        }
        
        static unsigned int getCost(){
            return cost;   
        }
};

CowMilk *CowMilk::object = NULL;
unsigned int CowMilk::cost = 200;


/*============ GoatMilk ============*/

class GoatMilk: public Liquid {
    private:
        static unsigned int cost;
        static GoatMilk *object;
        GoatMilk() {}
    public:
        static GoatMilk *make() {
            if (!object){
                object = new GoatMilk();
            }
            return object;
        }
        
        static unsigned int getCost(){
            return cost;   
        }
};

GoatMilk *GoatMilk::object = NULL;
unsigned int GoatMilk::cost = 300;


/*============ Animal ============*/

class Animal: public Product {
    private:
        string name;
        unsigned int age;
        bool gender; // 0 if male and 1 if female
    protected:
        Animal (string name, unsigned int age, bool gender) {
            this->name = name;
            this->age = age;
            this->gender = gender;
        }
        static const char *FemaleNames[];
        static const char *MaleNames[];
    public:
        virtual void MakeSound() = 0;
        
        string getName() const {
            return name;
        }
        
        unsigned int getAge() const {
            return age;
        }
        
        bool getGender() const {
            return gender; 
        }
        friend class AnimalCreator;
};

const char *Animal::FemaleNames[] = {
    "Dunya",
    "May",
    "March",
    "Agustina",
    "Astra",
    "Ada",
    "Vanda",
    "Belka",
    "Dasha",
    "Star"
};

const char *Animal::MaleNames[] = {
    "April",
    "Atom",
    "Bob",
    "Dux",
    "Dron",
    "Friend",
    "Jack",
    "Zahar",
    "Leo",
    "Mars",
    "Neon"
};

/*
class AnimalCreator: public Creator {
    private:
        static AnimalCreator *object;
        AnimalCreator() {}
    public:
        static AnimalCreator *make() {
            if (!object){
                object = new AnimalCreator();
            }
            return object;
        }
        virtual Animal *factoryMethod() {
            bool gend = rand() % 2;
            unsigned int age = rand() % 35;
            int nameId = rand() % 10;
            string name = (gend) ? Animal::FemaleNames[nameId] : Animal::MaleNames[nameId];
            return new Animal(name, age, gend);
        } 

};

AnimalCreator *AnimalCreator::object = NULL;
*/

/*============ Cow ============*/

class Cow : public Animal {
    private:
        unsigned int milk_ready;
        double avg_milk_yield;
    protected:
        Cow(string name, unsigned int age, bool gender, double avg_milk_yield, unsigned int milk_ready = 0)
            : Animal(name, age, gender) {
                this->avg_milk_yield = avg_milk_yield;
                this->milk_ready = milk_ready;
        }
    public:
        virtual void MakeSound() {
            cout << "Muu" << endl;
        } 
        
        bool readyToMilk() const {
            return (milk_ready == 100) ? true : false;
        }

        double milk() {
            if (this->getGender() == false) {
                cout << "It's bull" << endl;
                return 0;
            }
            if (this->readyToMilk()) {
                milk_ready = 0;
                return avg_milk_yield;
            } else {
                cout << "Cow is not ready to milk" << endl;
                return 0;
            }
        }
        
        double getAvgMilkYield() const {
            return avg_milk_yield;
        }

        unsigned int getReadyMilk() const {
            return milk_ready;
        }

        void feed() {
            if (milk_ready != 100){
                milk_ready += 20;
            }
        }
        friend class CowCreator;
};

class CowCreator: public Creator {
    private:
        static CowCreator *object;
        CowCreator() {}
    public:
        static CowCreator *make(){
            if (!object){
                object = new CowCreator();
            }
            return object;
        }
        virtual Cow *factoryMethod() {
            bool gend = rand() % 2;
            unsigned int age = rand() % 35;
            int nameId = rand() % 10;
            string name = (gend) ? Animal::FemaleNames[nameId] : Animal::MaleNames[nameId];
            double avg_milk_yield = (rand() + 800) % 1500 / 100;
            return new Cow(name, age, gend, avg_milk_yield);
        }        

};


CowCreator *CowCreator::object = NULL;


/*============ Goat ============*/

class Goat : public Animal {
    private:
        unsigned int milk_ready;
        double avg_milk_yield;
    protected:
        Goat(string name, unsigned int age, bool gender, double avg_milk_yield, unsigned int milk_ready = 0)
            : Animal(name, age, gender) {
                this->avg_milk_yield = avg_milk_yield;
                this->milk_ready = milk_ready;
        }
    public:
        virtual void MakeSound() {
            cout << "Beee" << endl;
        } 
        
        bool readyToMilk() const {
            return (milk_ready >= 100) ? true : false;
        }

        double milk() {
            if (this->getGender() == false) {
                cout << "It's bull" << endl;
                return 0;
            }
            if (this->readyToMilk()) {
                milk_ready = 0;
                return avg_milk_yield;
            } else {
                cout << "Cow is not ready to milk" << endl;
                return 0;
            }
        }
        
        double getAvgMilkYield() const {
            return avg_milk_yield;
        }

        unsigned int getReadyMilk() const {
            return milk_ready;
        }


        void feed() {
            if (milk_ready != 100){
                milk_ready += 20;
            }
        }
        friend class GoatCreator;
};

class GoatCreator: public Creator {
    private:
        static GoatCreator *object;
        GoatCreator() {}
    public:
        static GoatCreator *make() {
            if (!object){
                object = new GoatCreator();
            }
            return object;
        }
        virtual Goat *factoryMethod() {
            bool gend = rand() % 2;
            unsigned int age = rand() % 18;
            int nameId = rand() % 10;
            string name = (gend) ? Animal::FemaleNames[nameId] : Animal::MaleNames[nameId];
            double avg_milk_yield = (rand() + 300) % 700 / 100;
            return new Goat(name, age, gend, avg_milk_yield);
        }        

};


GoatCreator *GoatCreator::object = NULL;

/*============ Container ============*/

class Container: public Product {
    private:
        double cur_volume;
        double volume;
        Liquid *content;
    protected:
        Container (double volume, double cur_volume = 0, Liquid *content = NULL) {
            this->volume = volume;
            this->cur_volume = cur_volume;
            this->content = content;
        }      
    public:   
        bool fillUp (const double add_volume ){
            cur_volume += add_volume;
            if (cur_volume <= volume){
                return true;
            } else {
                cout << "container is already full. Poured out: " << cur_volume - volume << endl;
                cur_volume = volume;
                return false;
            }
        }
        
        Liquid *getLiquid(){
            return content;
        }
        
        void putLiquid(Liquid *content){
            this->content = content;
        }

        double fillOut(const double out_volume){
            if (out_volume <= cur_volume) {
                cur_volume -= out_volume;
                return out_volume;
            } else {
                cout << "Not enough fluid. It was taken: " << cur_volume << endl;
                return cur_volume;
            }
        }
        
        double getCurVolume() const {
            return cur_volume;
        }
        
        double getVolume() const {
            return volume;
        }
        
        friend class ContainerCreator;
};

class ContainerCreator: public Creator {
    private:
        
        static ContainerCreator *object;
        ContainerCreator() {}
    public:
        
        static ContainerCreator *make() {
            if (!object){
                object = new ContainerCreator();
            }
            return object;
        }
        
        virtual Container *factoryMethod() {
            cout << "write max value of container: ";
            double volume;
            cin >> volume;
            return new Container(volume);
        }        

};

ContainerCreator *ContainerCreator::object = NULL;


/*============ Bucket ============*/

class Bucket : public Container {
    private:
        Bucket(double cur_volume = 0)
            : Container(12, cur_volume){}
    public:
        friend class BucketCreator;
};

class BucketCreator: public Creator {
    private:
        static BucketCreator *object;
        BucketCreator() {}
    public:
        static BucketCreator *make() {
            if (!object){
                object = new BucketCreator();
            }
            return object;
        }
        virtual Bucket *factoryMethod() {
            return new Bucket();
        }        

};

BucketCreator *BucketCreator::object = NULL;


/*============ Can ============*/

class Can : public Container {
    private:
        Can(double cur_volume = 0)
            : Container(23, cur_volume){}
    public:
        friend class CanCreator;
};

class CanCreator: public Creator {
    private:
        static CanCreator *object;
        CanCreator() {}
    public:
        static CanCreator *make() {
            if (!object){
                object = new CanCreator();
            }
            return object;
        }
        virtual Can *factoryMethod() {
            return new Can();
        }        

};

CanCreator *CanCreator::object = NULL;

/*============ Tank ============*/

class Tank : public Container {
    private:
        Tank(double cur_volume = 0)
            : Container(1000, cur_volume){}
    public:
        friend class TankCreator;
};

class TankCreator: public Creator {
    private:
        static TankCreator *object;
        TankCreator() {}
    public:
        static TankCreator *make() {
            if (!object){
                object = new TankCreator();
            }
            return object;
        }
        virtual Tank *factoryMethod() {
            return new Tank();
        }        

};

TankCreator *TankCreator::object = NULL;


/*============ Farm ============*/

class Farm {
    private:
        CowCreator *cow_create;
        GoatCreator *goat_create;
        BucketCreator *bucket_create;
        CanCreator *can_create;
        TankCreator *tank_create;
        
        CowMilk *cmilk;
        GoatMilk *gmilk;

        string cmd;

        Cow **cows;
        int cur_cows;
        int max_cows;
        
        Goat **goats;
        int cur_goats;
        int max_goats;
        
        Bucket **buckets;
        int cur_buckets;
        int max_buckets;
        
        Can **cans;
        int cur_cans;
        int max_cans;
        
        Tank **tanks;
        int cur_tanks;
        int max_tanks;

        long money;

        static Farm *object;
        
        enum state { welcome, help, stat, shop, milk, feed, exit, error } curstate;
        enum prices { cowPr = 30000, goatPr = 20000, bucketPr = 1000, canPr = 5000, tankPr = 10000, expandPr = 40000 }; 
        static string cmdStr[exit];
        
        static state command(string str) {
            for (int i = help; i <= exit; ++i) {
                if (str == cmdStr[i - 1]){
                    return static_cast<state>(i);
                }
            }
            return error;
        }

        Farm();

        void cowExpansion();
        void goatExpansion();
        
        void bucketExpansion();
        void canExpansion();
        void tankExpansion();

        double bucketFill(double milk, Liquid *kind_milk);       
        double canFill(double milk, Liquid *kind_milk);       
        double tankFill(double milk, Liquid *kind_milk);
        
        double bucketOut(Liquid *kind_milk);
        double canOut(Liquid *kind_milk);
        double tankOut(Liquid *kind_milk);

        void milkCows();
        void milkGoats(); 
        
        void feedCows();
        void feedGoats();
        
        void buyCows();
        void buyGoats();

        void buyBucket();
        void buyCan();
        void buyTank();
        
        void sellCowMilk();
        void sellGoatMilk();
        
    public:
        static Farm *make() {
            if(!object) {
                object = new Farm();
            }
            return object;
        }
        
        void printInfo();
        
        void printCows();

        void printGoats();

        void start();
        void nextStep();

        ~Farm();

};

Farm *Farm::object = NULL;
string Farm::cmdStr[exit] = {"help", "stat", "shop", "milk", "feed", "exit"};

Farm::Farm()
{
    cow_create = CowCreator::make();
    goat_create = GoatCreator::make();
    bucket_create = BucketCreator::make();
    can_create = CanCreator::make();
    tank_create = TankCreator::make();
            
    cmilk = CowMilk::make();
    gmilk = GoatMilk::make();

    curstate = welcome;

    cows = new Cow*[5];
    cur_cows = 0;
    max_cows = 5;
            
    goats = new Goat*[10];
    cur_goats = 0;
    max_goats = 10;

    buckets = new Bucket*[10];
    cur_buckets = 0;
    max_buckets = 10;

    cans = new Can*[10];
    cur_cans = 0;
    max_cans = 10;

    tanks = new Tank*[10];
    cur_tanks = 0;
    max_tanks = 10;

    money = 100000;
}

Farm::~Farm()
{
    int i = 0;
    for (i = 0; i < cur_cows; ++i) {
        delete cows[i];
    }
    delete [] cows;

    for (i = 0; i < cur_goats; ++i) {
        delete goats[i];
    }
    delete [] goats;

    for (i = 0; i < cur_buckets; ++i) {
        delete buckets[i];
    }
    delete [] buckets;

    for (i = 0; i < cur_cans; ++i) {
        delete cans[i];
    }
    delete [] cans;

    for (i = 0; i < cur_tanks; ++i) {
        delete tanks[i];
    }
    delete [] tanks;

    delete cmilk;
    delete gmilk;
    delete cow_create;
    delete goat_create;
    delete bucket_create;
    delete can_create;
    delete tank_create;
}

void Farm::cowExpansion()
{
    if (money < expandPr * max_cows){
        cout << "Not enough money for expension" << endl;
        return;
    }
    money -= expandPr * max_cows;
    max_cows *=2;
    Cow **tmp = new Cow*[max_cows];
    for (int i = 0; i < cur_cows; ++i){
        tmp[i] = cows[i];
    }
    delete [] cows;
    cows = tmp;
}
void Farm::goatExpansion()
{
    if (money < expandPr * max_goats){
        cout << "Not enough money for expension" << endl;
        return;
    }
    money -= expandPr * max_goats;
    max_goats *=2;
    Goat **tmp = new Goat*[max_goats];
    for (int i = 0; i < cur_goats; ++i){
        tmp[i] = goats[i];
    }
    delete [] goats;
    goats = tmp;
}

void Farm::bucketExpansion()
{
    max_buckets *=2;
    Bucket **tmp = new Bucket*[max_buckets];
    for (int i = 0; i < cur_buckets; ++i){
        tmp[i] = buckets[i];
    }
    delete [] buckets;
    buckets = tmp;
}

void Farm::canExpansion()
{
    max_cans *=2;
    Can **tmp = new Can*[max_cans];
    for (int i = 0; i < cur_cans; ++i){
        tmp[i] = cans[i];
    }
    delete [] cans;
    cans = tmp;
}

void Farm::tankExpansion() {
    max_tanks *=2;
    Tank **tmp = new Tank*[max_tanks];
    for (int i = 0; i < cur_tanks; ++i){
        tmp[i] = tanks[i];
    }
    delete [] tanks;
    tanks = tmp;
}

double Farm::tankFill(double milk, Liquid *kind_milk)
{
    if (milk == 0){
        return 0;
    }
    for (int i = 0; i < cur_tanks; ++i){
        if (!((tanks[i])->getLiquid())){
            (tanks[i])->putLiquid(kind_milk); 
        }
        if ((tanks[i])->getLiquid() != kind_milk){
            continue;
        }
        double fill = (tanks[i])->getVolume() - (tanks[i])->getCurVolume();
        if (milk <= fill) {
            fill = milk;
        }
        if (!((tanks[i])->fillUp(fill))){
            continue;
        }
        milk -= fill;
    }
    return milk;            
}

double Farm::tankOut(Liquid *kind_milk)
{
    double milk = 0;
    for (int i = 0; i < cur_tanks; ++i){
        if ((tanks[i])->getLiquid() != kind_milk){
            continue;
        }
        double out = (tanks[i])->getCurVolume();
        milk += (tanks[i])->fillOut(out);
        (tanks[i])->putLiquid(NULL);
    }
    return milk;            
}

double Farm::canOut(Liquid *kind_milk)
{
    double milk = 0;
    for (int i = 0; i < cur_cans; ++i){
        if ((cans[i])->getLiquid() != kind_milk){
            continue;
        }
        double out = (cans[i])->getCurVolume();
        milk += (cans[i])->fillOut(out);
        (cans[i])->putLiquid(NULL);
    }
    return milk;            
}

double Farm::bucketOut(Liquid *kind_milk)
{
    double milk = 0;
    for (int i = 0; i < cur_buckets; ++i){
        if ((buckets[i])->getLiquid() != kind_milk){
            continue;
        }
        double out = (buckets[i])->getCurVolume();
        milk += (buckets[i])->fillOut(out);
        (buckets[i])->putLiquid(NULL);
    }
    return milk;            
}

double Farm::canFill(double milk, Liquid *kind_milk)
{
    if (milk == 0){
        return 0;
    }
    for (int i = 0; i < cur_cans; ++i){
        if (!((cans[i])->getLiquid())){
            (cans[i])->putLiquid(kind_milk); 
        }
        if ((cans[i])->getLiquid() != kind_milk){
            continue;
        }
        double fill = (cans[i])->getVolume() - (cans[i])->getCurVolume();
        if (milk <= fill) {
            fill = milk;
        }
        if (!((cans[i])->fillUp(fill))){
            continue;
        }
        milk -= fill;
    }
    return milk;            
}

double Farm::bucketFill(double milk, Liquid *kind_milk)
{
    if (milk == 0){
        return 0;
    }
    for (int i = 0; i < cur_buckets; ++i){
        if (!((buckets[i])->getLiquid())){
            (buckets[i])->putLiquid(kind_milk); 
        }
        if ((buckets[i])->getLiquid() != kind_milk){
            continue;
        }
        double fill = (buckets[i])->getVolume() - (buckets[i])->getCurVolume();
        if (milk <= fill) {
            fill = milk;
        }
        if (!((buckets[i])->fillUp(fill))){
            continue;
        }
        milk -= fill;
    }
    return milk;            
}

void Farm::milkCows()
{
    double milk = 0;
    for (int i = 0; i < cur_cows; ++i){
        if (((cows[i])->getGender()) && ((cows[i])->readyToMilk())){
            milk += (cows[i])->milk();
        }
    }
    milk = tankFill(milk, cmilk);
    milk = canFill(milk, cmilk);
    milk = bucketFill(milk, cmilk);
    if ( milk != 0){
        cout << "Spilled milk: " << milk << endl;
    } else {
        cout << "All cows are successfully milked" << endl;
    }
}

void Farm::milkGoats()
{
    double milk = 0;
    for (int i = 0; i < cur_goats; ++i){
        if (((goats[i])->getGender()) && ((goats[i])->readyToMilk())){
            milk += (goats[i])->milk();
        }
    }
    milk = tankFill(milk, gmilk);
    milk = canFill(milk, gmilk);
    milk = bucketFill(milk, gmilk);
    if ( milk != 0){
        cout << "Spilled milk: " << milk << endl;
    } else {
        cout << "All goats are successfully milked" << endl;
    }
}

void Farm::feedCows()
{
    for (int i = 0; i < cur_cows; ++i) {
        (cows[i])->feed();
    }
    cout << "All cows are fed" << endl;
}

void Farm::feedGoats()
{
    for (int i = 0; i < cur_goats; ++i) {
        (goats[i])->feed();
    }
    cout << "All goats are fed" << endl;
}

void Farm::buyCows()
{
    int num = 0;
    cout << "Write number of buying animals: ";
    cin >> num;
    if (cur_cows + num > max_cows){
        cout << "Not enough place" << endl;
        return;
    }
    if (money < cowPr * num) {
        cout << "Not enough money" << endl;
        return;
    }
    money -= cowPr * num;
    for (int i = cur_cows; i < cur_cows + num; ++i) {
        cows[i] = cow_create->factoryMethod();
    }
    cur_cows += num;
    cout << "Purchase successfully made" << endl;
}

void Farm::buyGoats()
{
    int num = 0;
    cout << "Write number of buying animals: ";
    cin >> num;
    if (cur_goats + num > max_goats){
        cout << "Not enough place" << endl;
        return;
    }
    if (money < goatPr * num) {
        cout << "Not enough money" << endl;
        return;
    }
    money -= goatPr * num;
    for (int i = cur_goats; i < cur_goats + num; ++i) {
        goats[i] = goat_create->factoryMethod();
    }
    cur_goats += num;
    cout << "Purchase successfully made" << endl;
}

void Farm::buyBucket()
{
    int num = 0;
    cout << "Write number of buying items: ";
    cin >> num;
    if (money < bucketPr * num) {
        cout << "Not enough money" << endl;
        return;
    }
    if (cur_buckets + num <= max_buckets){
        bucketExpansion();
    }
    money -= bucketPr * num;
    for (int i = cur_buckets; i < cur_buckets + num; ++i) {
        buckets[i] = bucket_create->factoryMethod();
    }
    cur_buckets += num;
    cout << "Purchase successfully made" << endl;

}

void Farm::buyCan()
{
    int num = 0;
    cout << "Write number of buying items: ";
    cin >> num;
    if (money < canPr * num) {
        cout << "Not enough money" << endl;
        return;
    }
    if (cur_cans + num <= max_cans){
        canExpansion();
    }
    money -= canPr * num;
    for (int i = cur_cans; i < cur_cans + num; ++i) {
        cans[i] = can_create->factoryMethod();
    }
    cur_cans += num;
    cout << "Purchase successfully made" << endl;

}

void Farm::buyTank()
{
    int num = 0;
    cout << "Write number of buying items: ";
    cin >> num;
    if (money < tankPr * num) {
        cout << "Not enough money" << endl;
        return;
    }
    if (cur_tanks + num <= max_tanks){
        bucketExpansion();
    }
    money -= tankPr * num;
    for (int i = cur_tanks; i < cur_tanks + num; ++i) {
        tanks[i] = tank_create->factoryMethod();
    }
    cur_tanks += num;
    cout << "Purchase successfully made" << endl;

}

void Farm::sellCowMilk()
{
    double milk = 0;
    milk += tankOut(cmilk);
    milk += canOut(cmilk);
    milk += bucketOut(cmilk);
    money += milk * (cmilk->getCost());
}

void Farm::sellGoatMilk()
{
    double milk = 0;
    milk += tankOut(gmilk);
    milk += canOut(gmilk);
    milk += bucketOut(gmilk);
    money += milk * (gmilk->getCost());
}

void Farm::printInfo()
{
    cout << "You have:" << endl;
    cout << "Money: " << money << endl;
    cout << "Cows: " << cur_cows << endl;
    cout << "Size of cowshed: " << max_cows << endl;
    cout << endl;
    cout << "Goats: " << cur_goats << endl;
    cout << "Size of goatshed: " << max_goats << endl;
    cout << endl;
    cout << "Buckets: " << cur_buckets << endl;
    cout << "Cans: " << cur_cans << endl;
    cout << "Tanks: " << cur_tanks << endl;
}

void Farm::printCows() {
    cout << "Cows at farm:" << endl;
    for (int i = 0; i < cur_cows; ++i){
        const char *gender = (cows[i])->getGender() ? "Female" : "Male";
        cout << "Name: " << (cows[i])->getName() << "; Gender: " << gender << "; Age: " << (cows[i])->getAge() << endl;
    }
    cout << endl;
}

void Farm::printGoats() {
    cout << "Goats at farm:" << endl;
    for (int i = 0; i < cur_goats; ++i){
        const char *gender = (goats[i])->getGender() ? "Female" : "Male";
        cout << "Name: " << (goats[i])->getName() << "; Gender: " << gender << "; Age: " << (goats[i])->getAge() << endl;
    }
    cout << endl;
}

void Farm::start()
{
    cout << "Welcome to the farm!" << endl;
    bool off_flag = false;
    nextStep();
    while(!off_flag) {
        cin >> cmd;
        curstate = command(cmd);
        nextStep();
        off_flag = (curstate == exit);
    }
}

void Farm::nextStep()
{
    int tmp = 0;
    switch(curstate) {
        case welcome:
        case help:
            cout << "List of command:" << endl;
            cout << "help - print list of command" << endl;
            cout << "stat - statistic of farm" << endl;
            cout << "shop - place to buy or sell what you want" << endl;
            cout << "milk - milk your pets" << endl;
            cout << "feed - feed your pets" << endl;
            cout << "exit - close farm" << endl;
            break;
        case stat:
            printInfo();
            cout << "Chose number of option:" << endl;
            cout << "1. Information about cows" << endl;
            cout << "2. information about goats" << endl;
            cout << "3. back" << endl;
            cin >> tmp;
            switch (tmp){
                case 1:
                    printCows();
                    break;
                case 2:
                    printGoats();
                    break;
                case 3:
                default:
                    break;
            }
            break;
        case shop:
            cout << "Chose number of option:" << endl;
            cout << "1. Buy cows (" << cowPr << ")" << endl;
            cout << "2. Buy goats (" << goatPr << ")" << endl;
            cout << "3. Buy buckets (" << bucketPr << ")" << endl;
            cout << "4. Buy cans (" << canPr << ")" << endl;
            cout << "5. Buy tanks (" << tankPr << ")" << endl;
            cout << "6. Expand the cowshed (" << expandPr << ")" << endl;
            cout << "7. Expand the goatshed (" << expandPr << ")" << endl;
            cout << "8. Sell cow's milk (" << cmilk->getCost()  << ")" << endl;
            cout << "9. Sell goat's milk (" << gmilk->getCost() << ")" << endl;
            cout << "10. Sell all milk" << endl;
            cout << "11. back" << endl;
            cin >> tmp;
            switch (tmp){
                case 1:
                    buyCows();
                    break;
                case 2:
                    buyGoats();
                    break;
                case 3:
                    buyBucket();
                    break;
                case 4:
                    buyCan();
                    break;
                case 5:
                    buyTank();
                    break;
                case 6:
                    cowExpansion();
                    break;
                case 7:
                    goatExpansion();
                    break;
                case 8:
                    sellCowMilk();
                    break;
                case 9:
                    sellGoatMilk();
                    break;
                case 10:
                    sellCowMilk();
                    sellGoatMilk();
                case 11:
                default:
                    break;
            }
            break;
        case milk:
            cout << "Chose number of option:" << endl;
            cout << "1. Milk cows" << endl;
            cout << "2. Milk goats" << endl;
            cout << "3. Milk all animals" << endl;
            cout << "4. back" << endl;
            cin >> tmp;
            switch (tmp){
                case 1:
                    milkCows();
                    break;
                case 2:
                    milkGoats();
                    break;
                case 3:
                    milkCows();
                    milkGoats();
                case 4:
                default:
                    break;
            }
            break;
        case feed:
            cout << "Chose number of option:" << endl;
            cout << "1. Feed cows" << endl;
            cout << "2. Feed goats" << endl;
            cout << "3. Feed all animals" << endl;
            cout << "4. back" << endl;
            cin >> tmp;
            switch (tmp){
                case 1:
                    feedCows();
                    break;
                case 2:
                    feedGoats();
                    break;
                case 3:
                    feedCows();
                    feedGoats();
                case 4:
                default:
                    break;
            }
            break;
        case exit:
            cout << "Goodbuy! See you at the farm." << endl;
            break;
        case error:
        default:
            cout << "Unexpected command. Try again." << endl;
    }
    cout << "=========================" << endl;
}

int main(void)
{
    srand(time(NULL));
    Farm *milk_farm = Farm::make();
    milk_farm->start();
    return 0;
}
