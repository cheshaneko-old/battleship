#include "battleplace.h"

battleplace::battleplace(){
    size = 0;
    type_of_ship[1]=4;
    type_of_ship[2]=3;
    type_of_ship[3]=2;
    type_of_ship[4]=1;
}

int battleplace::add_ship(ship unit){
    if(!ship_check(unit)){
        std::cerr << "broken ship\n";
        return 1;
    }
    int size_of_ship = unit.points.size();
    if(!((size_of_ship<=4) && (size_of_ship>=1))){
        std::cerr << "Ship don't added cose ship > 4 or <0\n";
        return 1;
    }
    if(type_of_ship[size_of_ship]==0){
        std::cerr << "Ship don't added cose too much ship of type\n";
        return 1;
    }
    if(size==10){
        std::cerr << "Ship don't added cose too mush ships\n";
        return 1;
    }
    for(int i = 0; i < size_of_ship;++i){
        if(in_battle(unit.points[i])\
            || in_battle(std::pair<char, int>(unit.points[i].first-1,unit.points[i].second-1))\
            || in_battle(std::pair<char, int>(unit.points[i].first-1,unit.points[i].second))\
            || in_battle(std::pair<char, int>(unit.points[i].first-1,unit.points[i].second+1))\
            || in_battle(std::pair<char, int>(unit.points[i].first,unit.points[i].second+1))\
            || in_battle(std::pair<char, int>(unit.points[i].first+1,unit.points[i].second+1))\
            || in_battle(std::pair<char, int>(unit.points[i].first+1,unit.points[i].second))\
            || in_battle(std::pair<char, int>(unit.points[i].first+1,unit.points[i].second-1))\
            || in_battle(std::pair<char, int>(unit.points[i].first,unit.points[i].second-1))\
            
        ){
            std::cerr << "Ship don't added cose ships intersect\n";
            return 1;
        }
    }
        ships[size] = unit;
        size++;
        type_of_ship[size_of_ship]--;
        std::cerr << "Ship added\n";
        return 0;
}

bool battleplace::in_battle(std::pair<char, int> unit){
   for(int i = 0; i < size; ++i){
       for(int j = 0; j < ships[i].points.size(); ++i){
           if (ships[i].points[j]==unit)
               return true;
       }
   }
   return false;
}

battleplace::state battleplace::shoot(std::pair<char, int> unit){
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < ships[i].points.size(); ++j){
            if(unit==ships[i].points[j]){
                ships[i].points[j]=ships[i].points[ships[i].points.size()-1];
                ships[i].points.pop_back();
                if(ships[i].points.empty()){
                    ships[i]=ships[size-1];
                    size--;
                    if(size==0){
                        return win;
                    } 
                    else{
                        return sunk;
                    }
                }
                return hit;
            }
        }
    }
    return nohit;
}

bool battleplace::ship_check(ship unit){
    for(int i = 0; i < unit.points.size(); ++i){
        if(!((unit.points[i].first<='j') &&\
             (unit.points[i].first>='a') &&\
             (unit.points[i].second>=1)  &&\
             (unit.points[i].second<=10))){
            std::cerr << "point outside of field\n";
            return false;
        }
    }
    if(!unit.points.empty()){
        char ctmp = unit.points[0].first;
        int itmp = unit.points[0].second;
        bool f_check = true;
        bool s_check = true;
        for(int i = 0; i < unit.points.size(); ++i){
            if(unit.points[i].first!=ctmp)
                f_check = false;
            if(unit.points[i].second!=itmp)
                s_check = false;
        }
        return f_check || s_check;
    }
    else{
        std::cerr << "Empty ship\n";
        return false;
    }
    std::cerr << "something wrong\n";
    return false;
}
