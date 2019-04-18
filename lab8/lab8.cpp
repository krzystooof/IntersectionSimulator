#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include "../menu.hpp"

#define cannotOpenFile "\n cannot open file\n"

bool check1(std::string line){
    std::regex pattern("Adam( )+Nowak( )+680510.");
    std::smatch result;
    if(std::regex_search(line,result,pattern)) return 1;
    else return 0;
}


void task1(){
    std::ifstream i;
    i.open("kartoteka.txt");
    std::string line;
    int number=0;
    if(i.is_open()){
        while(std::getline(i,line)){
            if(check1(line))std::cout<<number<<"\n";
            else std::cout<<"0\n";
            number++;
        }
    }
    else std::cout<<cannotOpenFile;
    i.close();
}

bool check2(std::string number){
    //if letter or minus on beggining or mark - return false
    std::regex pattern("[[:alpha:]]|-.|\d*[[:punct:]]\d*");
    std::smatch result;
    if(std::regex_search(number,result,pattern))return false;
    else return true;
}

void task2(){
    std::ifstream i;
    i.open("dane1.txt");
    std::ofstream o;
    o.open("dane2.txt");
    std::string line;
    if(i.is_open() || o.good()){
        while (std::getline(i,line)){
            bool good = true;
            std::istringstream s(line);
            std::string a;
            while (s>>a && good ==true){
                if (check2(a)!=true)good=false;
            }
            if(good==true) o << line <<"\n";
        }
    }
    else std::cout<<cannotOpenFile;
    i.close();
    o.close();
}

int main()
{
    menu m {{{1,task1},{2,task2}}};
    m.run();
    return 0;
}
