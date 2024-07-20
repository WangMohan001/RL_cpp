#ifndef MAB
#define MAB

#include<random>

class mab{
private:
    double* means;
    double* var;
    int num_arms;
public:
    mab(int num_arms, double* means, double* var){
        this->num_arms = num_arms;
        this->means = new double[num_arms];
        this->var = new double[num_arms];
        for(int i=0;i<num_arms;i++){
            this->means[i] = means[i];
            this->var[i] = var[i];
        }
    }

    mab(int num_arms){
        this->num_arms = num_arms;
        this->means = new double[num_arms];
        this->var = new double[num_arms];
        for(int i=0;i<num_arms;i++){
            this->means[i] = (double)rand()/RAND_MAX * 10 - 5;
            this->var[i] = (double)rand()/RAND_MAX * 3;
        }
    }
    int get_num_arms(){
        return num_arms;
    }
    double get_reward(int arm){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dist(means[arm],var[arm]);
        return dist(gen);
    }
    double maximum(){
        double maxm = -1000;
        for(int i=0;i<num_arms;i++){
            maxm=std::max(maxm,means[i]);
        }
        return maxm;
    }
    ~mab(){
        delete[] means;
        delete[] var;
    }
};

#endif