#include "pch.h"
#include "CPlayerScript.h"
#include <Engine\\CAnim.h>

CPlayerScript::CPlayerScript()
    : CScript(PLAYERSCRIPT)
    , m_State(PLAYER_STATE::Idle)
    , m_Dir(DIRECTION_TYPE::LEFT)
    , m_Speed(10.f)
    , m_Force(1.f)
{
    AddScriptParam(SCRIPT_PARAM::FLOAT, &m_Speed, "Speed");
    AddScriptParam(SCRIPT_PARAM::FLOAT, &m_Force, "Force");
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::begin()
{
    if (MeshRender())
        MeshRender()->CreateDynamicMaterial();

    if (Animator2D())
    {
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Acquisition.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Acquisition_Curse.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_AerialDownAttack.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_BookAttack_01.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_BookAttack_02.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_BookAttack_03.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_BossRitual_Intro.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Bump.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Combo_Stand.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboAerial_01.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboAerial_01_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboAerial_02.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboAerial_02_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboAerial_03.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboAerial_03_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboEvilHands.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboEvilHands_Up.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboKatana.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboKatanas_Ult.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboKatanas_Ult_Init.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboKatanas_Ult_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_01.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_01_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_02.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_02_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_03.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_03_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_04.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_04_Rest.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ComboMove_Jump.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Concentrate.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Concentrate_Start.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Dash.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Disappear.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Elevator_End.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Elevator_Enter.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Elevator_Out.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_EvilBirds.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_EvilBirds_Up.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Glide.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Hit.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Idle.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_IdleToRun.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_IdleUturn.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Jump_Falling.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Jump_Landing.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Jump_Start.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_JumpingAttack.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_OneWayDown.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_OneWayUp.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_PowerUp.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_PowerUp_01.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_PowerUp_02.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Ritual_End_Boss.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Run.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_RunToIdle.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_RunUturn.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Spawn_Lobby.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Teleport.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Waiting.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_Wallgrab_Idle.anim");
        Animator2D()->LoadAnimation(L"AnimData\\Player\\LD_ZipUp.anim");
    }

    ChangeState(PLAYER_STATE::Idle);
}

void CPlayerScript::tick()
{
    // Direction
    if (DIRECTION_TYPE::LEFT == m_Dir)
        Transform()->SetRelativeRotation(Vec3(0.f, XM_PI, 0.f));
    else
        Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));

    // FSM
    switch (m_State)
    {
    case PLAYER_STATE::Idle:
        Idle();
        break;
    case PLAYER_STATE::IdleToRun:
        IdleToRun();
        break;
    case PLAYER_STATE::IdleUturn:
        IdleUturn();
        break;
    case PLAYER_STATE::Jump_Falling:
        Jump_Falling();
        break;
    case PLAYER_STATE::Jump_Start:
        Jump_Start();
        break;
    case PLAYER_STATE::Jump_Landing:
        Jump_Landing();
        break;
    case PLAYER_STATE::Run:
        Run();
        break;
    case PLAYER_STATE::RunUturn:
        RunUturn();
        break;
    case PLAYER_STATE::RunToIdle:
        RunToIdle();
        break;
    case PLAYER_STATE::ComboMove:
        ComboMove();
        break;
    case PLAYER_STATE::ComboMove_Rest:
        ComboMove_Rest();
        break;
    case PLAYER_STATE::ComboAerial:
        ComboAerial();
        break;
    case PLAYER_STATE::ComboAerial_Rest:
        ComboAerial_Rest();
        break;
    case PLAYER_STATE::JumpingAttack:
        JumpingAttack();
        break;
    case PLAYER_STATE::AerialDownAttack:
        AerialDownAttack();
        break;
    case PLAYER_STATE::CapeAttack:
        CapeAttack();
        break;
    case PLAYER_STATE::Dash:
        Dash();
        break;
    case PLAYER_STATE::Hit:
        Hit();
        break;
    case PLAYER_STATE::EnterElavator:
        EnterElavator();
        break;
    case PLAYER_STATE::ExitElavator:
        ExitElavator();
        break;
    case PLAYER_STATE::Acquisition:
        Acquisition();
        break;
    case PLAYER_STATE::PowerUp:
        PowerUp();
        break;
    case PLAYER_STATE::UltAttack:
        UltAttack();
        break;
    case PLAYER_STATE::UltAttack_Rest:
        UltAttack_Rest();
        break;
    }

    // 테스트 코드
    if (KEY_TAP(KEY::T))
    {
        ChangeState(PLAYER_STATE::Idle);
    }
}

void CPlayerScript::ChangeState(PLAYER_STATE _NextState)
{
    ExitState();
    m_State = _NextState;
    EnterState();
}

