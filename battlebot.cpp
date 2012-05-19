#include "battlebot.h"
#include <cstdlib>
battlebot::battlebot(){
    for(int i = 0; i < 100; ++i){
        points.push_back(std::pair<char,int>('a'+i/10,i%10+1));
    }
    srandom(3);
    my_battleplace = create_battleplace();
}

battleplace battlebot::create_battleplace(){
    int ship_types[5]={0,4,3,2,1};
    battleplace my_p;
    battleplace::ship my_s;
    std::vector< std::pair<char, int> > my_points;
    for(int i = 0; i < 100; ++i){
        my_points.push_back(std::pair<char,int>('a'+i/10,i%10+1));
    }
    for(int i = 1; i < 5;  ++i){
        while(ship_types[i]){
		bool c_s = true;
		while(c_s){
            int n_start = random()%my_points.size();
            std::pair<char, int> start = my_points[n_start];
            my_s.points.push_back(start);
            my_points[n_start] = my_points[my_points.size()-1];
            my_points.pop_back();
            int choise = random()%2;
            for(int j = 1; j < i; ++j){
                std::pair<char, int> point;
                if(choise){
                    point.first=start.first+j;
                    point.second=start.second;
                }
                else{
                    point.first=start.first;
                    point.second=start.second+j;
                }
                bool exist = false;
                int n_exist;
                for(int k = 0; k < my_points.size(); ++k){
                    if(my_points[k]==point){
                        exist = true;
                        n_exist = k;
                        break;
                    }
                }
                if(exist){
                     my_s.points.push_back(point);
                     my_points[n_exist] = my_points[my_points.size()-1];
                     my_points.pop_back();
                }
                else{
                    for(int kkk = 0; kkk < my_s.points.size(); ++kkk){
                        my_points.push_back(my_s.points[kkk]);
                    }
                    my_s.points.clear();
                    break;
                }
            }
            if(my_s.points.size()==i){
				c_s = false;
			}
            
         }
            for(int r = 0; r < my_s.points.size(); ++r){
                for(int r1 = 0; r1 < 3; ++r1){
                    for(int r2 = 0; r2 < 3; ++r2){
                        std::pair<char,int> f_a_d = std::pair<char,int>(my_s.points[r].first+r1%3-1,my_s.points[r].second+r2%3-1);
                        for(int iii = 0; iii<my_points.size(); ++iii){
                            if(f_a_d==my_points[iii]){
                                my_points[iii] = my_points[my_points.size()-1];
                                my_points.pop_back();
                                break;
                            }
                        }
                    }
                }
            }
			my_p.add_ship(my_s);
			ship_types[i]--;
            my_s.points.clear();
        }
    }
    return my_p;
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
					if(((i%3-1) == 0) || ((j%3-1) == 0)){
						points_on_hit.push_back(std::pair<char,int>(last_hit_point.first+i%3-1,last_hit_point.second+j%3-1));
					}
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
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                delete_point(std::pair<char,int>(last_hit_point.first+i%3-1,last_hit_point.second+j%3-1));
                }
            }
        }
        points_on_hit.clear();
        return  points[random()%points.size()];
}





                


