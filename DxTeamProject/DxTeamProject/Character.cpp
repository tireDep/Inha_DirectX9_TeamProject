#include "stdafx.h"
#include "Character.h"
#include "OBB.h"
#include "IObject.h"
#include "PObject.h"
#include "SkinnedMesh.h"

CCharacter::CCharacter()
	: m_vDirection(0, 0, 1)
	, m_vPosition(0, 1.0f, 0)
	, m_isCollided(false)
	, m_Character(NULL)
	, m_isColorChanged(false)
	, m_color(GRAY)
	, m_isGrab(false)
	, m_isJump(false)
	, m_fMaxJumpHeight(0.01f)
	, m_fRadianJump(0.0f)
	, m_isFallAni(false)
	, m_preRotation(0.0f)
	, m_vContactNormal(0, 0, 0)
	, m_fPenetration(0.0f)
	, m_isCollidedTile(false)
	, m_fHeightTile(0.0f)
	, m_fSpeed(0.0f)
	, m_fRotation(0.0f)
	, m_fGrabRotation(0.0f)
	, m_isReset(false)
	/// Presentation
#ifdef _DEBUG
	, m_saveZonePosition(5, 1, -5)
#else
	, m_saveZonePosition(5, 1, -5)
#endif
	, m_vGrabDirection(0, 0, 1)
	, m_vGrabCamDir(0, 0, 1)
	, Keep(false)
	, m_preJumpPosition(1.0f)
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

static PlayerInputType preInput;
void CCharacter::ReceiveEvent(ST_EVENT eventMsg)
{
	if (g_pGameManager->GetNowScene() != SceneType::eGameScene)
		return;

	m_fRotation = -1.0f;

	if (!g_pGameManager->GetUImode())
	{
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
			// >> 색 변화가 일어날 경우 그 방향(정면) 쳐다봄
		}

		if (eventMsg.eventType == EventType::eInputEvent)
		{
			if (preInput == PlayerInputType::eHoldPull && preInput != eventMsg.playerInput)
			{
				if(m_nGrabAbleObeject != -1)
					g_pObjectManager->GetVecPObejct()[m_nGrabAbleObeject]->SetVelocity(D3DXVECTOR3(0,0,0));
			}
			else
			{
				preInput = eventMsg.playerInput;
			}

			switch (eventMsg.playerInput)
			{
			case PlayerInputType::eJump:
				if (!m_isJump)
				{
					m_preJumpPosition = m_vPosition.y;
					m_isJump = true;
					m_vDirection.x = m_vDirection.z = 0.0f;
					m_Character->SetAnimationIndexBlend(7); // jump
					m_fSpeed = 10.0f;
				}
				break;

			case PlayerInputType::eHold:
				//if (m_isGrab)
				//{
				//	// if (m_Character->CheckAnimationEnd())
				//	// 	m_Character->SetAnimationIndex(5);
				//}
				//else
				//{
				//	if (m_Character->CheckAnimationEnd())
				//		m_Character->SetAnimationIndex(10); // Idle
				//}

				if (m_Character->CheckAnimationEnd())
					m_Character->SetAnimationIndex(10);
				// >> 애니메이션 없어서 Idle로 고정
				m_fSpeed = 0.0f;
				break;

			case PlayerInputType::eHoldPush:
				if (m_isGrab)
				{
					if (m_nGrabAbleObeject != -1)
					{
						D3DXVECTOR3 v;
						D3DXVec3Normalize(&v, &this->m_vGrabDirection);
						g_pObjectManager->GetVecPObejct()[m_nGrabAbleObeject]->SetVelocity(10.0f * v);
						// m_fRotation = m_preRotation;
						// DoRotation(m_fRotation);
						// m_fSpeed = 10.0f;
						// m_vDirection.y = 0;
						// m_vPosition += (m_vDirection * m_fSpeed * g_pTimeManager->GetElapsedTime());
						if (m_Character->CheckAnimationEnd())
							m_Character->SetAnimationIndex(5);
						m_fSpeed = 10.0f;
					}
				}
				else
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(10); // Idle
					m_fSpeed = 0.0f;
				}
				break;

			case PlayerInputType::eHoldPull:
				if (m_isGrab)
				{
					if (m_nGrabAbleObeject != -1)
					{
					D3DXVECTOR3 v;
					D3DXVec3Normalize(&v, &this->m_vGrabDirection);
					g_pObjectManager->GetVecPObejct()[m_nGrabAbleObeject]->SetVelocity(-10.0f * v);
					// m_fRotation = m_preRotation;
					// DoRotation(m_fRotation);
					// m_fSpeed = -10.0f;
					// m_vDirection.y = 0;
					// m_vPosition += (m_vDirection * m_fSpeed * g_pTimeManager->GetElapsedTime());
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(4);
					m_fSpeed = -10.0f;
					}
				}
				else
				{
					if (m_Character->CheckAnimationEnd())
						m_Character->SetAnimationIndex(10); // Idle
					m_fSpeed = 0.0f;
				}
				break;

			case PlayerInputType::eUp:
				m_fRotation = 0.0f;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eLeftUp:
				m_fRotation = D3DX_PI / 4.0f * -1;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eRightUp:
				m_fRotation = D3DX_PI / 4.0f;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eDown:
				m_fRotation = D3DX_PI;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eLeftDown:
				m_fRotation = D3DX_PI + D3DX_PI / 4.0f;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eRightDown:
				m_fRotation = (D3DX_PI + D3DX_PI / 4.0f) * -1;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eLeft:
				m_fRotation = -D3DX_PI / 2.0f;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eRight:
				m_fRotation = D3DX_PI / 2.0f;
				m_fSpeed = 10.0f;
				m_preRotation = m_fRotation;
				m_isGrab = false;
				break;

			case PlayerInputType::eReset:
				m_isReset = true;
				Reset();
				g_pObjectManager->Reset();
				g_pObjectManager->ResetCube = true;
				break;

			default:
				if (m_Character->CheckAnimationEnd()) // !m_isJump || 
				{
					m_fSpeed = 0.0f;
					m_Character->SetAnimationIndex(10); // Idle
				}
				g_pObjectManager->ResetCube = false;
				break;
			}
		} // << eInputEvent
	}
}

