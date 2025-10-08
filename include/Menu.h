#ifndef MENU_H
#define MENU_H
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <limits>
class Menu
{
    Menu() = default;
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    std::map<int, std::pair<std::string, std::function<void()>>> items_;
public:
    static Menu& getInstance(){
        static Menu instance;
        return instance;
    }
    void addItem(int option, const std::string& description, std::function<void()> action){
        items_[option] = {description, std::move(action)};
    }
    void showAndExecute(){
        for(auto&[option,it]: items_){
            std::cout<<option<<"."<<it.first<<'\n';
        }
        std::cout<<"Alege o optiune: ";
        int choice;
        if(!(std::cin>>choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"Intrare invalida.\n";
            return;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        auto it = items_.find(choice);
        if (it != items_.end()){
            it->second.second();
        }else{
            std::cout<<"Optiune invalida.\n";
        }
    }
};

#endif // MENU_H
