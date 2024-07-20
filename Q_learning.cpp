#include<vector>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include "oasis.cpp"


class agent{ //q-learning
private:
    double q_values[1000][4];
    double alpha;
    double gamma;
    double epsilon;
    action actions[4] = {action(0,1),action(0,-1),action(1,0),action(-1,0)};
public:
    agent(double alpha = 0.4 , double gamma = 1, double epsilon = 1){
        this->alpha = alpha;
        this->gamma = gamma;
        this->epsilon = epsilon;
        for(int i=0;i<1000;i++){
            for(int j=0;j<4;j++){
                q_values[i][j] = 0;
            }
        }
    }
    action get_action(state s, int time_step = 0){
        int x = s.get_x();
        int y = s.get_y();
        int a;
        double eps=epsilon/(time_step / 2 + 1);
        //double eps=0.3;
        if((double)rand()/RAND_MAX<eps){
            a = rand()%4;
            while(!s.get_next_state(actions[a]).is_valid()){
                a = rand()%4;
            }
        }
        else{
            a = -1;
            for(int i=0;i<4;i++){
                if(!s.get_next_state(actions[i]).is_valid()){
                    continue;
                }
                if(q_values[s.get_hash()][i]>q_values[s.get_hash()][a]||a==-1){
                    a = i;
                }
            }
        }
        return actions[a];
    }
    void update(state s, action act, state s_prime){
        int x = s.get_x();
        int y = s.get_y();
        int x_prime = s_prime.get_x();
        int y_prime = s_prime.get_y();
        double r = s_prime.get_reward();
        int a;
        if(act.dx==0&&act.dy==1){
            a = 0;
        }
        else if(act.dx==0&&act.dy==-1){
            a = 1;
        }
        else if(act.dx==1&&act.dy==0){
            a = 2;
        }
        else if(act.dx==-1&&act.dy==0){
            a = 3;
        }
        if(s_prime.is_terminal()){
            q_values[s.get_hash()][a] = q_values[s.get_hash()][a] + alpha*(r-q_values[s.get_hash()][a]);
            return;
        }
        int a_prime = -1;
        for(int i=0;i<4;i++){
            if(!s_prime.get_next_state(actions[i]).is_valid()){
                continue;
            }
            if(q_values[s_prime.get_hash()][i]>q_values[s_prime.get_hash()][a_prime]||a_prime==-1){
                a_prime = i;
            }
        }
        q_values[s.get_hash()][a] = q_values[s.get_hash()][a] + alpha*(r+gamma*q_values[s_prime.get_hash()][a_prime]-q_values[s.get_hash()][a]);
    }
    void print_q(){
        auto all_states = state::get_all_states();
        for(auto s:all_states){
            if(s.is_terminal()){
                continue;
            }   
            std::cout<<s.get_x()<<" "<<s.get_y()<<std::endl;
            for(int i=0;i<4;i++){
                std::cout<<q_values[s.get_hash()][i]<<" ";
            }
            std::cout<<std::endl;
        }
    }
    void print_q(state s){
        for(int i=0;i<4;i++){
            std::cout<<actions[i].dx<<" "<<actions[i].dy<<" : "<<q_values[s.get_hash()][i]<<std::endl;
        }
        std::cout<<std::endl;
    }
};

int turn(agent& a, state& s, int ti, int display = 0 ){
    int ret = 0;
    while(!s.is_terminal()){
        action act = a.get_action(s, ti);
        int x = s.get_x();
        int y = s.get_y();
        if(!s.get_next_state(act).is_valid()){
            std::cout<<"invalid action"<<std::endl;
            exit(0);
        } 
        state s_prime = s.get_next_state(act);
        a.update(s, act, s_prime);
        s = s_prime;
        if(display) {
            s.print();
            
        }

        ret += s.get_reward();
    }
    return ret;
}

int main(){
    srand(time(NULL));
    agent a;
    state s = state::beginning_state();
    int total_reward = 0;
    int num=100;
    for(int i=0;i<num;i++){
        int tmp = turn(a, s, i);
        s = state::beginning_state();
        std::cout<<i<<" "<<tmp<<std::endl;
        total_reward += tmp;
    }
    std::cout<<total_reward<<std::endl;
    std::cout<<(double)total_reward/num<<std::endl;
    std::cout<<"regrets = "<<total_reward-21*num<<std::endl;
    s=state::beginning_state();
    turn(a, s,100000000, 1);
    //a.print_q();
    return 0;

}
