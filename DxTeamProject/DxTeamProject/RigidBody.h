#pragma once
class CRigidBody
{
public:
	CRigidBody();
	~CRigidBody();
protected:
	// 중력만을 구현
	vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3		m_vPosition;				// 위치
	D3DXVECTOR3		m_vVelocity;				// 속도
	D3DXVECTOR3		m_vAcceleration;			// 가속도
	float			m_finverseMass;				// 역질량. 프로그래밍에서 질량을 표현하는 부분. 
												// 움직이지 않는 벽이나 바닥 같은 부분을 0으로 두면 힘을 아무리 높게 주어도 고정된다.
	float			m_flinearDamping;			// 직선운동의 댐핑(기본 마찰력)
	D3DXMATRIXA16	m_matWorld;					// 월드행렬

	// 직선 운동 구현
	D3DXVECTOR3		m_vforceAccum;				// 가해진 힘들의 합

	// 직선 운동 구현
	//{
	//	D3DXVECTOR3		m_vlastFrameAcceleration;
	//	bool			m_isAwake;
	//}

	// 이 아래는 회전에 대한 부분
	//{
		//float			m_fangularDamping;
		//D3DXQUATERNION	m_qDirection;
		//D3DXVECTOR3		m_vRotation;
		//D3DXVECTOR3		m_vtorqueAccum;
		//D3DXMATRIXA16	m_inverseInertiaTensorWorld;
	//}
public:
	// 중력만 구현
	void intergrate(float duration);
	void clearAccumulators();

	// 직선 운동 구현
	bool hasFiniteMass() const;
	void addForce(const D3DXVECTOR3& force);
	float getMass() const;

	/// 이 아래 부분은 추후 구현
	//{
	//	void addForceAtPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);
	//	void addForceAtBodyPoint(const D3DXVECTOR3& force, const D3DXVECTOR3& point);
	//	D3DXVECTOR3 getPointInLocalSpace(const D3DXVECTOR3& point) const;
	//	void calculateDerivedData();
	//}
	
	// 이 아래 부분은 작용하는지 확인을 위해 잠시만 구현해둔 부분
	void Setup(D3DXVECTOR3 position, D3DXVECTOR3 acc);
	void Update();
	void Render();
};