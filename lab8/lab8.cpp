#include <iostream>
#include <string>
#include <regex>
#include<fstream>

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
    else std::cout<<"cannot open file\n";
    i.close();
}

bool check2(std::string number){
    std::regex pattern("-.");
    std::smatch result;
    if(std::regex_search(number,result,pattern)) return 0;
    else {
        std::cout<<"else\n";
        std::regex pattern2("\d*");
        if(std::regex_search(number,result,pattern2)) return 1;
        else return 0;
    }
}

void task2(){
    if(check2("50,0"))std::cout<<"passed\n";
    else std::cout<<"failed\n";
}

int main()
{
    task2();
    return 0;
}
