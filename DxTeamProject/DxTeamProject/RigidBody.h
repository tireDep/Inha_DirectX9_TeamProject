#pragma once
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
protected:
	// �߷¸��� ����
	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3		m_vPosition;				// ��ġ
	D3DXVECTOR3		m_vVelocity;				// �ӵ�
	D3DXVECTOR3		m_vAcceleration;			// ���ӵ�
	float			m_finverseMass;				// ������. ���α׷��ֿ��� ������ ǥ���ϴ� �κ�. 
												// �������� �ʴ� ���̳� �ٴ� ���� �κ��� 0���� �θ� ���� �ƹ��� ���� �־ �����ȴ�.
	float			m_flinearDamping;			// ������� ����(�⺻ ������)
	D3DXMATRIXA16	m_matWorld;					// �������

	// ���� � ����
	D3DXVECTOR3		m_vforceAccum;				// ������ ������ ��

	// ���� � ����
	//{
	//	D3DXVECTOR3		m_vlastFrameAcceleration;
	//	bool			m_isAwake;
	//}

	// �� �Ʒ��� ȸ���� ���� �κ�
	//{
		//float			m_fangularDamping;
		//D3DXQUATERNION	m_qDirection;
		//D3DXVECTOR3		m_vRotation;
		//D3DXVECTOR3		m_vtorqueAccum;
		//D3DXMATRIXA16	m_inverseInertiaTensorWorld;
	//}
public:
	// �߷¸� ����
	void intergrate(float duration);
	void clearAccumulators();

	// ���� � ����
	bool hasFiniteMass() const;
	void addForce(const D3DXVECTOR3& force);
	float getMass() const;

	/// �� �Ʒ� �κ��� ���� ����
	//{
	//	void addForceAtPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);
	//	void addForceAtBodyPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);
	//	D3DXVECTOR3 getPointInLocalSpace(const D3DXVECTOR3& point) const;
	//	void calculateDerivedData();
	//}
	
	// �� �Ʒ� �κ��� �ۿ��ϴ��� Ȯ���� ���� ��ø� �����ص� �κ�
	void Setup(D3DXVECTOR3 position, D3DXVECTOR3 acc);
	void Update();
	void Render();
};