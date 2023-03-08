#include <iostream>
#include <string>

using namespace std;

class Animal {
    private:
        string name;
        unsigned int age;
        bool gender; // 0 if male and 1 if female
    public:
        Animal (string name, unsigned int age, bool gender) {
            this->name = name;
            this->age = age;
            this->gender = gender;
        }
        
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
};

class Cow : public Animal {
    private:
        unsigned int milk_ready;
        double avg_milk_yield;
    public:
        Cow(string name, unsigned int age, bool gender, double avg_milk_yield, unsigned int milk_ready = 0)
            : Animal(name, age, gender) {
                this->avg_milk_yield = avg_milk_yield;
                this->milk_ready = milk_ready;
        }

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

};

class Liquid {
    private:
        string name;
    public:
        Liquid (string name) {
            this->name = name;
        }
        
        string getName() const {
            return name;
        }
        
};

class Container {
    private:
        double cur_volume;
        double volume;
    public:
        Container (double volume, double cur_volume = 0) {
            this->volume = volume;
            this->cur_volume = cur_volume;
        }      
        
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
        double fillOut(const double out_volume){
            if (out_volume < cur_volume) {
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
};

class Bucket : public Container {
    public:
        Bucket(double cur_volume = 0)
            : Container(12, cur_volume){}
};

class Can : public Container {
    public:
        Can(double cur_volume = 0)
            : Container(23, cur_volume){}
};

int main(void)
{
    Cow dunya("Dunya", 7, true, 30, 100);
    cout << dunya.readyToMilk() << endl;
    double milk = dunya.milk();
    dunya.MakeSound();

    Bucket b;
    cout << b.fillUp(milk) << endl;
    cout << "milk in bucket: " << b.getCurVolume() << endl;
    cout << b.fillOut(15) << endl;
    return 0;
}
