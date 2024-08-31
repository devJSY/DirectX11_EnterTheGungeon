#include "pch.h"
#include "CMorphoAtkA_DoubleSwordAtkR.h"
#include "CMorphoFSM.h"
#include "CPlayerMgr.h"
#include "CCameraController.h"
#include "CChangeAlphaScript.h"
#include "CDestroyParticleScript.h"

CMorphoAtkA_DoubleSwordAtkR::CMorphoAtkA_DoubleSwordAtkR()
    : m_LightningEffect(nullptr)
    , m_bFrmEnter(true)
{
    m_LightningEffectPref = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\Effect_MorphoLightningSet.pref", L"prefab\\Effect_MorphoLightningSet.pref");
}

CMorphoAtkA_DoubleSwordAtkR::~CMorphoAtkA_DoubleSwordAtkR()
{
}

void CMorphoAtkA_DoubleSwordAtkR::tick()
{
    switch (m_Step)
    {
    case StateStep::Start: {
        Start();
    }
    break;
    case StateStep::Progress: {
        Progress();
    }
    break;
    case StateStep::End: {
        End();
    }
    break;
    }
}

void CMorphoAtkA_DoubleSwordAtkR::Exit()
{
    Exit_Step();
    MRPFSM->OffWeaponRTrigger();
}

void CMorphoAtkA_DoubleSwordAtkR::Enter_Step()
{
    switch (m_Step)
    {
    case StateStep::Start: {
        GetOwner()->Animator()->Play(ANIMPREFIX("DoubleSwordAttack1Start"), false, false, 1.5f);
        MRPFSM->OnWeaponRTrigger();
        //@EFFECT ��¡����Ʈ
    }
    break;
    case StateStep::Progress: {
        GetOwner()->Animator()->Play(ANIMPREFIX("DoubleSwordAttack1"), false, false, 1.5f);
        m_bFrmEnter = true;
    }
    break;
    case StateStep::End: {
        GetOwner()->Animator()->Play(ANIMPREFIX("DoubleSwordAttack1End"), false, false, 1.5f);
        m_bFrmEnter = true;
    }
    break;
    }
}

void CMorphoAtkA_DoubleSwordAtkR::Exit_Step()
{
    switch (m_Step)
    {
    case StateStep::Start:
        break;
    case StateStep::Progress:
    break;
    case StateStep::End: {
        m_LightningEffect = nullptr;
    }
    break;
    }
}

void CMorphoAtkA_DoubleSwordAtkR::Start()
{
    RotateToPlayer(DT);

    if (GetOwner()->Animator()->IsFinish())
    {
        ChangeStep(StateStep::Progress);
    }
}

void CMorphoAtkA_DoubleSwordAtkR::Progress()
{
    // Spawn Effect
    if (m_bFrmEnter && CHECK_ANIMFRM(GetOwner(), 30))
    {
        m_bFrmEnter = false;

        if (m_LightningEffectPref != nullptr)
        {
            m_LightningEffect = m_LightningEffectPref->Instantiate();
            Vec3 Pos = MRPFSM->GetWeaponR()->GetChildObject()[0]->Transform()->GetWorldPos();
            Pos.y = 0.f;
            Vec3 Dir = CPlayerMgr::GetCameraController()->GetLookDir() * -1.f;
            Dir.y = 0.f;

            m_LightningEffect->Transform()->SetWorldPos(Pos);
            m_LightningEffect->Transform()->Slerp(Dir.Normalize(), 1.f);

            CChangeAlphaScript* Script = m_LightningEffect->GetScript<CChangeAlphaScript>();
            Script->FadeIn_RandomDelay(0.f, 0.4f);

            GamePlayStatic::SpawnGameObject(m_LightningEffect, LAYER_EFFECT);
            SpawnCircleDust(Pos);
        }

        CAMERACTRL->Shake(0.3f, 30.f, 30.f);

        // Spawn DropStar & Particle Butterfly
        Vec3 SpawnPos = MRPFSM->GetWeaponR()->Transform()->GetWorldPos();
        Vec3 FrontDir = MRPFSM->GetWeaponR()->Transform()->GetWorldDir(DIR_TYPE::FRONT);
        Vec3 RightDir = MRPFSM->GetWeaponR()->Transform()->GetWorldDir(DIR_TYPE::UP);
        FrontDir.y = RightDir.y = 0.f;
        FrontDir.y = 0.f;
        FrontDir.Normalize();
        RightDir.Normalize();

        for (int i = 0; i < 3; ++i)
        {
            Vec3 OffsetSpawnPos = SpawnPos;
            OffsetSpawnPos += RightDir * 20.f;
            OffsetSpawnPos += FrontDir * (100.f * i);

            SpawnButterfly(OffsetSpawnPos);
            MRPFSM->SpawnDropStar(OffsetSpawnPos);
        }

        for (int i = 0; i < 3; ++i)
        {
            Vec3 OffsetSpawnPos = SpawnPos;
            OffsetSpawnPos -= RightDir * 20.f;
            OffsetSpawnPos += FrontDir * (50.f + 100.f * i);

            SpawnButterfly(OffsetSpawnPos);
            MRPFSM->SpawnDropStar(OffsetSpawnPos);
        }
    }

    if (GetOwner()->Animator()->IsFinish())
    {
        ChangeStep(StateStep::End);
    }
}

