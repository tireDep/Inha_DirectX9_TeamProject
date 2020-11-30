#pragma once
class CTestAngleSet
{
private:
	float m_fXrotationAngle;	// x-Rotation Angle
	float m_fYrotationAngle;	// y-Rotation Angle
	float m_fZrotationAngle;	// z-Rotation Angle
	float CheckAngle(float angle);
public:
	CTestAngleSet();
	~CTestAngleSet();
	CTestAngleSet(float xRotation, float yRotation, float zRotation);
	CTestAngleSet(const CTestAngleSet &angleset);

	void setXAngle(float xRotation);
	void setYAngle(float yRotation);
	void setZAngle(float zRotation);

	float getXAngle();
	float getYAngle();
	float getZAngle(); 

	void SetRotation(float xRotation, float yRotation, float zRotation);
	CTestAngleSet &operator=(const CTestAngleSet &rightOperand);
};

