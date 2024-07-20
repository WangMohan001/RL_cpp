#ifndef OASIS
#define OASIS
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
    int vis;
public:
    state& operator=(const state& s){
        this->x = s.x;
        this->y = s.y;
        this->vis = s.vis;
        return *this;
    }
    state(int x, int y, int v){
        this->x = x;
        this->y = y;
        this->vis = v;
        
    }
    int get_hash(){
        return this->x*8 + this->y + 8*8*vis;
    }
    static state get_state(int hash){
        return state(hash/8, hash%8, hash/(8*8));
    }
    int get_x(){
        return this->x;
    }
    int get_y(){
        return this->y;
    }
    bool is_terminal(){
        if(x==0||x==6||y==0||y==7){
            return true;
        }
        if(x==3&&y==6) return true;
        return false;
    }
    void print(){
        std::cout<<"("<<x<<" , "<<y<<") -"<<vis<<std::endl;
    }
    int get_reward(){
        if(x==0||x==6||y==0||y==7){
            return -100;
        }
        if(x==3&&y==4) {
            if(vis==0) return 50 - 1;
            else return -10 - 1;
        }
        if(x>=2&&x<=4&&y>=2&&y<=5) return -10 - 1;
        return -1;
    }
    bool is_valid(){
        return x>=0&&x<=6&&y>=0&&y<=7;
    }
    state get_next_state(action act){
        if(x==3&&y==4){
            return state(x+act.dx, y+act.dy, 1);
        }
        return state(x+act.dx, y+act.dy, vis);
    }
    static int get_num_states(){
        return 8*8*2;
    }
    static std::vector<state> get_all_states(){
        std::vector<state> states;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                states.push_back(state(i,j,0));
                states.push_back(state(i,j,1));
            }
        }
        return states;
    }
    static state beginning_state(){
        return state(3,1,0);
    }
};

#endif
