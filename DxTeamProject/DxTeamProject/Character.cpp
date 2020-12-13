#include "stdafx.h"
#include "Character.h"
#include "OBB.h"
#include "CHeight.h"
// Ray y check
#include "MeshTile.h"
#include "IObject.h"
#include "PObject.h"
#include "SkinnedMesh.h"

CCharacter::CCharacter()
	: m_vDirection(0, 0, 1)
	, m_vPosition(0, 0.0f, 0)
	// , m_pOBB(NULL)
	, m_isCollided(false)
	, m_jump(false)
	, jumpis(false)
	, jumping(false)
	, m_Character(NULL)
	, m_isColorChanged(false)
	// Ray y check
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRotY);
	D3DXMatrixIdentity(&matT);
	m_strName = "Character";
}

//COBB* CCharacter::GetOBB()
//{
//	// return m_pOBB;
//}
//
//void CCharacter::SetBool(bool istrue)
//{
//	
//	m_isOBB = istrue;
//}

void CCharacter::SetColor(D3DXCOLOR c)
{
	// for (int i = 12; i <= 17; i++)
	// 	m_vecVertex[i].c = c;
	m_color = c;
}

void CCharacter::ReceiveEvent(ST_EVENT eventMsg)
{
	// float duration = *(float*) eventMsg.ptrMessage;
	// speed *= duration;
	float speed = 10.0f * eventMsg.duration;
	rotation = -1.0f;

	if (!g_gameManager->GetUImode())
	{
		// todo : 애니메이션 관련 함수 생성(인덱스 세팅)

		if (eventMsg.message == WM_LBUTTONDOWN)
		{
			ST_EVENT msg;
			msg.eventType = EventType::eColorChangeEvent;
			msg.ptrMessage = &m_color;

			g_pEventManager->CheckEvent(msg);

			m_Character->SetAnimationIndexBlend(3); // ChangeColor
			return;
		}

		if (eventMsg.eventType == EventType::eChangedColorEvent)
		{
			DoRotation(0.0f);
			return;
			// >> 색 변화가 일어날 경우 그 방향(정면) 쳐다봄
		}

		if (eventMsg.eventType == EventType::eInputEvent)
		{
			switch (eventMsg.playerInput)
			{
			case PlayerInputType::eUp:
				rotation = 0.0f;
				break;

			case PlayerInputType::eLeftUp:
				rotation = D3DX_PI / 4.0f * -1;
				break;

			case PlayerInputType::eRightUp:
				rotation = D3DX_PI / 4.0f;
				break;

			case PlayerInputType::eDown:
				rotation = D3DX_PI;
				break;

			case PlayerInputType::eLeftDown:
				rotation = D3DX_PI + D3DX_PI / 4.0f;
				break;

			case PlayerInputType::eRightDown:
				rotation = (D3DX_PI + D3DX_PI / 4.0f) * -1;
				break;

			case PlayerInputType::eLeft:
				rotation = -D3DX_PI / 2.0f;
				break;

			case PlayerInputType::eRight:
				rotation = D3DX_PI / 2.0f;
				break;

				// todo : 점프 구현
			case PlayerInputType::eJump:
				if (!jumping)
				{
					m_jump = true;
					if (m_Character->CheckAnimationEnd())
					{
						m_Character->SetAnimationIndex(7); // jump
					}
				}
				speed = -1.0f;
				break;

				// todo : 잡기 구현
			case PlayerInputType::eHold:
				if (m_nGrabAbleObeject != -1)
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndexBlend(5); // push
					// >> 블랜드가 안되서 잡기 대기 상태처럼 나옴
				}
				// else
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndexBlend(5); // push
				speed = -1.0f;
				break;
			case PlayerInputType::eHoldPush:
				if (m_nGrabAbleObeject != -1)
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(5); // Push
				}
				else
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(10); // Idle
				speed = -1.0f;
				break;
			case PlayerInputType::eHoldPull:
				if (m_nGrabAbleObeject != -1)
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(4); // Pull
				}
				else
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(10); // Idle
				speed = -1.0f;
				break;
			default:
				speed = -1.0f;
				if (m_Character->CheckAnimationEnd())
					m_Character->SetAnimationIndex(10); // Idle
				break;
			}
		} // << eInputEvent

		if (speed > 0 && m_Character->CheckAnimationEnd())
		{
			// >> 특정 애니메이션 재생 중 이동 하지 않음
			if(!jumping)
				m_Character->SetAnimationIndex(9); // Walk

			// >> todo : 속도 변화 감지해서 달리기 추가
			// >> 입력 시간에 따른 달리기 변화?

			DoRotation(rotation);
			DoMove(speed);
		}
	}


	//D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	//m_matWorld = m_matRotY * matT;
}

string CCharacter::GetName()
{
	return m_strName;
}