string CCharacter::GetName()
{
	return m_strName;
}

void CCharacter::ColliderObject()
{
	if (g_pObjectManager->GetVecMapObjCnt() > 0)
	{
		vector<IObject *> vecCheck = g_pObjectManager->GetMapVecIObject();
		ObjectType objType = ObjectType::eNull;
		int loopCnt = vecCheck.size();

		for (int i = 0; i < loopCnt; i++)
		{
			if (m_nGrabAbleObeject == i)
			{
				m_isCollided = false;
				continue;
			}

			objType = vecCheck[i]->GetObjType();

			if (m_Character->GetOBB()->IsCollision(vecCheck[i]->GetOBB()))
			{
				if (objType == eG_DoorFrame)
					if (vecCheck[i]->GetCondition())
						continue;

				if (objType == eOrb || objType == eBook)
				{
					//fout.open("OrbData.txt");

					vecCheck[i]->SetBool(true);

					//for (int i = 0; i < g_pObjectManager->GetVecIObject().size(); i++)				
					//	fout << g_pObjectManager->GetVecIObject()[i]->GetBool(); // 

					//fout.close();
					continue;
				}

				if (objType <= eTile13 || objType == eBridge)
				{
					//				if (m_isCollidedTile)
					continue;
				}
				if (objType == eTrigger)
				{
					m_saveZonePosition = vecCheck[i]->SendPosition();
					ZoneType zone = vecCheck[i]->ZoneIndex();

					if (zone == ZoneType::eFall)
					{

						if (g_pSoundManager->isPlaying() == false)
						{
							g_pSoundManager->PlayBGM("w_first");
						}
					}

					else if (zone == ZoneType::eWinter)
					{

						if (g_pSoundManager->isPlaying() == false)
						{
							g_pSoundManager->PlayBGM("f_first");
						}

					}
					else  if (zone == ZoneType::eZone)
					{
						cout << "save" << endl;
						g_pSoundManager->Stop();

					}
					ofstream fout;

					fout.open("SaveData.txt");
					fout << m_saveZonePosition.x << " " << m_saveZonePosition.y << " " << m_saveZonePosition.z << endl;
					fout.close();

					continue;
				}


				m_isGrab = false; // >> 잡기 상태시 충돌나면 잡기 해제
				m_isCollided = true;
				return;
			}
		}
	}

	if (m_isGrab)
	{
		m_isCollided = false;
		// >> 없으면 충돌 상태로 판단되서 캐릭터가 이동하지 않음
		return;
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
				m_vGrabDirection = this->m_vDirection;
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

void CCharacter::Reset()
{
	// Need To Modify... SavePosition;
	//m_vPosition = D3DXVECTOR3(m_saveZonePosition.x, m_saveZonePosition.y - 0.5f, m_saveZonePosition.z);
	m_vPosition = m_saveZonePosition;

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRotY);
	D3DXMatrixIdentity(&matT);

	// >> reset list?
	m_isCollided = false;
	m_isColorChanged = false;
	// m_color = GRAY;
	m_isGrab = false;
	m_isJump = false;
	m_fMaxJumpHeight = 0.01f; 
	m_fRadianJump = 0.0f;
	m_isFallAni = false;
	m_preRotation = 0.0f;
	m_vContactNormal = D3DXVECTOR3(0, 0, 0);
	m_fPenetration = 0.0f; 
	m_isCollidedTile = false; 
	m_fHeightTile = 0.0f;
	m_fSpeed = 0.0f;
	m_fRotation = 0.0f;
	m_fGrabRotation = 0.0f;
	m_isReset = false;
	m_vGrabDirection = D3DXVECTOR3(0, 0, 1);
	m_vGrabCamDir = D3DXVECTOR3(0, 0, 1);
	Keep = false;
	m_preJumpPosition = 1.0f;
}

void CCharacter::SaveData(D3DXVECTOR3 pos)
{
	m_saveZonePosition = pos;
}

CCharacter::~CCharacter()
{
	SafeDelete(m_Character);
}

void CCharacter::Setup()
{
	m_vPosition = m_saveZonePosition;

	m_Character = new CSkinnedMesh;
	m_Character->SetUp("Resource/XFile/Character", "AnimationCharacter.X");
	m_Character->SetAnimationIndex(10);

	D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 0.5f, 0);
	m_Ray.SetOrigin(rayOrigin);
	m_Ray.SetDirection(D3DXVECTOR3(0, -1, 0));
}

