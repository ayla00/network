#ifndef INNEURON_H
#define INNEURON_H


#include "neural.h"


class inNeuron : public Neural
{
public:
	inNeuron();
	~inNeuron();
	void setInput(Neural *setptr); //maybe change pointer type to inNeural * setptr
private:
	//int nodenum;


};

#endif  //INNEURON_H
