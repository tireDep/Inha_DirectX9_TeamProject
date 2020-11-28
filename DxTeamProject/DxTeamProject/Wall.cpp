#include "stdafx.h"
#include "Wall.h"
#include "PhysicsSphere.h"

CWall::CWall()
{
    D3DXMatrixIdentity(&m_mLocal);
    ZeroMemory(&m_mtrl, sizeof(m_mtrl));
    m_width = 0;
    m_depth = 0;

    m_pBoundMesh = NULL;
}

void CWall::Setup(float iwidth, float iheight, float idepth)
{

    m_mtrl.Ambient = RED;
    m_mtrl.Diffuse = RED;
    m_mtrl.Specular = RED;
    m_mtrl.Emissive = D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
    m_mtrl.Power = 5.0f;

    m_width = iwidth;
    m_height = iheight;
    m_depth = idepth;

    D3DXCreateBox(g_pD3DDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL);

}

void CWall::destroy(void)
{
    if (m_pBoundMesh != NULL) {
        m_pBoundMesh->Release();
        m_pBoundMesh = NULL;
    }
}
void CWall::draw()
{
    g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mLocal);
    //g_pD3DDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
    g_pD3DDevice->SetMaterial(&m_mtrl);
    m_pBoundMesh->DrawSubset(0);
}


bool CWall::Gravity(CPhysicsSphere& ball)
{
    float ballpos_y = ball.getCenter().y;
    if ((ballpos_y > 0))
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool CWall::hasIntersected(CPhysicsSphere& ball)
{
    float ballpos_x = ball.getCenter().x;
    float ballpos_z = ball.getCenter().z;
    //float ballpos_y = ball.getCenter().y;

    // for better collision detection // 벽을 좀 작게해서 보정
    float correction = 0.08f;

    // compare position with wall and ball position
    if ((ballpos_x >= ((4.5 - correction) - 0.21f))
        || (ballpos_x <= ((-1) * (4.5 - correction) + 0.21f))
        || (ballpos_z <= ((-1) * (3.0 - correction) + 0.21f))
        || (ballpos_z >= (3.0 - correction - 0.21f)))
    {
        return true;
    }
    else {
        return false;
    }
}
void CWall::hitBy(CPhysicsSphere& ball)
{
    static const float energyComsumption = 0.2f;
    // when collided, do physics
    //if (hasIntersected(ball)) {
    //
    //   // Collide with Upper Wall // 상위의 벽과 충돌
    //   if (ball.getCenter().z >= (3.0 - 0.21f))
    //   {
    //      ball.setCenter(ball.getCenter().x, ball.getCenter().y, 3 - 0.21f);
    //      ball.setPower(ball.getVelocity_X(),0, (-1)*ball.getVelocity_Z());

    //      // decrease velocity of ball after collision of wall
    //      ball.setPower(ball.getVelocity_X()*(1.0f - energyComsumption),0, ball.getVelocity_Z());
    //   }
    //   // Collide with Lower Wall // 하위의 벽과 충돌
    //   if (ball.getCenter().z <= (-(3.0) + 0.21f))
    //   {
    //      ball.setCenter(ball.getCenter().x, ball.getCenter().y, -3 + 0.21f);
    //      ball.setPower(ball.getVelocity_X(),0, (-1)*ball.getVelocity_Z());

    //      // decrease velocity of ball after collision of wall
    //      ball.setPower(ball.getVelocity_X()*(1.0f - energyComsumption),0, ball.getVelocity_Z());
    //   }
    //   // Collide with Left Wall // 좌측의 벽과 충돌
    //   if (ball.getCenter().x <= (-(4.5) + 0.21f))
    //   {
    //      ball.setCenter(-4.5 + 0.21f, ball.getCenter().y, ball.getCenter().z);
    //      ball.setPower((-1)*ball.getVelocity_X(),0, ball.getVelocity_Z());

    //      // decrease velocity of ball after collision of wall
    //      ball.setPower(ball.getVelocity_X()*(1.0f - energyComsumption),0, ball.getVelocity_Z());
    //   }
    //   // Collide with Right Wall // 우측의 벽과 충돌
    //   if (ball.getCenter().x >= (4.5 - 0.21f))
    //   {
    //      ball.setCenter(4.5 - 0.21f, ball.getCenter().y, ball.getCenter().z);
    //      ball.setPower((-1)*ball.getVelocity_X(),0, ball.getVelocity_Z());

    //      // decrease velocity of ball after collision of wall
    //      ball.setPower(ball.getVelocity_X()*(1.0f - energyComsumption),0, ball.getVelocity_Z());
    //   }
    //}

     // 바닥





    ball.setCenter(ball.getCenter().x, ball.getCenter().y, ball.getCenter().z);

    float BallPhyics = ball.getVelocity_Y() * 0.9f;
    ball.setPower(ball.getVelocity_X(), -BallPhyics, ball.getVelocity_Z());






}
void CWall::setPosition(float x, float y, float z)
{
    D3DXMATRIX m;
    this->m_y = y;
    this->m_x = x;
    this->m_z = z;

    WallPos = D3DXVECTOR3(x, y, z);
    D3DXMatrixTranslation(&m, x, y, z);
    setLocalTransform(m);
}


D3DXVECTOR3 CWall::GetPosition()
{
    return WallPos;
}