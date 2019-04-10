#include <iostream>
#include <vector>
#include <random>
#include <list>
#include <algorithm>

int randomInt(int min,int max){
    static std::default_random_engine e{};
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

void task1(){
    std::vector<int> v;
    std::cout<<"Podaj n: ";
    int n;
    std::cin>>n;
    for (int i=0;i<n;i++) v.push_back(randomInt(-20,20));
    for (int i=0;i<v.size();i++) std::cout << v[i] <<" ";
    std::cout << "\n";
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    std::cout<<"\n Podaj wartość do usunięcia: ";
    int value;
    std::cin>>value;
    // for (auto i=v.begin();i!=v.end();){
    //     if(*i==value) v.erase(i);
    //     else i++;
    // }
    //find
    auto position = std::find(v.begin(),v.end(),value);
    if (position!=v.end()) v.erase(position);
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    //min max
    std::cout << "\n min: "<< *std::min_element(v.begin(),v.end()) << " max: " << *std::max_element(v.begin(),v.end());
    std::cout<<"\n min-max: ";
    //sort
    std::sort(v.begin(),v.end());
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    std::cout<<"\n max-min: ";
    std::sort(v.begin(),v.end(),[](int a, int b){return a>b;});
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    std::cout<<"\n max-min absolute: ";
    std::sort(v.begin(),v.end(),[](int a, int b){return abs(a)>abs(b);});
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    //count
    std::cout<<"\n zliczenie: ";
    for(int i=-20;i<21;i++){
        int times = std::count(v.begin(),v.end(),i);
        if (times !=0) std::cout << i <<": " << times << ", ";
    }
}
void task2(){
    std::list<int> v;
    std::cout<<"Podaj n: ";
    int n;
    std::cin>>n;
    for (int i=0;i<n;i++) v.push_back(randomInt(-20,20));
    for (auto i:v) std::cout << i <<" ";
    std::cout << "\n";
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    std::cout<<"\n Podaj wartość do usunięcia: ";
    int value;
    std::cin>>value;
//    for (auto i=v.begin();i!=v.end();){
//         if(*i==value) i=v.erase(i);
//         else i++;
//     }
    //find
    auto position = std::find(v.begin(),v.end(),value);
    if (position!=v.end()) v.erase(position);
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    //min max
    std::cout << "\n min: "<< *std::min_element(v.begin(),v.end()) << " max: " << *std::max_element(v.begin(),v.end());
    //sort
    std::cout<<"\n min-max: ";
    v.sort();
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    std::cout<<"\n max-min: ";
    v.sort([](int a, int b){return a>b;});
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    std::cout<<"\n max-min absolute: ";
    v.sort([](int a, int b){return abs(a)>abs(b);});
    for (auto i=v.begin();i!=v.end();i++) std::cout << *i << " ";
    //count
    std::cout<<"\n zliczenie: ";
    for(int i=-20;i<21;i++){
        int times = std::count(v.begin(),v.end(),i);
        if (times !=0) std::cout << i <<": " << times << ", ";
    }
}

int main(int argc, char const *argv[])
{
    int task =1;
    while(task!=0){
        std::cout<<"Podaj numer zadania: ";
        std::cin>>task;
        switch (task)
        {
            case 1:
                task1();
                break;
            case 2:
            task2();
            break;
            default:
            std::cout<< "Nie ma takiego zadania!";
                break;
        }
        std::cout<<"\n";
    }
    return 0;
}