void CMorphoAtkA_DoubleSwordAtkR::End()
{
    // ����Ʈ ����
    if (m_bFrmEnter && CHECK_ANIMFRM(GetOwner(), 15))
    {
        m_bFrmEnter = false;

        if (m_LightningEffect)
        {
            CChangeAlphaScript* Script = m_LightningEffect->GetScript<CChangeAlphaScript>();
            Script->FadeOutDestroy(1.f);
        }
    }

    if (GetOwner()->Animator()->IsFinish())
    {
        MRPFSM->ProcPatternStep();
    }
}

void CMorphoAtkA_DoubleSwordAtkR::SpawnButterfly(Vec3 _Pos)
{
    CGameObject* Butterfly = new CGameObject;
    CParticleSystem* Particle = nullptr;
    int Rand = GetRandomInt(0, 2);

    if (Rand == 0)
    {
        Particle = MRPFSM->GetParticleButterflyPink()->ParticleSystem()->Clone();
    }
    else if (Rand == 1)
    {
        Particle = MRPFSM->GetParticleButterflyYellow()->ParticleSystem()->Clone();
    }
    else if (Rand == 2)
    {
        Particle = MRPFSM->GetParticleButterflyYellowPink()->ParticleSystem()->Clone();
    }

    if (Particle)
    {
        tParticleModule Module = Particle->GetParticleModule();
        Module.vSpawnMinScale = Vec3(20.f, 20.f, 1.f);
        Module.vSpawnMaxScale = Vec3(40.f, 40.f, 1.f);
        Module.vScaleRatio = Vec3::Zero;
        Module.MinSpeed = 30.f;
        Module.MaxSpeed = 80.f;
        Module.VelocityAlignment = GetRandomInt(0, 1);
        Module.AlphaBasedLife = 1;

        Particle->SetParticleModule(Module);
        Butterfly->AddComponent(Particle);
    }

    _Pos.y = GetRandomfloat(0.f, 50.f);
    Butterfly->AddComponent(new CTransform);
    Butterfly->Transform()->SetWorldPos(_Pos);

    CDestroyParticleScript* Script = new CDestroyParticleScript;
    Script->SetSpawnTime(0.5f);
    Butterfly->AddComponent(Script);

    Butterfly->SetName(L"Particle_Butterfly");
    GamePlayStatic::SpawnGameObject(Butterfly, LAYER_EFFECT);
}

void CMorphoAtkA_DoubleSwordAtkR::SpawnCircleDust(Vec3 _Pos)
{
    CGameObject* Dust = new CGameObject;
    CParticleSystem* Particle = MRPFSM->GetParticleCircleDust()->ParticleSystem()->Clone();
    Dust->AddComponent(Particle);

    _Pos.y = GetRandomfloat(0.f, 10.f);
    Dust->AddComponent(new CTransform);
    Dust->Transform()->SetWorldPos(_Pos);

    CDestroyParticleScript* Script = new CDestroyParticleScript;
    Script->SetSpawnTime(0.5f);
    Dust->AddComponent(Script);

    Dust->SetName(L"Particle_CircleDust");
    GamePlayStatic::SpawnGameObject(Dust, LAYER_EFFECT);
}
