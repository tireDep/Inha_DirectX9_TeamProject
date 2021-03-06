#include "stdafx.h"
#include "PhysicsSphere.h"

CPhysicsSphere::CPhysicsSphere()
    : m_fRadius(0.21f)
    , m_vVelocity(0, 0, 0)
{
    //D3DXMatrixIdentity(&m_matWorld);
    //D3DXMatrixIdentity(&m_matLocal);
    Setup();
}

CPhysicsSphere::~CPhysicsSphere()
{
}

void CPhysicsSphere::Setup()
{
    m_strName = string("PhysicsSphere") + to_string(m_nRefCount);
    D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pMesh, NULL);
    m_stMtl.Ambient = BLUE;
    m_stMtl.Diffuse = BLUE;
    m_stMtl.Specular = BLUE;
}

void CPhysicsSphere::Update(float duration)
{
    SphereUpdate(duration);
}

void CPhysicsSphere::Render()
{
    g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matLocal);
    //g_pD3DDevice->MultiplyTransform(D3DTS_WORLD, &m_matLocal);
    g_pD3DDevice->SetTexture(0, 0);
    g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
    g_pD3DDevice->SetMaterial(&m_stMtl);
    m_pMesh->DrawSubset(0);
}

void CPhysicsSphere::SphereUpdate(float duration)
{
    const float TIME_SCALE = 3.3f;
    D3DXVECTOR3 cord = this->getCenter();
    float vx = abs(this->getVelocity_X());
    float vz = abs(this->getVelocity_Z());
    float vy = abs(this->getVelocity_Y());
    if (vx > 0.01 || vz > 0.01 || vy > 0.0)
    {
        float tX = cord.x + TIME_SCALE * duration * m_vVelocity.x;
        float tZ = cord.z + TIME_SCALE * duration * m_vVelocity.z;
        float tY = cord.y + TIME_SCALE * duration * m_vVelocity.y;
        this->setCenter(tX, tY, tZ);
    }
    else
    {
        this->setPower(0, 0, 0);
    }

    float rate = 1 - (1 - 0.999) * duration * 400;
    if (rate < 0)
        rate = 0;

    this->setPower(getVelocity_X() * rate, getVelocity_Y() * rate, getVelocity_Z() * rate);
    //this->setPower(getVelocity_X(), getVelocity_Z());
}

void CPhysicsSphere::Hitball(CPhysicsSphere& ball)
{
    static D3DXVECTOR3 direction;
    static D3DXVECTOR3 warpVector;
    static D3DXVECTOR3 totalVelocity;
    static D3DXVECTOR3 normalizedDirection;
    static D3DXVECTOR3 ballVelocity;
    static D3DXVECTOR3 thisVelocity;
    static const float fix = 1.1f;
    static float distance;
    static float overlapInterval;

    if (hasIntersected(ball))
    {
        direction = this->getCenter() - ball.getCenter();
        distance = sqrt(direction.x * direction.x + direction.z * direction.z);
        overlapInterval = 2 * ball.getRadius() - distance;
        warpVector = fix * direction * (overlapInterval / (2 * ball.getRadius() - overlapInterval));

        if (((ball.m_vVelocity.x * ball.m_vVelocity.x) + (ball.m_vVelocity.z * ball.m_vVelocity.z) + (ball.m_vVelocity.y * ball.m_vVelocity.y) >=
            ((this->m_vVelocity.x * this->m_vVelocity.x) + (this->m_vVelocity.z * this->m_vVelocity.z) + (this->m_vVelocity.y * this->m_vVelocity.y))))
        {
            ball.Hitball(*this);
            return;
        }
        else
        {
            this->setCenter(this->getCenter().x + warpVector.x, this->getCenter().y +warpVector.y, this->getCenter().z + warpVector.z);
        }

        totalVelocity = D3DXVECTOR3(getVelocity_X() + ball.getVelocity_X(), 0, getVelocity_Z() + ball.getVelocity_Z());
        normalizedDirection = (-1) * direction / distance;

        ballVelocity = normalizedDirection * (normalizedDirection.x * totalVelocity.x + normalizedDirection.z * totalVelocity.z);
        thisVelocity = -ballVelocity + totalVelocity;

        this->setPower(thisVelocity.x, ballVelocity.y, thisVelocity.z);
        ball.setPower(ballVelocity.x, ballVelocity.y, ballVelocity.z);

        if (hasIntersected(ball))
            this->setCenter(this->getCenter().x + 3 * warpVector.x, this->getCenter().y, this->getCenter().z + 3 * warpVector.z);
    }
}

bool CPhysicsSphere::hasIntersected(CPhysicsSphere& ball)
{
    if (this == &ball)
        return false;

    D3DXVECTOR3 direction = this->getCenter() - ball.getCenter();
    float distance = D3DXVec3LengthSq(&direction);

    if (((this->getRadius() + ball.getRadius()) * (this->getRadius() + ball.getRadius())) < distance)
        return false;
    else
        return true;
}

void CPhysicsSphere::setPower(double vx, double vy, double vz)
{
    this->m_vVelocity.x = vx;
    this->m_vVelocity.y = vy;
    this->m_vVelocity.z = vz;
}

void CPhysicsSphere::setCenter(float x, float y, float z)
{
    D3DXMATRIXA16 m;
    m_vCenter.x = x;   m_vCenter.y = y;   m_vCenter.z = z;
    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}

D3DXVECTOR3 CPhysicsSphere::getCenter() const
{
    D3DXVECTOR3 org(m_vCenter.x, m_vCenter.y, m_vCenter.z);
    return org;
}

void CPhysicsSphere::ReceiveEvent(ST_EVENT eventMsg)
{

}