// Ray y check
void CCharacter::UpdateRayYCheck(MeshTile & meshtile)
{
	//BOOL Hit = false;
	//DWORD FaceIndex;
	//float U, V;
	//float Dist;
	//D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 10, 0);
	////rayOrigin.x -= meshtile.GetMatWorld()._41;
	////rayOrigin.y -= meshtile.GetMatWorld()._42;
	////rayOrigin.z -= meshtile.GetMatWorld()._43;
	//m_Ray.SetOrigin(rayOrigin);
	//D3DXIntersect(meshtile.GetMesh(), &m_Ray.GetOrigin(), &m_Ray.GetDirection(), 
	//	&Hit, &FaceIndex, &U, &V, &Dist, NULL, NULL);
	//if (Hit)
	//	m_vPosition.y = (m_Ray.GetOrigin().y - Dist) + 0.5f;
	//	//m_vPosition.y = (m_Ray.GetOrigin().y - Dist + meshtile.GetMatWorld()._42) + 0.5f;
	//else
	//	m_vPosition.y = 0.5f;
}

CCharacter::~CCharacter()
{
	SafeDelete(m_Character);
}

void CCharacter::Setup()
{
	//ST_PC_VERTEX v;
	//float cubeSize = 0.5f;
	//
	//// : front
	//v.c = RED; // 캐릭터 후면 빨강
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//
	//// : back 
	//v.c = BLUE; // 캐릭터 정면 파랑
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//
	//// : top 
	//v.c = D3DCOLOR_XRGB(127, 127, 127); // 캐릭터 뚜껑(변화)
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//
	//// : left
	//v.c = WHITE; // 캐릭터 왼면(흰)
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//
	//// : right 
	//v.c = BLACK; // 캐릭터 오른면(흑)
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//
	//// : bottom
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, -cubeSize);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cubeSize, -cubeSize, cubeSize);	m_vecVertex.push_back(v);
	//
	//for (int i = 0; i < m_vecVertex.size(); i++)
	//	m_vecVertex[i].p += D3DXVECTOR3(0, 0.5f, 0);
	//
	// m_pOBB = new COBB;
	// m_pOBB->SetupCube(m_vecVertex[0], m_vecVertex[11], cubeSize);

	m_Character = new CSkinnedMesh;
	m_Character->SetUp("Resource/XFile/Character", "AnimationCharacter.X");
	// m_Character->SetAnimationIndexBlend(8);
	m_Character->SetAnimationIndex(10);

	// Ray y check
	D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 10, 0);
	m_Ray.SetOrigin(rayOrigin);
	m_Ray.SetDirection(D3DXVECTOR3(0, -1, 0));
}

void CCharacter::Update(D3DXVECTOR3 cameradirection)
{
	m_vDirection = cameradirection;

		if (m_jump)
		{
			jumping = true;
			if (m_vPosition.y <= 3.f)
			{
				m_vPosition.y += 0.005f;
				if (m_vPosition.y >= 3.f)
				{
					jumpis = true;
					m_jump = false;
				}
			}
		}
		if (jumpis == true)
		{
			m_vPosition.y -= 0.005f;
			if (m_vPosition.y <= 0)
			{
				jumpis = false;
				jumping = false;
			}
			m_Character->SetAnimationIndexBlend(6); // fall
		}
	
}

