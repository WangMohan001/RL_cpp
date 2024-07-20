#ifndef AGENT_H
#define AGENT_H

class agent{
public:
    virtual int get_action()=0;
    virtual void update(int action, double reward)=0;
};

#endif