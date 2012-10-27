#pragma once
#include <string>
#include "Starbucks.h"
using namespace std;


class dwyermwStarbucks : public Starbucks
{
public:
	dwyermwStarbucks(void);
	~dwyermwStarbucks(void);

	void build(Entry* c, int n);
	Entry* getNearest(double x, double y);
};

