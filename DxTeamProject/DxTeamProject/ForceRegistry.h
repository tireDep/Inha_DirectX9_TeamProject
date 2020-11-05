#pragma once

class CRigidBody;
class CForceGenerator;

class CForceRegistry
{
protected:
	struct ForceRegistration
	{
		CRigidBody *body;
		CForceGenerator *fg;
	};
	typedef vector<ForceRegistration> Registry;
	Registry registrations;
public:
	void add(CRigidBody* body, CForceGenerator *fg);
	void remove(CRigidBody* body, CForceGenerator *fg);
	void clear();
	void updateForces(float duration);
};