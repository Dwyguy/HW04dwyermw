#pragma once
#include <string>
#include "Starbucks.h"
#include "Node.h"
using namespace std;


class dwyermwStarbucks : public Starbucks
{
public:
	dwyermwStarbucks();
	~dwyermwStarbucks(void);

	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);
	Node* root;
	
};

