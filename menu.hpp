//copied from StackOverflow
#pragma once

#include <algorithm>  //all_of
#include <functional> //std::function
#include <iostream>
#include <vector>

constexpr auto red = "\033[31m";
constexpr auto green = "\033[32m";
constexpr auto yellow = "\033[33m";
constexpr auto blue = "\033[34m";
constexpr auto magenta = "\033[35m";
constexpr auto cyan = "\033[36m";
constexpr auto reset = "\033[0m";

class menu {
    std::vector<std::pair<int, std::function<void()>>> functions_index;

    inline void clear_term() {
#ifdef _WIN32
        system("CLS");
#else
        system("clear");
#endif
    }

    void print_menu() {
        std::cout << blue << "Choose exercise:\n";

        for (const auto &i : functions_index)
            std::cout << "[" << i.first << "] ";

        std::cout << "\t[q]" << reset << "\n> ";
    }

public:
    menu(std::vector<std::pair<int, std::function<void()>>> v)
        : functions_index(v) {}

    inline void run() {
        std::string command;
        int command_number;

        
#ifdef _WIN32
        system("");
#endif

        while (1) {
            print_menu();
            std::cin >> command;

            if (command == "q")
                break;
            else if (std::all_of(command.begin(), command.end(),
                     [](char c) { return isdigit(c); })) {
                command_number = stoi(command);
                auto choosen = std::find_if(functions_index.begin(),
                                            functions_index.end(),
                                            [&command_number](auto current) {
                                            return current.first == command_number; });

                if (choosen != std::end(functions_index)) {
                    clear_term();
                    choosen->second();
                    std::cout << '\n';
                } else
                    std::cerr << red << "error:" << reset << " wrong number\n";
            } else
                std::cerr << red << "error:" << reset << " invalid input\n";
        }
    }
};