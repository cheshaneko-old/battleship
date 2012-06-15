#include "battlebot.h"
#include <iostream>
void go_player_action(battleplace& bot_p);
void go_bot_action(battlebot& bot);
int main(){
    battlebot bot;
    battleplace bot_p = bot.get_battleplace();
    enum action {bot_action, player_action};
    action act = player_action;
    while(1){
        if(act == player_action){
            go_player_action(bot_p);
            act = bot_action;
        }
        else {
            go_bot_action(bot);
            act = player_action;
        }
    }
    return 0;
}

void go_player_action(battleplace& bot_p){
    int i_tmp;
    char c_tmp;
    std::cout << "Enter point ";
    std::cin >> c_tmp >> i_tmp;
    int tmp;
    tmp = bot_p.shoot(std::pair<char,int>(c_tmp, i_tmp));
    std::cout << tmp << "\n";
    if(tmp > 0){
        go_player_action(bot_p);
    }
    return;
}

void go_bot_action(battlebot& bot){
    static int state_last_hit = 0;
    static std::pair<char, int> point_last_hit;
    point_last_hit = bot.shoot((battleplace::state)state_last_hit, point_last_hit);
    std::cout << "Bot shoot on: " << point_last_hit.first << " " << point_last_hit.second << "\n" << "Enter state: ";
    std::cin >> state_last_hit;
    if(state_last_hit > 0){
        go_bot_action(bot);
    }
    return;
}


