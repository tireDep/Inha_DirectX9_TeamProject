#pragma once
#include "cCubeNode.h"
class cBody :
	public cCubeNode
{
public:
	cBody();
	~cBody();

	virtual void Setup() override; 
};

