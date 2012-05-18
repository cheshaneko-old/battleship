#include "battleplace.h"
#include <iostream>
int main(){
    battleplace some;
    battleplace::ship a;
    battleplace::ship b;
    a.points.push_back(std::pair<char,int>('e',4));
    a.points.push_back(std::pair<char,int>('f',4));
    a.points.push_back(std::pair<char,int>('g',4));
    a.points.push_back(std::pair<char,int>('h',4));
    
    b.points.push_back(std::pair<char,int>('c',6));
    b.points.push_back(std::pair<char,int>('c',7));
    b.points.push_back(std::pair<char,int>('c',8));
    
    some.add_ship(a);
    some.add_ship(b);
    
    char ctmp;
    int itmp;
    while(1){
		std::cout << "Enter: ";
		std::cin >> ctmp;
		std::cin >> itmp;
		std::cout << some.shoot(std::pair<char,int>(ctmp, itmp)) << "\n";
		
	}
    
    return 0;
}
