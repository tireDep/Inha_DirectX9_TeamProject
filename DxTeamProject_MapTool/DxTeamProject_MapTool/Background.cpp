#include "stdafx.h"
#include "Background.h"

// #define Va_Start	__crt_va_start
// #define Va_Arg		__crt_va_arg
// #define Va_End		__crt_va_end
// #define Va_Copy(dest, source) ((dest) == (source))

void CBackground::DoNewTagging(int cnt, string ...)
{
	m_vecColorTag.clear();

	va_list vaList;
	va_start(vaList, cnt);
	
	for (int i = 0; i < cnt; i++)
	{
		m_vecColorTag.push_back(va_arg(vaList, string));
	}

	va_end(vaList);
}

CBackground::CBackground()
{
	m_pMesh = NULL;
	m_pTexture = NULL;
}

CBackground::~CBackground()
{
}

void CBackground::Setup()
{
}

void CBackground::Setup(ST_MapData setData)
{
	m_strObjName = setData.strObjName;
	m_strFolder = setData.strFolderPath;
	m_strXFile = setData.strXFilePath;
	m_strTxtFile = setData.strTxtPath;
	m_ObjectType = setData.objType;
	m_vScale = setData.vScale;
	m_vRotate = setData.vRotate;
	m_vTranslate = setData.vTranslate;

	m_vecColorTag = setData.vecColorTag; 

	if (m_strXFile != "")
	{
		ST_XFile* xfile = new ST_XFile;

		g_pFileLoadManager->FileLoad_XFile(m_strFolder, m_strXFile, xfile);

		if (m_strTxtFile != "")
			g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);

		m_pMesh = xfile->pMesh;
		m_adjBuffer = xfile->adjBuffer;
		m_vecMtrls = xfile->vecMtrl;
		m_vecTextures = xfile->vecTextrure;
		m_numMtrls = xfile->nMtrlNum;

		int check = 0;
		for (int i = 0; i < m_vecTextures.size(); i++)
		{
			if (m_vecTextures[i] == NULL)
				check++;
		}

		if (check == m_vecTextures.size())
		{
			// >> 텍스쳐 로드 정보 x 일 때
			m_vecTextures.clear();
			m_vecTextures.push_back(m_pTexture);
		}

		delete xfile;
	}
	else
	{
		m_vTranslate.y = 0.5f;
		D3DXCreateBox(g_pD3DDevice, 1, 1, 1, &m_pMesh, NULL);
		
		m_pMtrl.Ambient = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_pMtrl.Diffuse = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);
		m_pMtrl.Specular = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);

		m_vecMtrls.push_back(m_pMtrl);
	}

	IObject::Setup_OBB_Box();
}

void CBackground::Update()
{
}

void CBackground::Render()
{
	IObject::Render_OBB_Box();

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &GetmatWorld());

	if (m_pMesh == NULL)
		return;

	if (m_ObjectType == ObjectType::eInvisibleWall || m_ObjectType == ObjectType::eFlower)
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	else
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	if (!m_isPick && !m_isClick || !m_pShader)
	{
		for (int i = 0; i < m_vecMtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecMtrls[i]);

			if (m_ObjectType != ObjectType::eInvisibleWall && m_ObjectType != ObjectType::eFlower)
			{
				if(m_vecTextures[i] != NULL)
					g_pD3DDevice->SetTexture(0, m_vecTextures[i]);
			}

			m_pMesh->DrawSubset(i);
		}
	}
	else
	{
		SetShader(GetmatWorld());
		IObject::Render();
	}

	g_pD3DDevice->SetTexture(0, NULL);
}

void CBackground::SetDiffScale(D3DXVECTOR3 set)
{
	// >> 같은 비율로 크기 변환
	if (set.x != m_vScale.x)
		m_vScale = D3DXVECTOR3(set.x, set.x, set.x);
	else if (set.y != m_vScale.y)
		m_vScale = D3DXVECTOR3(set.y, set.y, set.y);
	else if (set.z != m_vScale.z)
		m_vScale = D3DXVECTOR3(set.z, set.z, set.z);
}

