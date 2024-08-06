#pragma once
#include "CState.h"

class CKirbyChangeAbility : public CState
{
private:
    float m_Acc;
    float m_Duration;

    bool m_bFrameEnter;

public:
    virtual void tick();
    virtual void Enter();
    virtual void Exit();

public:
    CLONE(CKirbyChangeAbility)
    CKirbyChangeAbility();
    virtual ~CKirbyChangeAbility();
};
