#include <iostream>
#include <string>
#include <map>
#include <sstream>

#define overload "przekroczenie ladownosci \n"

int smallShipsMaxPackageWeight=0;

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
    std::string getLoad() const{
        std::string result;
        for(auto it=cargo.begin();it!=cargo.end();it++){
                result += it->first + ": " + std::to_string(it->second.first) + " " + std::to_string(it->second.second) +"\n";
        }
        return result;
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
        try
        {
            auto iterator = cargo.find(name);
            if(packageAmount>iterator->second.first)throw 0;
            if(iterator!=cargo.end()) iterator->second.first-=packageAmount;
        }
        catch(int number)
        {
            std::cout<<name<<": za mało towaru\n";
        }
        
    }
    void unload(std::string name){
        auto iterator = cargo.find(name);
        if(iterator!=cargo.end()) cargo.erase(iterator);
    }
    void unload(){
        cargo.clear();
    }

    //ile TODO
};

class smallShip:public ship{
private:

public:
    smallShip(){}
    smallShip(std::string name, int capacity):ship(name,capacity){}
    virtual void load(std::string name,int packageAmount, int packageWeight){
        if(packageWeight>smallShipsMaxPackageWeight)std::cout<< name <<": za cięzka paczka\n";
        else ship::load(name,packageAmount,packageWeight);
    }
};

void readTask(std::string line,ship &SHIP){
    std::istringstream input(line);
    std::string rest;
    if (line[0]=='Z'){
        std::string name;
        int amount,weight;
        input>>rest>>name>>amount>>weight;
        SHIP.load(name,amount,weight);
    }
    else if(line[0]=='S'){
            std::cout << SHIP.getLoad();
    }
    else if (line[0]=='W'){
        std::string name;
        int amount;
        input>>rest>>name>>amount;
        SHIP.unload(name,amount);
    }
    else if (line[0]=='O')SHIP.unload();
    else if(line[0]=='-'){
        std::string name;
        input>>rest>>name;
        SHIP.unload(name);
    }

}


int main()
{
    std::string name;
    int maxLoad;
    std::cout<<"Podaj nazwe statku i ladownosc (t): ";
    std::cin>>name>>maxLoad;
    ship* SHIP = new smallShip(name,maxLoad);
    std::cout << "Podaj maksymalna wage paczki dla malych statkow (kg): ";
    std::cin>>smallShipsMaxPackageWeight;    

    std::string input ="";
    while(input!="q"){
        std::cout<<"1. Wczytywanie polecen z klawiatury\t 2. Wczytywanie polecen z pliku\t q - wyjscie\n";
        std::cin>>input;
        if(input=="1"){
            std::cout<<"Podaj polecenie, a nastepnie nacisnij ENTER. Podaj q aby wyjsc\n";
            while(input!="q"){
            getline(std::cin,input);
            readTask(input,*SHIP);
            }
        }
    }
    
    return 0;
}
