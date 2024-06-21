#include "pch.h"

#include "CAnimator.h"

#include "CTimeMgr.h"
#include "CMeshRender.h"
#include "CStructuredBuffer.h"
#include "CAssetMgr.h"
#include "CAnimationUpdateShader.h"
#include "CKeyMgr.h"

CAnimator::CAnimator()
    : CComponent(COMPONENT_TYPE::ANIMATOR)
    , m_SkeletalMesh(nullptr)
    , m_CurClipIdx(0)
    , m_vecClipUpdateTime{}
    , m_bPlay(true)
    , m_bRepeat(true)
    , m_PlaySpeed(1.f)
    , m_FrameRate(30)
    , m_CurTime(0.)
    , m_FrameIdx(0)
    , m_NextFrameIdx(0)
    , m_Ratio(0.f)
    , m_BoneFinalMatBuffer(nullptr)
    , m_bFinalMatUpdate(false)
{
    m_BoneFinalMatBuffer = new CStructuredBuffer;
}

CAnimator::CAnimator(const CAnimator& _origin)
    : CComponent(_origin)
    , m_SkeletalMesh(_origin.m_SkeletalMesh)
    , m_CurClipIdx(_origin.m_CurClipIdx)
    , m_vecClipUpdateTime(_origin.m_vecClipUpdateTime)
    , m_bPlay(_origin.m_bPlay)
    , m_bRepeat(_origin.m_bRepeat)
    , m_PlaySpeed(_origin.m_PlaySpeed)
    , m_FrameRate(_origin.m_FrameRate)
    , m_CurTime(_origin.m_CurTime)
    , m_FrameIdx(_origin.m_FrameIdx)
    , m_NextFrameIdx(_origin.m_NextFrameIdx)
    , m_Ratio(_origin.m_Ratio)
    , m_BoneFinalMatBuffer(nullptr)
    , m_bFinalMatUpdate(false)
{
    m_BoneFinalMatBuffer = new CStructuredBuffer;
}

CAnimator::~CAnimator()
{
    if (nullptr != m_BoneFinalMatBuffer)
    {
        delete m_BoneFinalMatBuffer;
        m_BoneFinalMatBuffer = nullptr;
    }
}

void CAnimator::finaltick()
{
    if (nullptr == m_SkeletalMesh)
    {
        // SkeletalMesh 가 존재하지 않는 경우 Mesh Render의 Mesh로 설정
        CheckSkeletalMesh();
        return;
    }

    // 현재 재생중인 Clip 의 시간을 진행한다.
    if (m_bPlay)
    {
        m_vecClipUpdateTime[m_CurClipIdx] += DT * m_PlaySpeed;
    }

    if (m_vecClipUpdateTime[m_CurClipIdx] >= m_SkeletalMesh->GetAnimClip()->at(m_CurClipIdx).dTimeLength)
    {
        // 반복 재생
        if (m_bRepeat)
        {
            m_vecClipUpdateTime[m_CurClipIdx] = 0.f;
        }
        else
        {
            m_vecClipUpdateTime[m_CurClipIdx] = (float)m_SkeletalMesh->GetAnimClip()->at(m_CurClipIdx).dTimeLength;
        }
    }

    m_CurTime = m_SkeletalMesh->GetAnimClip()->at(m_CurClipIdx).dStartTime + m_vecClipUpdateTime[m_CurClipIdx];

    // 현재 프레임 인덱스 구하기
    double dFrameIdx = m_CurTime * m_FrameRate;
    m_FrameIdx = (int)(dFrameIdx);

    // 다음 프레임 인덱스
    if (m_FrameIdx >= m_SkeletalMesh->GetAnimClip()->at(m_CurClipIdx).iEndFrame)
        m_NextFrameIdx = m_FrameIdx; // 끝이면 현재 인덱스를 유지
    else
        m_NextFrameIdx = m_FrameIdx + 1;

    // 프레임간의 시간에 따른 비율을 구해준다.
    m_Ratio = (float)(dFrameIdx - (double)m_FrameIdx);

    // 컴퓨트 쉐이더 연산여부
    m_bFinalMatUpdate = false;
}