void CPlayerScript::EnterState()
{
    switch (m_State)
    {
    case PLAYER_STATE::Idle: {
        Animator2D()->Play(L"LD_Idle");
    }
    break;
    case PLAYER_STATE::IdleToRun: {
        Animator2D()->Play(L"LD_IdleToRun");
    }
    break;
    case PLAYER_STATE::IdleUturn: {
        Animator2D()->Play(L"LD_IdleUturn");
    }
    break;
    case PLAYER_STATE::Jump_Falling: {
        Animator2D()->Play(L"LD_Jump_Falling");
    }
    break;
    case PLAYER_STATE::Jump_Start: {
        Rigidbody2D()->AddForce(Vec2(0.f, m_Force), ForceMode2D::Impulse);
        Animator2D()->Play(L"LD_Jump_Start", false);
    }
    break;
    case PLAYER_STATE::Jump_Landing: {
        Animator2D()->Play(L"LD_Jump_Landing", false);
    }
    break;
    case PLAYER_STATE::Run: {
        Animator2D()->Play(L"LD_Run");
    }
    break;
    case PLAYER_STATE::RunUturn: {
        Animator2D()->Play(L"LD_RunUturn", false);
    }
    break;
    case PLAYER_STATE::RunToIdle: {
        Animator2D()->Play(L"LD_RunToIdle", false);
    }
    break;
    case PLAYER_STATE::ComboMove: {
        Animator2D()->Play(L"LD_ComboMove", false);
    }
    break;
    case PLAYER_STATE::ComboMove_Rest: {
        Animator2D()->Play(L"LD_ComboMove_Rest", false);
    }
    break;
    case PLAYER_STATE::ComboAerial: {
        Animator2D()->Play(L"LD_ComboAerial", false);
    }
    break;
    case PLAYER_STATE::ComboAerial_Rest: {
        Animator2D()->Play(L"LD_ComboAerial_Rest", false);
    }
    break;
    case PLAYER_STATE::JumpingAttack: {
        Animator2D()->Play(L"LD_JumpingAttack", false);
    }
    break;
    case PLAYER_STATE::AerialDownAttack: {
        Animator2D()->Play(L"LD_AerialDownAttack", false);
    }
    break;
    case PLAYER_STATE::CapeAttack: {
    }
    break;
    case PLAYER_STATE::Dash: {
        Animator2D()->Play(L"LD_Dash", false);
    }
    break;
    case PLAYER_STATE::Hit: {
        Animator2D()->Play(L"LD_Hit", false);
    }
    break;
    case PLAYER_STATE::EnterElavator: {
        Animator2D()->Play(L"LD_EnterElavator", false);
    }
    break;
    case PLAYER_STATE::ExitElavator: {
        Animator2D()->Play(L"LD_ExitElavator", false);
    }
    break;
    case PLAYER_STATE::Acquisition: {
        Animator2D()->Play(L"LD_Acquisition", false);
    }
    break;
    case PLAYER_STATE::PowerUp: {
        Animator2D()->Play(L"LD_PowerUp", false);
    }
    break;
    case PLAYER_STATE::UltAttack: {
        Animator2D()->Play(L"LD_UltAttack", false);
    }
    break;
    case PLAYER_STATE::UltAttack_Rest: {
        Animator2D()->Play(L"LD_UltAttack_Rest", false);
    }
    break;
    }
}

void CPlayerScript::ExitState()
{
    switch (m_State)
    {
    case PLAYER_STATE::Idle: {
    }
    break;
    case PLAYER_STATE::IdleToRun: {
    }
    break;
    case PLAYER_STATE::IdleUturn: {
    }
    break;
    case PLAYER_STATE::Jump_Falling: {
    }
    break;
    case PLAYER_STATE::Jump_Start: {
    }
    break;
    case PLAYER_STATE::Jump_Landing: {
    }
    break;
    case PLAYER_STATE::Run: {
    }
    break;
    case PLAYER_STATE::RunUturn: {
    }
    break;
    case PLAYER_STATE::RunToIdle: {
    }
    break;
    case PLAYER_STATE::ComboMove: {
    }
    break;
    case PLAYER_STATE::ComboMove_Rest: {
    }
    break;
    case PLAYER_STATE::ComboAerial: {
    }
    break;
    case PLAYER_STATE::ComboAerial_Rest: {
    }
    break;
    case PLAYER_STATE::JumpingAttack: {
    }
    break;
    case PLAYER_STATE::AerialDownAttack: {
    }
    break;
    case PLAYER_STATE::CapeAttack: {
    }
    break;
    case PLAYER_STATE::Dash: {
    }
    break;
    case PLAYER_STATE::Hit: {
    }
    break;
    case PLAYER_STATE::EnterElavator: {
    }
    break;
    case PLAYER_STATE::ExitElavator: {
    }
    break;
    case PLAYER_STATE::Acquisition: {
    }
    break;
    case PLAYER_STATE::PowerUp: {
    }
    break;
    case PLAYER_STATE::UltAttack: {
    }
    break;
    case PLAYER_STATE::UltAttack_Rest: {
    }
    break;
    }
}

