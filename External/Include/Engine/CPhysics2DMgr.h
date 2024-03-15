#pragma once

#include <box2d\\b2_world_callbacks.h>

// 충돌 콜백 클래스
class CollisionCallback : public b2ContactListener
{
public:
    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;
};

class b2World;
class CGameObject;
class CCollider2D;

class CPhysics2DMgr : public CSingleton<CPhysics2DMgr>
{
    SINGLE(CPhysics2DMgr);

private:
    b2World* m_PhysicsWorld;
    CollisionCallback m_CallbackInst;
    vector<CGameObject*> m_vecPhysicsObj;

    unsigned short m_Matrix[LAYER_MAX];

    const float m_PPM; // PixelPerMeter

public:
    void tick();

    void OnPhysics2DStart();
    void OnPhysics2DStop();

public:
    void LayerCheck(UINT _LeftLayer, UINT _RightLayer, bool _bCheck = true);
    void LayerCheck(CLevel* _CurLevel, const wstring& _LeftLayer, const wstring& _RightLayer);

    void EnableAllLayer();
    void DisableAllLayer();

    unsigned short GetCollisionLayer(UINT idx) const { return m_Matrix[idx]; }
    void SetCollisionLayer(UINT idx, UINT row) { m_Matrix[idx] = row; }

    CGameObject* CollisionCheck(Vec2 _point);

public:
    const float GetPPM() const { return m_PPM; }

private:
    void AddPhysicsObject(CGameObject* _GameObject);
    void RemovePhysicsObject(CGameObject* _GameObject);

    friend class CTaskMgr;
    friend class CRigidbody2D;
};
