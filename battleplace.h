#ifndef CLASS_BATTLEPLACE
#define CLASS_BATTLEPLACE
#include <vector>
#include <utility>
#include <iostream>

class battleplace{
    public:
        struct ship{
            std::vector<std::pair<char, int> > points;
        };
    private:
        ship ships[10];
        int type_of_ship[5];
        int size;
        bool in_battle(std::pair<char, int> unit);
        bool ship_check(ship unit);
    public:
        battleplace();
        int add_ship(ship unit); 
        enum state {nohit, hit, sunk, win};
        state shoot(std::pair<char, int>);
};

#endif //CLASS_BATTLEPLACE
