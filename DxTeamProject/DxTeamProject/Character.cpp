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
	, m_vPosition(0, 0, 0)
	, m_isCollided(false)
	, m_Character(NULL)
	, m_isColorChanged(false)
	, m_color(GRAY)
	, m_isGrab(false)
	, m_isJump(false)
	, m_fMaxJumpHeight(1.5f)
	, m_fRadianJump(0.0f)
	, m_isFallAni(false)
	, m_preRotation(0.0f)
	, m_vContactNormal(0, 0, 0)
	, m_fPenetration(0.0f)
	, m_isCollidedTile(false)
	, m_fHeightTile(0.0f)
	// , m_pOBB(NULL)
	// , jumpis(false)
	// , jumping(false)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRotY);
	D3DXMatrixIdentity(&matT);
	m_strName = "Character";
}

void CCharacter::SetColor(D3DXCOLOR c)
{
	m_color = c;
}

void CCharacter::ReceiveEvent(ST_EVENT eventMsg)
{
	// float duration = *(float*) eventMsg.ptrMessage;
	// speed *= duration;
	float speed = 10.0f * eventMsg.duration;
	rotation = -1.0f;

	if (!g_pGameManager->GetUImode())
	{
		// todo : �ִϸ��̼� ���� �Լ� ����(�ε��� ����)

		if (eventMsg.message == WM_LBUTTONDOWN)
		{
			if (m_isJump)
				return;

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
			// >> �� ��ȭ�� �Ͼ ��� �� ����(����) �Ĵٺ�
		}

		if (eventMsg.eventType == EventType::eInputEvent)
		{
			switch (eventMsg.playerInput)
			{
				// todo : ���� ����
			case PlayerInputType::eJump:
				//if (!jumping)
				// {
				// 	m_isJump = true;
				// 	m_Character->SetAnimationIndex(7); // jump
				// }
				// speed = -1.0f;

				if (!m_isJump)
				{
					m_isJump = true;
					m_Character->SetAnimationIndexBlend(7); // jump
					speed = -1;
				}
				break;

				// todo : ��� ����
			case PlayerInputType::eHold:
				if (m_isGrab)
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(5);
				}
				else
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(10); // Idle
				}
				//if (m_nGrabAbleObeject != -1)
				//{
				//	if (m_Character->CheckAnimationEnd())
				//		//m_Character->SetAnimationIndexBlend(5); // push
				//		m_Character->SetAnimationIndex(5);
				//	// >> ���尡 �ȵǼ� ��� ��� ����ó�� ����
				//}
				// else
				//m_Character->SetAnimationIndexBlend(5); // push
				//m_Character->SetAnimationIndex(5);
				speed = -1.0f;
				break;

			case PlayerInputType::eHoldPush:
				if (m_isGrab)
				{
					if (m_nGrabAbleObeject != -1)
					{
						D3DXVECTOR3 v;
						v = g_pObjectManager->GetVecPObejct()[m_nGrabAbleObeject]->GetPosition() - this->GetPosition();
						v.y -= 0.5f;
						D3DXVec3Normalize(&v, &v);
						g_pObjectManager->GetVecPObejct()[m_nGrabAbleObeject]->SetPusingForce(v);
						rotation = m_preRotation;
						speed = 1.0f;

						m_Character->SetAnimationIndex(5);
					}
					// if (m_Character->CheckAnimationEnd())
				}
				else
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(10); // Idle
					speed = -1.0f;
				}
				//if (m_nGrabAbleObeject != -1)
				//{
				//	if (m_Character->CheckAnimationEnd())
				//		m_Character->SetAnimationIndex(5); // Push
				//}
				//else
				//	if (m_Character->CheckAnimationEnd())
				//		m_Character->SetAnimationIndex(10); // Idle

				break;
			case PlayerInputType::eHoldPull:
				if (m_isGrab)
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(4);
				}
				else
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(10); // Idle
				}
				//if (m_nGrabAbleObeject != -1)
				//{
				//	if (m_Character->CheckAnimationEnd())
				//		m_Character->SetAnimationIndex(4); // Pull
				//}
				//else
				//	if (m_Character->CheckAnimationEnd())
				//		m_Character->SetAnimationIndex(10); // Idle
				speed = -1.0f;
				break;

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

			default:
				if (m_Character->CheckAnimationEnd()) // !m_isJump || 
				{
					speed = -1.0f;
					m_Character->SetAnimationIndex(10); // Idle
				}
				break;
			}
		} // << eInputEvent

		if (speed > 0 && m_Character->CheckAnimationEnd())
		{
			m_preRotation = rotation;

			// >> Ư�� �ִϸ��̼� ��� �� �̵� ���� ����
			if(!m_isJump)
				m_Character->SetAnimationIndex(9); // Walk
			// m_Character->SetAnimationIndex(9); // Walk

			// >> todo : �ӵ� ��ȭ �����ؼ� �޸��� �߰�
			// >> �Է� �ð��� ���� �޸��� ��ȭ?

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

void CCharacter::ColliderObject()
{
	for (int i = 0; i < g_pObjectManager->GetVecIObject().size(); i++)
	{
		//if (m_Character->GetOBB()->IsCollision(g_pObjectManager->GetVecIObject()[i]->GetOBB(), &m_vContactNormal, &m_fPenetration))
		if (m_Character->GetOBB()->IsCollision(g_pObjectManager->GetVecIObject()[i]->GetOBB()))
		{
			if (g_pObjectManager->GetVecIObject()[i]->GetObjType() == eBook)
			{
				g_pObjectManager->GetVecIObject()[i]->SetBool(true);
				continue;
			}
				
			//if (g_pObjectManager->GetVecIObject()[i]->GetObjType() <= eTile13 || g_pObjectManager->GetVecIObject()[i]->GetObjType() == eBridge)
			//{
			//	BOOL hit = false;
			//	DWORD FaceIndex;
			//	float u, v, dist;
			//	D3DXVECTOR3 rayOrigin = m_Ray.GetOrigin();
			//	D3DXMATRIXA16 matInverse;
			//	D3DXMatrixInverse(&matInverse, NULL, &g_pObjectManager->GetVecIObject()[i]->GetOBB()->GetOBBWorldMatrix());
			//	D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &matInverse);
			//	D3DXIntersect(g_pObjectManager->GetVecIObject()[i]->GetMesh(), &rayOrigin, &m_Ray.GetDirection(), &hit, &FaceIndex, &u, &v, &dist, NULL, NULL);
			//	if (hit)
			//	{
			//		if (m_fHeightTile < m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y)
			//			m_fHeightTile = m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y;
			//		//cout << dist*g_pObjectManager->GetVecIObject()[i]->GetScale().y << endl;
			//		//m_vPosition.y += dist*g_pObjectManager->GetVecIObject()[i]->GetScale().y;
			//		//m_fHeightTile =	m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y;
			//		//m_vPosition.y += m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y;
			//		//m_fHeightTile = m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y;
			//		//m_vPosition.y = m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y;
			//	}
			//	m_isCollidedTile = true;
			//	m_isCollided = true;
			//}
			m_isCollided = true;
			return;
		}
	}
	for (int i = 0; i < g_pObjectManager->GetVecPObejct().size(); i++)
	{
		if (m_Character->GetOBB()->IsCollision(g_pObjectManager->GetVecPObejct()[i]->GetOBB()))
		{
			D3DXVECTOR3 grabvector = g_pObjectManager->GetVecPObejct()[i]->GetPosition() - this->GetPosition();
			float grabradian = D3DXVec3Dot(&this->m_vDirection, &grabvector) / (D3DXVec3Length(&m_vDirection) * D3DXVec3Length(&grabvector));
			if (grabradian > cosf(D3DXToRadian(45)))
			{
				m_isGrab = true;
				m_nGrabAbleObeject = i;
			}
			else
			{
				m_isGrab = false;
				m_nGrabAbleObeject = -1;
			}
			m_isCollided = true;
			return;
		}
	}
	m_isCollided = false;
	m_isGrab = false;
}

CCharacter::~CCharacter()
{
	SafeDelete(m_Character);
}

void CCharacter::Setup()
{
	m_Character = new CSkinnedMesh;
	m_Character->SetUp("Resource/XFile/Character", "AnimationCharacter.X");
	// m_Character->SetAnimationIndexBlend(8);
	m_Character->SetAnimationIndex(10);

	// Ray y check
	D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 4.5f, 0);
	m_Ray.SetOrigin(rayOrigin);
	m_Ray.SetDirection(D3DXVECTOR3(0, -1, 0));
}

