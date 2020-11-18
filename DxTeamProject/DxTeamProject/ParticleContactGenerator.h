#pragma once

class CParticleContact;

class CParticleContactGenerator
{
public:
	virtual UINT addContact(CParticleContact* contact, UINT limit) const = 0;
};