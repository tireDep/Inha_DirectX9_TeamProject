#pragma once
class cCubePNT
{
public:
	cCubePNT();
	//~cCubePNT();
protected :
	std::vector<ST_PNT_VERTEX>	m_vecVertex; 

public :
	virtual ~cCubePNT(void); 
	virtual void Setup(); 
	virtual void Update(); 
	virtual void Render(); 
};