void CCharacter::SaveSetup()
{
	m_vPosition = m_saveZonePosition;
	
	m_Character = new CSkinnedMesh;
	m_Character->SetUp("Resource/XFile/Character", "AnimationCharacter.X");
	// m_Character->SetAnimationIndexBlend(8);
	m_Character->SetAnimationIndex(10);

	// Ray y check
	//D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 0.95f, 0);	// 0.95 Need To Modify...
	D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 0.5f, 0);	// TEST
	m_Ray.SetOrigin(rayOrigin);
	m_Ray.SetDirection(D3DXVECTOR3(0, -1, 0));
}

void CCharacter::Update(D3DXVECTOR3 cameradirection)
{
	if (!m_isGrab)
		m_vDirection = cameradirection;
	else
		m_vGrabCamDir = cameradirection;
}

void CCharacter::Update(float duration)
{
	static D3DXVECTOR3 prePos = m_vPosition;
	static float dir = 1.0f;

	if (m_isJump)
	{
		m_fRadianJump += 5.0f * duration;
		m_vPosition.y += m_fMaxJumpHeight * sinf(m_fRadianJump) * dir;
		if (m_preRotation == m_fRotation)
		{
			DoRotation(m_preRotation);
			m_vPosition += (m_vDirection * m_fSpeed * duration);
		}
		
		if (m_fRadianJump >= D3DXToRadian(180.0f))				// Low Spot	
		{
			if (m_Character->CheckAnimationEnd())
				m_Character->SetAnimationIndexBlend(10); // idle
			m_isFallAni = false;
			m_isJump = false;
			m_fRadianJump = 0;
			m_fSpeed = 0.0f;
			dir = 1.0f;
		}
		else if (m_fRadianJump >= D3DXToRadian(90.0f) && !m_isFallAni)	// High Spot
		{
			m_Character->SetAnimationIndex(6); // fall
			m_isFallAni = true;
			m_fSpeed = 0.0f;
			dir = -1.0f;
		}
	}
	else
	{
		if (m_fSpeed > 0 && m_Character->CheckAnimationEnd() && !m_isGrab)
		{
			m_Character->SetAnimationIndex(9); // Walk

			DoRotation(m_fRotation);
			m_vPosition += (m_vDirection * m_fSpeed * duration);
		}
		else if (m_isGrab)
		{
			if (D3DXVec3Dot(&m_vGrabCamDir, &m_vDirection) < 0)
				m_vDirection = m_vGrabCamDir;	// >> 잡기 상태일 때 일정 각도 이상이면 dir 변경

			m_vDirection.y = 0;
			m_fRotation = m_preRotation;

			DoRotation(m_fRotation);
			m_vPosition += (m_vDirection * m_fSpeed * duration);

			// >> todo : 일정 거리 이상시 해제 필요?
			// >> todo : 밀기+당기기 상태일 때 마우스 이동하면 잡기 해제 필요?
			// -> 오브젝트방향과 플레이어 이동 방향이 달라짐
		}

		// >> DoRotation if문 밖으로 빼면 매번 동작해서 안됨
	}

	//if (m_isFallAni || !m_isJump)
	if(m_preJumpPosition > m_vPosition.y || !m_isJump)
	//if (prejumpyposition > m_vPosition.y)
	{
#ifdef _DEBUG
		D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 0.6f, 0);
		m_Ray.SetOrigin(rayOrigin);
#else
		D3DXVECTOR3 rayOrigin = this->GetPosition() + D3DXVECTOR3(0, 0.7f, 0);
		m_Ray.SetOrigin(rayOrigin);
#endif // DEBUG

		if (g_pObjectManager->GetVecMapObjCnt() > 0)
		{
			vector<IObject *> vecCheck = g_pObjectManager->GetMapVecIObject();
			ObjectType objType = ObjectType::eNull;
			int loopCnt = vecCheck.size();

			for (int i = 0; i < loopCnt; i++)
			{
				objType = vecCheck[i]->GetObjType();
				if (objType <= eTile13 || objType == eBridge)
				{
					BOOL hit = false;
					DWORD FaceIndex;
					float u, v, dist;
					D3DXVECTOR3 rayOrigin = m_Ray.GetOrigin();
					D3DXMATRIXA16 matInverse;
					D3DXMatrixInverse(&matInverse, NULL, &vecCheck[i]->GetOBB()->GetOBBWorldMatrix());
					D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &matInverse);
					D3DXIntersect(vecCheck[i]->GetMesh(), &rayOrigin, &m_Ray.GetDirection(), &hit, &FaceIndex, &u, &v, &dist, NULL, NULL);
					if (hit)
					{
						if (m_fHeightTile < m_Ray.GetOrigin().y - dist * vecCheck[i]->GetScale().y)
							m_fHeightTile = m_Ray.GetOrigin().y - dist * vecCheck[i]->GetScale().y;
					}
				}
			}
			if (m_fHeightTile != 0)
			{
				m_vPosition.y = m_fHeightTile;
				m_fHeightTile = 0.0f;
			}
		}
	}

	CCharacter::ColliderObject();
	if (m_isReset)
	{
		m_isCollided = false;
		m_isGrab = false;
		m_isReset = false;
	}

	if (m_isCollided)
	{
		m_vPosition = prePos;
	}
	else
	{
		prePos = m_vPosition;
	}

	if (m_Character)
	{
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		m_matWorld = m_matRotY * matT;
		m_Character->SetTransform(&m_matWorld);
		m_Character->Update(duration);
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

void CCharacter::Render()
{
	if (m_Character)
		m_Character->Render(NULL);
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
	return m_fRotation;
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