//void CCharacter::Update(D3DXVECTOR3 cameradirection, CHeight* pMap)
//{
//	m_vDirection = cameradirection;
//	//D3DXMATRIXA16 matWorldOBB;
//	//matWorldOBB = m_matWorld;
//	//matWorldOBB._42 -= 0.5f;
//	//if (m_pOBB)
//	//	m_pOBB->Update(&matWorldOBB);
//	
//	
//	//if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[0]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[0]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[0]->GetTranslate().y + 0.5;
//	//	cout << 0 << endl;
//	//}
//	//else if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[1]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[1]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[1]->GetTranslate().y + 0.5;
//	//	cout << 1 << endl;
//	//}
//	//else if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[2]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[2]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[2]->GetTranslate().y + 0.5;
//	//	cout << 2 << endl;
//	//}
//	//else if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[3]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[3]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[3]->GetTranslate().y + 0.5;
//	//	cout << 3 << endl;
//	//}
//	//
//
//	float height = m_vPosition.y;
//
//	for (int i = 0; i < g_pObjectManager->m_OBB.size(); ++i)
//	{
//		if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[i]) == true)
//		{
//			m_vPosition.y = g_pObjectManager->m_vecIObject[i]->GetScale().y *
//				g_pObjectManager->GetScale() +
//				g_pObjectManager->m_vecIObject[i]->GetTranslate().y + 0.5;
//		}
//		else
//		{
//			//m_vPosition.y -= 0.001f;
//		}
//	
//	}
//
//	
//	if (pMap)
//	{
//		pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
//	}
//
//	if (m_pOBB)
//		m_pOBB->Update(&m_matWorld);
//
//
//}
//void CCharacter::Update(D3DXVECTOR3 cameradirection, CHeight* pMap)
//{
//	m_vDirection = cameradirection;
//	//D3DXMATRIXA16 matWorldOBB;
//	//matWorldOBB = m_matWorld;
//	//matWorldOBB._42 -= 0.5f;
//	//if (m_pOBB)
//	//	m_pOBB->Update(&matWorldOBB);
//	
//	
//	//if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[0]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[0]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[0]->GetTranslate().y + 0.5;
//	//	cout << 0 << endl;
//	//}
//	//else if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[1]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[1]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[1]->GetTranslate().y + 0.5;
//	//	cout << 1 << endl;
//	//}
//	//else if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[2]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[2]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[2]->GetTranslate().y + 0.5;
//	//	cout << 2 << endl;
//	//}
//	//else if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[3]) == 1)
//	//{
//	//	m_vPosition.y = g_pObjectManager->m_vecIObject[3]->GetScale().y *g_pObjectManager->GetScale() + g_pObjectManager->m_vecIObject[3]->GetTranslate().y + 0.5;
//	//	cout << 3 << endl;
//	//}
//	
//
//	float height = m_vPosition.y;
//
//	
//		for (int i = 0; i < g_pObjectManager->m_OBB.size(); ++i)
//		{
//			if (COBB::IsCollision(GetOBB(), g_pObjectManager->m_OBB[i]) == true)
//			{
//				m_vPosition.y = g_pObjectManager->m_vecIObject[i]->GetScale().y *
//					g_pObjectManager->GetScale() +
//					g_pObjectManager->m_vecIObject[i]->GetTranslate().y + 0.5;
//			}
//			else
//			{
//				m_vPosition.y -= 0.001f;
//			}
//
//		}
//	
//	
//
//	
//	if (pMap)
//	{
//		pMap->GetHeight(m_vPosition.x, m_vPosition.y, m_vPosition.z);
//	}
//
//	if (m_pOBB)
//		m_pOBB->Update(&m_matWorld);
//
//
//}

int CCharacter::Update(vector<PObject*> ObjectPosition, float duration)
{

	//if (m_pOBB)
	//	m_pOBB->Update(&m_matWorld);

	for (int i = 0; i < ObjectPosition.size(); ++i)
	{
		if (ObjectPosition[i]->GetPosition().x - m_vPosition.x < 1.0f
			&& ObjectPosition[i]->GetPosition().z - m_vPosition.z < 1.0f
			&& ObjectPosition[i]->GetPosition().x - m_vPosition.x > -1.0f
			&& ObjectPosition[i]->GetPosition().z - m_vPosition.z > -1.0f
			&& ObjectPosition[i]->GetPosition().y - m_vPosition.y <  1.0f
			&& ObjectPosition[i]->GetPosition().y - m_vPosition.y > -1.0f)
		{
			//m_nGrabAbleObeject = i;
			return i;
		}
	}
	//m_nGrabAbleObeject = -1;

	// >> skinnedMesh
	if (m_Character)
	{
		m_Character->Update(duration);
		m_Character->SetTransform(&m_matWorld);
	}
	// << skinnedMesh

	return -1;
}

void CCharacter::DoRotation(const float& radian)
{
	m_vDirection.y = 0;
	D3DXMatrixRotationY(&m_matRotY, radian);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &m_matRotY);
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);

	D3DXVECTOR3 tempPos(0, 0, 0);
	D3DXVECTOR3 tempUp(0, 1, 0);
	D3DXMatrixLookAtLH(&m_matRotY, &tempPos, &m_vDirection, &tempUp);
	D3DXMatrixTranspose(&m_matRotY, &m_matRotY);
}

void CCharacter::DoMove(const float& velocity)
{
	static D3DXVECTOR3 m_position = m_vPosition;

	if (m_isCollided)
	{
		m_vPosition = m_position;
	}
	else
	{
		m_position = m_vPosition;
	}
	m_vPosition = m_vPosition + (m_vDirection * velocity);
}

void CCharacter::Render(D3DCOLOR d)
{
	// g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	// g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	// g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
	// 	m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
	// D3DCOLOR c = d;
	// m_pOBB->OBBBOX_RENDER(c);

	if (m_Character)
	{
		m_Character->Render(NULL);
	}
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = m_matRotY * matT;
}

D3DXVECTOR3& CCharacter::GetPosition()
{
	return m_vPosition;
}

D3DXMATRIXA16* CCharacter::GetTransform()
{
	return &m_matWorld;
}

float CCharacter::Getrotation()
{
	return rotation;
}

D3DXCOLOR CCharacter::GetColor()
{
	return m_color;
}

bool CCharacter::Collider(bool isCollided)
{
	m_isCollided = isCollided;
	return m_isCollided;
}

void CCharacter::ColliderOtherObject(IObject * background)
{
	if (m_Character->GetOBB()->IsCollision(background->GetOBB()))
	{
		
		m_isCollided = true;
		
	}
	else
	{
		m_isCollided = false;
		
	}
}