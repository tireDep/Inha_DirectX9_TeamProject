#include "stdafx.h"
#include "TestAngleSet.h"

float CTestAngleSet::CheckAngle(float angle)
{
	float tempAngle = angle;
	tempAngle = (tempAngle < 0.0) ? -1 * tempAngle : tempAngle;
	for (; tempAngle > 2 * D3DX_PI; tempAngle -= 2 * D3DX_PI){	}
	tempAngle = (angle < 0.0) ? -1 * tempAngle : tempAngle;
	return tempAngle;
}

CTestAngleSet::CTestAngleSet()
	: m_fXrotationAngle(0.0f)
	, m_fYrotationAngle(0.0f)
	, m_fZrotationAngle(0.0f)
{
}

CTestAngleSet::~CTestAngleSet()
{
}

CTestAngleSet::CTestAngleSet(float xRotation, float yRotation, float zRotation)
{
	m_fXrotationAngle = CheckAngle(xRotation);
	m_fYrotationAngle = CheckAngle(yRotation);
	m_fZrotationAngle = CheckAngle(zRotation);
}

CTestAngleSet::CTestAngleSet(const CTestAngleSet & angleset)
{
	setXAngle(angleset.m_fXrotationAngle);
	setYAngle(angleset.m_fYrotationAngle);
	setZAngle(angleset.m_fZrotationAngle);
}

void CTestAngleSet::setXAngle(float xRotation)
{
	m_fXrotationAngle = CheckAngle(xRotation);
}

void CTestAngleSet::setYAngle(float yRotation)
{
	m_fYrotationAngle = CheckAngle(yRotation);
}

void CTestAngleSet::setZAngle(float zRotation)
{
	m_fZrotationAngle = CheckAngle(zRotation);
}

float CTestAngleSet::getXAngle()
{
	return m_fXrotationAngle;
}

float CTestAngleSet::getYAngle()
{
	return m_fYrotationAngle;
}

float CTestAngleSet::getZAngle()
{
	return m_fZrotationAngle;
}

void CTestAngleSet::SetRotation(float xRotation, float yRotation, float zRotation)
{
	setXAngle(xRotation);
	setYAngle(yRotation);
	setZAngle(zRotation);
}

CTestAngleSet & CTestAngleSet::operator=(const CTestAngleSet & rightOperand)
{
	setXAngle(rightOperand.m_fXrotationAngle);
	setYAngle(rightOperand.m_fYrotationAngle);
	setZAngle(rightOperand.m_fZrotationAngle);

	return (*this);
}