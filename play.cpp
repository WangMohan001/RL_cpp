#include "agent.h"
#include "mab.cpp"
#include<cstdlib>
#include<iostream>
class play{
private:
    mab* bandit;
    agent* player;
    int num_steps;
public:
    play(mab* bandit, agent* player, int num_steps){
        this->bandit = bandit;
        this->player = player;
        this->num_steps = num_steps;
    }
    double run(int display = 0){
        double total_reward = 0;
        for(int i=0;i<num_steps;i++){
            int action = player->get_action();
            double reward = bandit->get_reward(action);
            if(display){
                std::cout<<"Step: "<<i<<" Action: "<<action<<" Reward: "<<reward<<std::endl;
            }
            player->update(action,reward);
            total_reward += reward;
        }
        return total_reward;
    }
};