void CPlayerScript::Idle()
{
    if (KEY_TAP(KEY::A) || KEY_PRESSED(KEY::A))
    {
        ChangeState(PLAYER_STATE::IdleToRun);
        m_Dir = DIRECTION_TYPE::LEFT;
    }

    if (KEY_TAP(KEY::D) || KEY_PRESSED(KEY::D))
    {
        ChangeState(PLAYER_STATE::IdleToRun);
        m_Dir = DIRECTION_TYPE::RIGHT;
    }

    if (KEY_TAP(KEY::SPACE))
    {
        ChangeState(PLAYER_STATE::Jump_Start);
    }
}

void CPlayerScript::IdleToRun()
{
    if (Animator2D()->IsFinish())
    {
        if (KEY_PRESSED(KEY::A))
        {
            ChangeState(PLAYER_STATE::Run);
            m_Dir = DIRECTION_TYPE::LEFT;
        }
        else if (KEY_PRESSED(KEY::D))
        {
            ChangeState(PLAYER_STATE::Run);
            m_Dir = DIRECTION_TYPE::RIGHT;
        }
        else
        {
            ChangeState(PLAYER_STATE::Idle);
        }
    }

    // 이동
    Vec3 pos = Transform()->GetRelativePos();

    if (DIRECTION_TYPE::LEFT == m_Dir)
        pos.x -= m_Speed * DT;
    else
        pos.x += m_Speed * DT;

    Transform()->SetRelativePos(pos);
}

void CPlayerScript::IdleUturn()
{
}

void CPlayerScript::Jump_Falling()
{
}

void CPlayerScript::Jump_Start()
{
}

void CPlayerScript::Jump_Landing()
{
}

void CPlayerScript::Run()
{
    if (!(KEY_PRESSED(KEY::A) || KEY_PRESSED(KEY::D)))
    {
        ChangeState(PLAYER_STATE::RunToIdle);
    }

    // 이동
    Vec3 pos = Transform()->GetRelativePos();

    if (DIRECTION_TYPE::LEFT == m_Dir)
        pos.x -= m_Speed * DT;
    else
        pos.x += m_Speed * DT;

    Transform()->SetRelativePos(pos);
}

void CPlayerScript::RunUturn()
{
}

void CPlayerScript::RunToIdle()
{
    if (Animator2D()->IsFinish())
    {
        ChangeState(PLAYER_STATE::Idle);
    }
}

void CPlayerScript::ComboMove()
{
}

void CPlayerScript::ComboMove_Rest()
{
}

void CPlayerScript::ComboAerial()
{
}

void CPlayerScript::ComboAerial_Rest()
{
}

void CPlayerScript::JumpingAttack()
{
}

void CPlayerScript::AerialDownAttack()
{
}

void CPlayerScript::CapeAttack()
{
}

void CPlayerScript::Dash()
{
}

void CPlayerScript::Hit()
{
}

void CPlayerScript::EnterElavator()
{
}

void CPlayerScript::ExitElavator()
{
}

void CPlayerScript::Acquisition()
{
}

void CPlayerScript::PowerUp()
{
}

void CPlayerScript::UltAttack()
{
}

void CPlayerScript::UltAttack_Rest()
{
}

void CPlayerScript::OnCollisionEnter(CCollider2D* _OtherCollider)
{
}

void CPlayerScript::OnCollisionStay(CCollider2D* _OtherCollider)
{
}

void CPlayerScript::OnCollisionExit(CCollider2D* _OtherCollider)
{
}

void CPlayerScript::OnTriggerEnter(CCollider2D* _OtherCollider)
{
}

void CPlayerScript::OnTriggerStay(CCollider2D* _OtherCollider)
{
}

void CPlayerScript::OnTriggerExit(CCollider2D* _OtherCollider)
{
}

void CPlayerScript::SaveToLevelFile(FILE* _File)
{
    fwrite(&m_Speed, sizeof(float), 1, _File);
    fwrite(&m_Force, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
    fread(&m_Speed, sizeof(float), 1, _File);
    fread(&m_Force, sizeof(float), 1, _File);
}