void CCharacter::Update(D3DXVECTOR3 cameradirection)
{
	m_vDirection = cameradirection;
	D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 4.5f, 0);
	m_Ray.SetOrigin(rayOrigin);
	//if (m_isJump)
	//{
	//	// jumping = true;
	//	if (m_vPosition.y <= 3.f)
	//	{
	//		m_vPosition.y += 0.005f;
	//		if (m_vPosition.y >= 3.f)
	//		{
	//			jumpis = true;
	//			m_jump = false;
	//		}
	//	}
	//}
	//if (jumpis == true)
	//{
	//	m_vPosition.y -= 0.005f;
	//	if (m_vPosition.y <= 0)
	//	{
	//		jumpis = false;
	//		jumping = false;
	//	}
	//	m_Character->SetAnimationIndexBlend(6); // fall
	//}
	//if (m_jump)
	//{
	//	jumping = true;
	//	if (m_vPosition.y <= 3.f)
	//	{
	//		m_vPosition.y += 0.005f;
	//		if (m_vPosition.y >= 3.f)
	//		{
	//			jumpis = true;
	//			m_jump = false;
	//		}
	//	}
	//}
	//if (jumpis == true)
	//{
	//	CCharacter::ColliderObject();
	//	if(!m_isCollided && m_vPosition.y > 0)
	//		m_vPosition.y -= 0.005f;
	//	else
	//	{
	//		jumpis = false;
	//		jumping = false;
	//		//if (m_vPosition.y <= 0)
	//		//{
	//		//	jumpis = false;
	//		//	jumping = false;
	//		//}
	//	}
	//	
	//	m_Character->SetAnimationIndexBlend(6); // fall
	//}
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

