#ifndef CLASS_BATTLEBOT
#define CLASS_BATTLEBOT
#include <vector>
#include <utility>
#include "battleplace.h"

class battlebot{
    private:
        std::vector< std::pair<char, int> > points;
        std::vector< std::pair<char, int> > points_on_hit;
        battleplace my_battleplace;
        bool delete_point(std::pair<char, int> point);
        std::pair<char, int> previous_hit_point;
        battleplace create_battleplace();
    public:
        battlebot();
        std::pair<char, int> shoot(battleplace::state last_hit, std::pair<char, int> last_hit_point);
        battleplace get_battleplace();
};

#endif //CLASS_BATTLEBOT


