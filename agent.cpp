#include "agent.h"
#include<cstdlib>
#include<ctime>
#include<cmath>
class epsilon_greedy: public agent{
private:
    double epsilon;
    double* q_values;
    int num_arms;
    int* counts;
    double decay;
public:
    epsilon_greedy(int num_arms, double epsilon, double dec = 0.01):agent(){
        this->epsilon = epsilon;
        this->num_arms = num_arms;
        this->q_values = new double[num_arms];
        this->counts = new int[num_arms];
        this->decay = dec;
        for(int i=0;i<num_arms;i++){
            this->q_values[i] = 0;
            this->counts[i] = 0;
        }
    }
    int get_action(){
        if((double)rand()/RAND_MAX<epsilon){
            return rand()%num_arms;
        }
        else{
            int a = -1;
            for(int i=0;i<num_arms;i++){
                if(counts[i]==0){
                    return i;
                }
                if(q_values[i]>q_values[a]||a==-1){
                    a = i;
                }
            }
            return a;
        }
        epsilon -= decay*epsilon;

    }
    void update(int action, double reward){
        counts[action]++;
        q_values[action] = q_values[action] + (reward - q_values[action])/counts[action];
    }
    ~epsilon_greedy(){
        delete[] q_values;
        delete[] counts;
    }
};

class optimistic_greedy: public agent{
private:
    double* q_values;
    int num_arms;
    double alpha;
public:
    optimistic_greedy(int num_arms, double start, double alpha):agent(){
        this->num_arms = num_arms;
        this->q_values = new double[num_arms];
        this->alpha = alpha;
        for(int i=0;i<num_arms;i++){
            this->q_values[i] = start;
        }
    }
    int get_action(){
        int a = -1;
        for(int i=0;i<num_arms;i++){
            if(q_values[i]>q_values[a]||a==-1){
                a = i;
            }
        }
        return a;
    }
    void update(int action, double reward){
        q_values[action] = q_values[action] + alpha*(reward - q_values[action]);
    }
    ~optimistic_greedy(){
        delete[] q_values;
    }
};

class ucb: public agent{
private:
    double* q_values;
    int num_arms;
    int* counts;
    double* ucb_values;
    double alpha;
    int time_step;
public:
    ucb(int num_arms, double alpha):agent(){
        this->num_arms = num_arms;
        this->q_values = new double[num_arms];
        this->counts = new int[num_arms];
        this->ucb_values = new double[num_arms];
        this->alpha = alpha;
        this->time_step = 0;
        for(int i=0;i<num_arms;i++){
            this->q_values[i] = 0;
            this->counts[i] = 0;
            this->ucb_values[i] = 0;
        }
    }
    int get_action(){
        int a = -1;
        for(int i=0;i<num_arms;i++){
            if(counts[i]==0){
                return i;
            }
            if(ucb_values[i]>ucb_values[a]||a==-1){
                a = i;
            }
        }
        return a;
    }
    void update(int action, double reward){
        time_step++;
        counts[action]++;
        q_values[action] = q_values[action] + (reward - q_values[action])/counts[action];
        for(int i=0;i<num_arms;i++){
            ucb_values[i] = q_values[i] + alpha*sqrt(log(time_step)/counts[i]);
        }
    }
};
