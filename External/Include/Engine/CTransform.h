#pragma once
#include "CComponent.h"

class CTransform : public CComponent
{
private:
    Vec3 m_vRelativePos;
    Vec3 m_vRelativeScale;
    Vec3 m_vRelativeRotation;

    Vec3 m_arrLocalDir[3]; // Right, Up, Front
    Vec3 m_arrWorldDir[3]; // Right, Up, Front

    Matrix m_matWorld;
    bool m_bAbsolute;

    Matrix m_matParentMat;

private:
    BoundingSphere m_BoundingSphere;

public:
    virtual void finaltick() override;
    virtual void UpdateData() override;

public:
    void SetRelativePos(Vec3 _Pos) { m_vRelativePos = _Pos; }
    void SetRelativeScale(Vec3 _Scale) { m_vRelativeScale = _Scale; }
    void SetRelativeRotation(Vec3 _Rotation) { m_vRelativeRotation = _Rotation; }

    Vec3 GetRelativePos() const { return m_vRelativePos; }
    Vec3 GetRelativeScale() const { return m_vRelativeScale; }
    Vec3 GetRelativeRotation() const { return m_vRelativeRotation; }

    bool IsAbsolute() const { return m_bAbsolute; }
    void SetAbsolute(bool _bAbsolute) { m_bAbsolute = _bAbsolute; }

    const Matrix& GetWorldMat() const { return m_matWorld; }
    void SetWorldMat(const Matrix _matWorld) { m_matWorld = _matWorld; }

    Vec3 GetLocalDir(DIR_TYPE _type) { return m_arrLocalDir[(UINT)_type]; }
    Vec3 GetWorldDir(DIR_TYPE _type) { return m_arrWorldDir[(UINT)_type]; }

public:
    Vec3 GetWorldPos() const { return Vec3(m_matWorld._41, m_matWorld._42, m_matWorld._43); }
    const Matrix& GetParentMat() const { return m_matParentMat; }

    const BoundingSphere& GetBoundingSphere() const { return m_BoundingSphere; }
public:
    CTransform();
    virtual ~CTransform();
};
