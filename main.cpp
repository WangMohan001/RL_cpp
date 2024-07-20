#include "mab.cpp"
#include "agent.h"
#include "play.cpp"
#include "agent.cpp"
#include<vector>
#include<cstring>
#include<algorithm>
const int num=200;
const int num_arms=10;
class result{
public:
    std::string name;
    double reward;
    std::vector<double> para;
    result(std::string name, double reward, std::vector<double> para){
        this->name = name;
        this->reward = reward;
        this->para = para;
    }
    void print(){
        std::cout<<name<<"  Parameters: ";
        for(int i=0;i<para.size();i++){
            std::cout<<para[i]<<" ";
        }

        std::cout<<std::endl;
        std::cout<<"Reward: "<<reward<<std::endl;
    }
    bool operator<(const result& r){
        return this->reward>r.reward;
    }
};
std::vector<result> res;
void simulater(mab *bandit, std::string name){
    if(name=="epsilon_greedy"){
        double a=(double)rand()/RAND_MAX * 0.5;
        double b=(double)rand()/RAND_MAX * 0.05;
        play p(bandit, new epsilon_greedy(10,a,b), num);
        double r=p.run();
        std::vector<double> para{a,b};
        res.push_back(result(name,r,para));
    }
    if(name=="optimistic_greedy"){
        double a=(double)rand()/RAND_MAX * 20;
        double b=(double)rand()/RAND_MAX * 0.5;
        play p(bandit, new optimistic_greedy(10,a,b), num);
        double r=p.run();
        std::vector<double> para{a,b};
        res.push_back(result(name,r,para));
    }
    if(name=="ucb"){
        double a=(double)rand()/RAND_MAX * 1;
        play p(bandit, new ucb(10,a), num);
        double r=p.run();
        std::vector<double> para{a};
        res.push_back(result(name,r,para));
    }

}
int main(){
    srand(time(0));
    mab m(10);
    for(int i=0;i<100;i++){
        simulater(&m,"epsilon_greedy");
        simulater(&m,"optimistic_greedy");
        simulater(&m,"ucb");
    }
    std::sort(res.begin(),res.end());
    for(int i=0;i<50;i++){
        res[i].print();
    }

}