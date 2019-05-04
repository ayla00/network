#ifndef INNEURON_H
#define INNEURON_H


#include "neural.h"


class inNeuron : public Neural
{
public:
	inNeuron();
	~inNeuron();
	void setInput(inNeuron *setptr); //maybe add override
private:
	//int nodenum;


};

#endif  //INNEURON_H
