#include "pch.h"
#include "CSkyBox.h"

#include "CTransform.h"

#include "CDevice.h"
#include "CAssetMgr.h"

CSkyBox::CSkyBox()
    : CRenderComponent(COMPONENT_TYPE::SKYBOX)
    , m_Shape(SKYBOX_SHAPE::BOX)
{
    SetShape(m_Shape);

    SetFrustumCheck(false);
    SetCastShadow(false);
}

CSkyBox::~CSkyBox()
{
    CTexture::Clear(17);
    CTexture::Clear(18);
    CTexture::Clear(19);
}

void CSkyBox::finaltick()
{
    if (GetOwner()->IsDead())
    {
        CTexture::Clear(17);
        CTexture::Clear(18);
        CTexture::Clear(19);
        return;
    }

    CRenderComponent::finaltick();
}

void CSkyBox::UpdateData()
{
    nullptr != m_BrdfTex ? m_BrdfTex->UpdateData(17) : CTexture::Clear(17);
    nullptr != m_DiffuseTex ? m_DiffuseTex->UpdateData(18) : CTexture::Clear(18);
    nullptr != m_SpecularTex ? m_SpecularTex->UpdateData(19) : CTexture::Clear(19);
}

void CSkyBox::render()
{
    if (nullptr == GetMesh() || nullptr == GetMaterial(0))
        return;

    if (GetOwner()->IsDead())
    {
        CTexture::Clear(17);
        CTexture::Clear(18);
        CTexture::Clear(19);
        return;
    }

    UpdateData();

    Transform()->UpdateData();

    GetMaterial(0)->SetScalarParam(INT_0, (int)m_Shape);

    if (SKYBOX_SHAPE::SPHERE == m_Shape)
    {
        GetMaterial(0)->SetTexParam(TEX_0, m_EnvTex);
    }
    else
    {
        GetMaterial(0)->SetTexParam(TEXCUBE_0, m_EnvTex);
    }

    GetMaterial(0)->UpdateData();

    GetMesh()->render(0);
}

void CSkyBox::render(Ptr<CMaterial> _mtrl)
{
    if (nullptr == GetMesh() || nullptr == _mtrl)
        return;

    Transform()->UpdateData();

    _mtrl->SetScalarParam(INT_0, (int)m_Shape);

    if (SKYBOX_SHAPE::SPHERE == m_Shape)
    {
        _mtrl->SetTexParam(TEX_0, m_EnvTex);
    }
    else
    {
        _mtrl->SetTexParam(TEXCUBE_0, m_EnvTex);
    }

    _mtrl->UpdateData();

    GetMesh()->render(0);
}

void CSkyBox::render(UINT _Subset)
{
    render();
}

void CSkyBox::SetShape(SKYBOX_SHAPE _Shape)
{
    m_Shape = _Shape;

    if (SKYBOX_SHAPE::SPHERE == _Shape)
    {
        SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"SphereMesh"));
    }

    else if (SKYBOX_SHAPE::BOX == _Shape)
    {
        SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"BoxMesh"));
    }

    SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"SkyBoxMtrl"), 0);
    // SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"SkyBoxMtrl_V2"), 0);
}

void CSkyBox::SaveToLevelFile(FILE* _File)
{
    CRenderComponent::SaveToLevelFile(_File);

    fwrite(&m_Shape, sizeof(SKYBOX_SHAPE), 1, _File);
    SaveAssetRef(m_EnvTex, _File);
    SaveAssetRef(m_BrdfTex, _File);
    SaveAssetRef(m_DiffuseTex, _File);
    SaveAssetRef(m_SpecularTex, _File);
}

void CSkyBox::LoadFromLevelFile(FILE* _File)
{
    CRenderComponent::LoadFromLevelFile(_File);

    fread(&m_Shape, sizeof(SKYBOX_SHAPE), 1, _File);
    LoadAssetRef(m_EnvTex, _File);
    LoadAssetRef(m_BrdfTex, _File);
    LoadAssetRef(m_DiffuseTex, _File);
    LoadAssetRef(m_SpecularTex, _File);

    SetShape(m_Shape);
}
