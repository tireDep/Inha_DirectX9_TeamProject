#include "stdafx.h"
#include "ParticleContactResolver.h"
#include "ParticleContact.h"

CParticleContactResolver::~CParticleContactResolver()
{
}

CParticleContactResolver::CParticleContactResolver(UINT iterations) : m_unIterations(iterations)
{
}

void CParticleContactResolver::setIterations(UINT iterations)
{
	m_unIterations = iterations;
}

void CParticleContactResolver::resolveContacts(CParticleContact * contactArray, UINT numContacts, float duration)
{
	UINT i;
	m_unIterationsUsed = 0;
	while (m_unIterationsUsed < m_unIterations)
	{
		float max = FLT_MAX;
		UINT maxIndex = numContacts;
		for (i = 0; i < numContacts; i++)
		{
			float separatingVelocity = contactArray[i].calculateSeparatingVelocity();
			if (separatingVelocity < max && 
			   (separatingVelocity < 0 || contactArray[i].m_fpenetration>0))
			{
				max = separatingVelocity;
				maxIndex = i;
			}
		}

		if (maxIndex == numContacts)
			break;

		contactArray[maxIndex].Resolve(duration);

		D3DXVECTOR3 *move = contactArray[maxIndex].m_vParticleMovement;
		for (i = 0; i < numContacts; i++)
		{
			if (contactArray[i].particle[0] == contactArray[maxIndex].particle[0])
			{
				contactArray[i].m_fpenetration -= D3DXVec3Dot(&contactArray[i].m_vContactNormal, &move[0]);
			}
			else if (contactArray[i].particle[0] == contactArray[maxIndex].particle[1])
			{
				contactArray[i].m_fpenetration -= D3DXVec3Dot(&contactArray[i].m_vContactNormal, &move[1]);
			}
			if (contactArray[i].particle[1])
			{
				if (contactArray[i].particle[1] == contactArray[maxIndex].particle[0])
				{
					contactArray[i].m_fpenetration -= D3DXVec3Dot(&contactArray[i].m_vContactNormal, &move[0]);
				}
				else if (contactArray[i].particle[1] == contactArray[maxIndex].particle[1])
				{
					contactArray[i].m_fpenetration -= D3DXVec3Dot(&contactArray[i].m_vContactNormal, &move[1]);
				} // << : particle [1] if inside
			} // << : particle [1] if outside
		} // << : for
		m_unIterationsUsed++;
	}
}