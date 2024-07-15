#include "pch.h"
#include "CNormalEnemyFailedAttack.h"

CNormalEnemyFailedAttack::CNormalEnemyFailedAttack()
{
}

CNormalEnemyFailedAttack::~CNormalEnemyFailedAttack()
{
}

void CNormalEnemyFailedAttack::Enter()
{
    GetOwner()->GetComponent<CAnimator>()->Play(MONSTERANIM(L"Brake"),false);
}

void CNormalEnemyFailedAttack::tick()
{
    CAnimator* _anim = GetOwner()->GetComponent<CAnimator>();
    if (_anim->IsFinish() && _anim->FindClipIndex(MONSTERANIM(L"Brake")) == _anim->GetCurClipIdx())
    {
        GetOwner()->GetComponent<CAnimator>()->Play(MONSTERANIM(L"LookAround"),false);
    }

    if (_anim->IsFinish() && _anim->FindClipIndex(MONSTERANIM(L"LookAround")) == _anim->GetCurClipIdx())
    {
        ChangeState(L"IDLE");
    }
}

void CNormalEnemyFailedAttack::Exit()
{
}