void CAnimator::UpdateData()
{
    if (nullptr == m_SkeletalMesh)
    {
        // SkeletalMesh 가 존재하지 않는 경우 Mesh Render의 Mesh로 설정
        CheckSkeletalMesh();
        return;
    }

    if (!m_bFinalMatUpdate)
    {
        // Animation Update Compute Shader
        static CAnimationUpdateShader* pUpdateShader =
            (CAnimationUpdateShader*)CAssetMgr::GetInst()->FindAsset<CComputeShader>(L"AnimationUpdateCS").Get();

        // Bone Data
        CheckBoneFinalMatBuffer();

        pUpdateShader->SetFrameDataBuffer(m_SkeletalMesh->GetBoneFrameDataBuffer());
        pUpdateShader->SetOffsetMatBuffer(m_SkeletalMesh->GetBoneOffsetBuffer());
        pUpdateShader->SetOutputBuffer(m_BoneFinalMatBuffer);

        pUpdateShader->SetBoneCount(m_SkeletalMesh->GetBoneCount());
        pUpdateShader->SetFrameIndex(m_FrameIdx);
        pUpdateShader->SetNextFrameIdx(m_NextFrameIdx);
        pUpdateShader->SetFrameRatio(m_Ratio);

        // 업데이트 쉐이더 실행
        pUpdateShader->Execute();

        m_bFinalMatUpdate = true;
    }

    // t31 레지스터에 최종행렬 데이터(구조버퍼) 바인딩
    m_BoneFinalMatBuffer->UpdateData(31);
}

void CAnimator::SetSkeletalMesh(Ptr<CMesh> _SkeletalMesh)
{
    if (nullptr == _SkeletalMesh)
        return;

    m_SkeletalMesh = _SkeletalMesh;

    const vector<tMTAnimClip>* vecAnimClip = m_SkeletalMesh->GetAnimClip();

    m_vecClipUpdateTime.resize(vecAnimClip->size());

    // Frame Rate 설정
    if (!vecAnimClip->empty())
    {
        m_FrameRate = FbxTime::GetFrameRate(vecAnimClip->back().eMode);
    }
}

void CAnimator::SetFrameIdx(int _FrameIdx)
{
    float FrameRate = float(m_SkeletalMesh->GetAnimClip()->at(m_CurClipIdx).iEndFrame - _FrameIdx) /
                      (float)m_SkeletalMesh->GetAnimClip()->at(m_CurClipIdx).iFrameLength;

    FrameRate = (1.f - FrameRate);
    if (FrameRate >= 1.f)
    {
        FrameRate = 1.f;
    }

    m_vecClipUpdateTime[m_CurClipIdx] = FrameRate * (float)m_SkeletalMesh->GetAnimClip()->at(m_CurClipIdx).dTimeLength;
}

UINT CAnimator::GetBoneCount() const
{
    if (nullptr == m_SkeletalMesh)
        return 0;

    return m_SkeletalMesh->GetBoneCount();
}

void CAnimator::ClearData()
{
    m_BoneFinalMatBuffer->Clear(31);

    UINT iMtrlCount = MeshRender()->GetMtrlCount();
    Ptr<CMaterial> pMtrl = nullptr;
    for (UINT i = 0; i < iMtrlCount; ++i)
    {
        pMtrl = MeshRender()->GetSharedMaterial(i);
        if (nullptr == pMtrl)
            continue;

        pMtrl->SetAnim3D(false);
        pMtrl->SetBoneCount(0);
    }
}

void CAnimator::CheckSkeletalMesh()
{
    if (nullptr != MeshRender())
    {
        SetSkeletalMesh(MeshRender()->GetMesh());
    }
}

void CAnimator::CheckBoneFinalMatBuffer()
{
    if (nullptr == m_SkeletalMesh)
        return;

    UINT iBoneCount = m_SkeletalMesh->GetBoneCount();
    if (m_BoneFinalMatBuffer->GetElementCount() != iBoneCount)
    {
        m_BoneFinalMatBuffer->Create(sizeof(Matrix), iBoneCount, SB_TYPE::READ_WRITE, false, nullptr);
    }
}

void CAnimator::SaveToLevelFile(FILE* _File)
{
    SaveAssetRef(m_SkeletalMesh, _File);

    fwrite(&m_bPlay, 1, sizeof(bool), _File);
    fwrite(&m_bRepeat, 1, sizeof(bool), _File);
    fwrite(&m_PlaySpeed, 1, sizeof(float), _File);
}

void CAnimator::LoadFromLevelFile(FILE* _File)
{
    LoadAssetRef(m_SkeletalMesh, _File);
    SetSkeletalMesh(m_SkeletalMesh);

    fread(&m_bPlay, 1, sizeof(bool), _File);
    fread(&m_bRepeat, 1, sizeof(bool), _File);
    fread(&m_PlaySpeed, 1, sizeof(float), _File);
}