//int CCharacter::Update(vector<PObject*> ObjectPosition, float duration)
//{
//	//if (m_pOBB)
//	//	m_pOBB->Update(&m_matWorld);
//	//for (int i = 0; i < ObjectPosition.size(); ++i)
//	//{
//	//	if (ObjectPosition[i]->GetPosition().x - m_vPosition.x < 1.0f
//	//		&& ObjectPosition[i]->GetPosition().z - m_vPosition.z < 1.0f
//	//		&& ObjectPosition[i]->GetPosition().x - m_vPosition.x > -1.0f
//	//		&& ObjectPosition[i]->GetPosition().z - m_vPosition.z > -1.0f
//	//		&& ObjectPosition[i]->GetPosition().y - m_vPosition.y <  1.0f
//	//		&& ObjectPosition[i]->GetPosition().y - m_vPosition.y > -1.0f)
//	//	{
//	//		//m_nGrabAbleObeject = i;
//	//		return i;
//	//	}
//	//}
//	////m_nGrabAbleObeject = -1;
//	//return -1;
//}

void CCharacter::Update(float duration)
{
	D3DXVECTOR3 tempPos = m_vPosition;
	if (m_isJump)
	{
		// cout << radian << endl;
		// radian += D3DXToRadian(180.0f * duration);
		m_fRadianJump += 7.0f * duration;
		tempPos.y = m_fMaxJumpHeight * sinf(m_fRadianJump);

		// >> todo : collision
		if (true)
			m_vPosition = tempPos;

		if (m_fRadianJump >= D3DXToRadian(180.0f))
		{
			if(m_Character->CheckAnimationEnd())
				m_Character->SetAnimationIndexBlend(10); // idle

			m_isFallAni = false;
			m_isJump = false;
			m_fRadianJump = 0;
		}
		else if (m_fRadianJump >= D3DXToRadian(90.0f) && !m_isFallAni)
		{
			// >> todo : �浹 ���� ��쵵 ���� ��������(�Ӹ� �� ��ֹ�)
			m_Character->SetAnimationIndex(6); // fall
			m_isFallAni = true;
		}
	}

	if (m_Character)
	{
		m_Character->Update(duration);
		m_Character->SetTransform(&m_matWorld);
	}
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
	//D3DXVECTOR3 m_position = m_vPosition;
	CCharacter::ColliderObject();
	//m_vPosition.y = m_fHeightTile;
	//m_fHeightTile = 0.0f;
	if (m_isCollided)
	{
		m_vPosition = m_position;
		//if (m_isCollidedTile)
		//{
		//	m_vPosition.y = m_fHeightTile;
		//	m_fHeightTile = 0.0f;
		//}
		//if (m_isCollidedTile)
		//{
		//	//m_vPosition.y += 0.005f;
		//	D3DXVec3Normalize(&m_vContactNormal, &m_vContactNormal);
		//	m_vPosition += m_vContactNormal * m_fPenetration;
 		//	//m_vPosition.x += m_vContactNormal.x * m_fPenetration;
		//	//m_vPosition.y += m_vContactNormal.y * m_fPenetration;
		//	//m_vPosition.z += m_vContactNormal.z * m_fPenetration;
		//	//cout << "m_vContactNormal : " << m_vContactNormal.x << ' ' << m_vContactNormal.y << ' ' << m_vContactNormal.z << endl;
		//	//cout << m_fPenetration << endl;
		//	m_isCollidedTile = false;
		//}
	}
	else
	{
		m_position = m_vPosition;
	}
	//cout << "m_vDirection : " << m_vDirection.x << ' ' << m_vDirection.y << ' ' << m_vDirection.z << endl;
	//m_vPosition.y = m_fHeightTile;
	//m_fHeightTile = 0.0f;
	m_vPosition = m_vPosition + (m_vDirection * velocity);
	//if (m_vPosition.y >= 0)
	//	m_vPosition.y -= 0.005f;
	//else
	//	m_vPosition.y = 0;
	for (int i = 0; i < g_pObjectManager->GetVecIObject().size(); i++)
	{
		if (g_pObjectManager->GetVecIObject()[i]->GetObjType() <= eTile13 || g_pObjectManager->GetVecIObject()[i]->GetObjType() == eBridge)
		{
			BOOL hit = false;
			DWORD FaceIndex;
			float u, v, dist;
			D3DXVECTOR3 rayOrigin = m_Ray.GetOrigin();
			D3DXMATRIXA16 matInverse;
			D3DXMatrixInverse(&matInverse, NULL, &g_pObjectManager->GetVecIObject()[i]->GetOBB()->GetOBBWorldMatrix());
			D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &matInverse);
			D3DXIntersect(g_pObjectManager->GetVecIObject()[i]->GetMesh(), &rayOrigin, &m_Ray.GetDirection(), &hit, &FaceIndex, &u, &v, &dist, NULL, NULL);
			if (hit)
			{
				if (m_fHeightTile < m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y)
					m_fHeightTile = m_Ray.GetOrigin().y - dist * g_pObjectManager->GetVecIObject()[i]->GetScale().y;
			}
		}
	}
	m_vPosition.y = m_fHeightTile;
	m_fHeightTile = 0.0f;
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
		background->SetBool(true);
	}
	else
	{
		m_isCollided = false;
		background->SetBool(false);
	}
}