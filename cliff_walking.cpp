#ifndef CLIFF_WALKING
#define CLIFF_WALKING
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct action{
    int dx;
    int dy;
    action(int dx, int dy){
        this->dx = dx;
        this->dy = dy;
    }
};

class state{
private:
    int x;
    int y;
public:
    state& operator=(const state& s){
        this->x = s.x;
        this->y = s.y;
        return *this;
    }
    state(int x, int y){
        this->x = x;
        this->y = y;
    }
    int get_hash(){
        return this->x*30 + this->y;
    }
    int get_x(){
        return this->x;
    }
    int get_y(){
        return this->y;
    }
    bool is_terminal(){
        if(x==3&&y>=1&&y<=11){
            return true;
        }
        return false;
    }
    void print(){
        std::cout<<"("<<x<<" , "<<y<<")"<<std::endl;
    }
    int get_reward(){
        if(x==3&&y>=1&&y<=10){
            return -100;
        }
        return -1;
    }
    bool is_valid(){
        if(x>=0&&x<=3&&y>=0&&y<=11){
            return true;
        }
        return false;
    }
    state get_next_state(action act){
        return state(x+act.dx, y+act.dy);
    }
};

#endif
