#pragma once

class cMtlTex;
class cGroup;

class cObjLoader
{
private:
	map<string, cMtlTex*> m_mapMtlTex;

public:
	cObjLoader();
	~cObjLoader();

	void Load(OUT vector<cGroup*>&vecGroup, IN char* szFolder, IN char* szFile);
	void LoadMtlLib(char * szFolder, char* szFile);

	void LoadSurface(OUT vector<D3DXVECTOR3> & vecSurface, IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pmat = NULL);

	LPD3DXMESH LoadMesh(OUT vector<cMtlTex*>& vecMtlTex, IN char * szFolder, IN char* szFile);
};