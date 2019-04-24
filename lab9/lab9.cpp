#include <iostream>
#include <string>
#include <map>
#include "../common.hpp"

#define overload "przekroczenie ladownosci \n"

class ship
{
private:
    std::string name;
    int capacity;
    std::map<std::string,std::pair<int,int>> cargo; 
public:
    ship(){}
    ship(std::string name, int capacity){
        this->capacity = capacity;
        this->name=name;
    }
    std::string getName()const{
        return this->name;
    }
    int getCapacity() const{
        return capacity;
    }
    

    virtual void load(std::string name,int packageAmount, int packageWeight){
        try
        {
            double loaded =0;
            for(auto it=cargo.begin();it!=cargo.end();it++){
                loaded+= it->second.first * it->second.second;
            }
            if(loaded+(packageAmount*packageWeight)>capacity*1000) throw 0;
            cargo.insert({name,std::make_pair(packageAmount,packageWeight)});
        }
        catch(int number)
        {
            std::cout << name <<": " overload;
        }      
       
    }
    void unload(std::string name, int packageAmount){
        auto iterator = cargo.find(name);
        if(iterator!=cargo.end()) iterator->second.first-=packageAmount;
    }
    void unload(){
        cargo.clear();
    }

    //ile TODO
};

void task1(){
    ship grigory("grigory",10);
    grigory.load("Banany",10,900);
    grigory.load("Kiwi",10,20);
}

int main()
{
    menu m{{{1,task1}}};
    m.run();
    return 0;
}