int CBackground::GetTextureIndex()
{
	if (m_ObjectType == ObjectType::eCTree)
	{
		if (m_strTxtFile == "TreesBlue.png")
			return 0;
		if (m_strTxtFile == "TreesGreen.png")
			return 1;
		if (m_strTxtFile == "TreesYellow.png")
			return 2;
		if (m_strTxtFile == "TreesRed.png")
			return 3;
	}
	else if (m_ObjectType == ObjectType::eUmbrella)
	{
		if (m_strTxtFile == "Umbrella_Blue.png")
			return 0;
		if (m_strTxtFile == "Umbrella_BlueRed.png")
			return 1;
		if (m_strTxtFile == "Umbrella_Red.png")
			return 2;
		if (m_strTxtFile == "Umbrella_White.png")
			return 3;
	}
}

void CBackground::SetTexture(int index)
{
	bool isTree = false;
	bool isUmbrella = false;
	if (m_ObjectType == ObjectType::eCTree)
	{
		isTree = true;
		if (index == 0)
		{
			m_strTxtFile = "TreesBlue.png";
			DoNewTagging(1, "Blue");
		}
		else if (index == 1)
		{
			m_strTxtFile = "TreesGreen.png";
			DoNewTagging(1, "Green");
		}
		else if (index == 2)
		{
			m_strTxtFile = "TreesYellow.png";
			DoNewTagging(1, "Yellow");
		}
		else if (index == 3)
		{
			m_strTxtFile = "TreesRed.png";
			DoNewTagging(1, "Red");
		}
	}
	else if (m_ObjectType == ObjectType::eUmbrella)
	{
		isUmbrella = true;
		if (index == 0)
		{
			m_strTxtFile = "Umbrella_Blue.png";
			DoNewTagging(1, "Blue");
		}
		else if (index == 1)
		{
			m_strTxtFile = "Umbrella_BlueRed.png";
			DoNewTagging(2, "Blue", "Red");
		}
		else if (index == 2)
		{
			m_strTxtFile = "Umbrella_Red.png";
			DoNewTagging(1, "Red");
		}
		else if (index == 3)
		{
			m_strTxtFile = "Umbrella_White.png";
			DoNewTagging(1, "White");
		}
	}

	if (isUmbrella)
	{
		int index = 0;
		for (int i = 0; i < m_strObjName.length(); i++)
		{
			if (m_strObjName[i] >= 48 && m_strObjName[i] <= 57)
			{
				index = i;
				break;
			}
		}
		// << refCnt 추출

		string temp = m_strTxtFile;
		temp = temp.substr(0, temp.length() - 4);

		m_strObjName = temp + m_strObjName.substr(index, m_strObjName.length());
	}
	else if (isTree)
	{
		int index = 0;
		int index1 = 0;
		int index2 = 0;
		int check = 0;
		for (int i = 0; i < m_strObjName.length(); i++)
		{
			if (m_strObjName[i] == '_')
			{
				check++;
				if (check <= 2)
					index = i;
				else if (check == 3)
					index1 = i;
				else if (check == 4)
					index2 = i - 1;
			}
		}
		// >> 이름 인덱스 추출

		string temp;
		if (strstr(m_strTxtFile.c_str(), "Blue")) temp = "_Blue";
		else if (strstr(m_strTxtFile.c_str(), "Green")) temp = "_Green";
		else if (strstr(m_strTxtFile.c_str(), "Red")) temp = "_Red";
		else if (strstr(m_strTxtFile.c_str(), "Yellow")) temp = "_Yellow";

		m_strObjName = m_strObjName.substr(0, index) + temp
			+ m_strObjName.substr(index1, index2);
	}

	g_pFileLoadManager->FileLoad_Texture(m_strFolder, m_strTxtFile, m_pTexture);
	m_vecTextures.clear();
	m_vecTextures.push_back(m_pTexture);
}
