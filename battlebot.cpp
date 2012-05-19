#include "battlebot.h"
#include <cstdlib>
battlebot::battlebot(){
    for(int i = 0; i < 100; ++i){
        points.push_back(std::pair<char,int>('a'+i/10,i%10+1));
    }
    srandom(1);
	/*battleplace::ship a1;
	battleplace::ship a2;
	battleplace::ship a3;
	battleplace::ship a4;
	battleplace::ship a5;
	battleplace::ship a6;
	battleplace::ship a7;
	battleplace::ship a8;
	battleplace::ship a9;
	battleplace::ship a10;
	
	a1.points.push_back(std::pair<char,int>('a',1));
	a1.points.push_back(std::pair<char,int>('b',1));
	
	a2.points.push_back(std::pair<char,int>('b',2));
	
	a3.points.push_back(std::pair<char,int>('a',10));
	a3.points.push_back(std::pair<char,int>('b',10));
	
	a4.points.push_back(std::pair<char,int>('e',2));
	
	a5.points.push_back(std::pair<char,int>('d',4));
	
	a6.points.push_back(std::pair<char,int>('d',6));
	a6.points.push_back(std::pair<char,int>('d',7));
	a6.points.push_back(std::pair<char,int>('d',8));
	
	a7.points.push_back(std::pair<char,int>('i',1));
	a7.points.push_back(std::pair<char,int>('l',1));
	
	a8.points.push_back(std::pair<char,int>('f',4));
	a8.points.push_back(std::pair<char,int>('g',4));
	a8.points.push_back(std::pair<char,int>('h',4));
	a8.points.push_back(std::pair<char,int>('i',4));
	
	a9.points.push_back(std::pair<char,int>('h',7));
	
	a10.points.push_back(std::pair<char,int>('h',10));
	a10.points.push_back(std::pair<char,int>('i',10));
	a10.points.push_back(std::pair<char,int>('j',10));
	
	my_battleplace.add_ship(a1);
	my_battleplace.add_ship(a2);
	my_battleplace.add_ship(a3);
	my_battleplace.add_ship(a4);
	my_battleplace.add_ship(a5);
	my_battleplace.add_ship(a6);
	my_battleplace.add_ship(a7);
	my_battleplace.add_ship(a8);
	my_battleplace.add_ship(a9);
	my_battleplace.add_ship(a10);*/
}

battleplace battlebot::get_battleplace(){
    return my_battleplace;
}

bool battlebot::delete_point(std::pair<char, int> point){
    for(int i = 0; i < points.size(); ++i){
        if(points[i]==point){
            points[i]=points[points.size()-1];
            points.pop_back();
            return true;
        }
    }
    return false;
}

std::pair<char, int> battlebot::shoot(battleplace::state last_hit, std::pair<char, int> last_hit_point){
    if((last_hit==battleplace::nohit)&&(points_on_hit.empty())){
        delete_point(last_hit_point);
        return points[random()%points.size()];
    }

    if((last_hit==battleplace::hit)&&(points_on_hit.empty())){
        delete_point(last_hit_point);
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(delete_point(std::pair<char,int>(last_hit_point.first+i%3-1,last_hit_point.second+j%3-1))){
                    points_on_hit.push_back(std::pair<char,int>(last_hit_point.first+i%3-1,last_hit_point.second+j%3-1));
                }
            }
        }
        previous_hit_point = last_hit_point;
        return points_on_hit[random()%points_on_hit.size()];
    }

    if((last_hit==battleplace::hit)&&(!points_on_hit.empty())){
        for(int i = 0; i < points_on_hit.size(); ++i){
            if(points_on_hit[i]==last_hit_point){
                points_on_hit[i]=points_on_hit[points_on_hit.size()-1];
                points_on_hit.pop_back();
            }
        }

        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(delete_point(std::pair<char,int>(last_hit_point.first+i%3-1,last_hit_point.second+j%3-1))){
                    points_on_hit.push_back(std::pair<char,int>(last_hit_point.first+i%3-1,last_hit_point.second+j%3-1));
                }
            }
        }
        char ctmp = 0;
        int itmp = 0;

        if(previous_hit_point.first==last_hit_point.first){
            ctmp = last_hit_point.first;
        }

        if(previous_hit_point.second==last_hit_point.second){
            itmp = last_hit_point.second;
        }

        if(ctmp){
            for(int i = 0; i < points_on_hit.size(); ++i){
                if(points_on_hit[i].first!=ctmp){
                    points_on_hit[i]=points_on_hit[points_on_hit.size()-1];
                    points_on_hit.pop_back();
                    --i;
                }
            }
        }

        if(itmp){
            for(int i = 0; i < points_on_hit.size(); ++i){
                if(points_on_hit[i].second!=itmp){
                    points_on_hit[i]=points_on_hit[points_on_hit.size()-1];
                    points_on_hit.pop_back();
                    --i; 
                }
            }
        }
        return points_on_hit[random()%points_on_hit.size()];
    }

    if((last_hit==battleplace::nohit)&&(!points_on_hit.empty())){
        for(int i = 0; i < points_on_hit.size(); ++i){
            if(points_on_hit[i]==last_hit_point){
                points_on_hit[i]=points_on_hit[points_on_hit.size()-1];
                points_on_hit.pop_back();
            }
        }
        return points_on_hit[random()%points_on_hit.size()];
    }

    if(last_hit==battleplace::sunk){
		delete_point(last_hit_point);
        points_on_hit.clear();
        return  points[random()%points.size()];
    }
}




                


