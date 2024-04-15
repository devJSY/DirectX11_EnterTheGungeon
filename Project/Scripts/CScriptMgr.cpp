#include "pch.h"
#include "CScriptMgr.h"

#include "CBridgeScript.h"
#include "CCameraMoveScript.h"
#include "CCinematicScript.h"
#include "CEnemyDamageLifeBarScript.h"
#include "CEnemyHitBoxScript.h"
#include "CEnemyLifeBarScript.h"
#include "CEntetElevatorScript.h"
#include "CEvilPumpkinBombScript.h"
#include "CEvilPumpkinScript.h"
#include "CExitElevatorScript.h"
#include "CFlyingBookScript.h"
#include "CFXScript.h"
#include "CGameManagerScript.h"
#include "CGhostScript.h"
#include "CHallofEternity_Floor1_CinematicScript.h"
#include "CLevelChangeScript.h"
#include "CLifeScript.h"
#include "CPhysics2DScript.h"
#include "CPlayButtonScript.h"
#include "CPlayerCameraScript.h"
#include "CPlayerDamageLifeBarScript.h"
#include "CPlayerDetectScript.h"
#include "CPlayerHitBoxScript.h"
#include "CPlayerLifeBarScript.h"
#include "CPlayerLifeTextScript.h"
#include "CPlayerManaBarScript.h"
#include "CPlayerManaTextScript.h"
#include "CPlayerScript.h"
#include "CPlayerSkillScript.h"
#include "CProjectile2DScript.h"
#include "CPyroGhostScript.h"
#include "CSkeletonHandScript.h"
#include "CSoundManagerScript.h"
#include "CSpooksmenScript.h"
#include "CW9_Boss_CinematicScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBridgeScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCinematicScript");
	_vec.push_back(L"CEnemyDamageLifeBarScript");
	_vec.push_back(L"CEnemyHitBoxScript");
	_vec.push_back(L"CEnemyLifeBarScript");
	_vec.push_back(L"CEntetElevatorScript");
	_vec.push_back(L"CEvilPumpkinBombScript");
	_vec.push_back(L"CEvilPumpkinScript");
	_vec.push_back(L"CExitElevatorScript");
	_vec.push_back(L"CFlyingBookScript");
	_vec.push_back(L"CFXScript");
	_vec.push_back(L"CGameManagerScript");
	_vec.push_back(L"CGhostScript");
	_vec.push_back(L"CHallofEternity_Floor1_CinematicScript");
	_vec.push_back(L"CLevelChangeScript");
	_vec.push_back(L"CLifeScript");
	_vec.push_back(L"CPhysics2DScript");
	_vec.push_back(L"CPlayButtonScript");
	_vec.push_back(L"CPlayerCameraScript");
	_vec.push_back(L"CPlayerDamageLifeBarScript");
	_vec.push_back(L"CPlayerDetectScript");
	_vec.push_back(L"CPlayerHitBoxScript");
	_vec.push_back(L"CPlayerLifeBarScript");
	_vec.push_back(L"CPlayerLifeTextScript");
	_vec.push_back(L"CPlayerManaBarScript");
	_vec.push_back(L"CPlayerManaTextScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPlayerSkillScript");
	_vec.push_back(L"CProjectile2DScript");
	_vec.push_back(L"CPyroGhostScript");
	_vec.push_back(L"CSkeletonHandScript");
	_vec.push_back(L"CSoundManagerScript");
	_vec.push_back(L"CSpooksmenScript");
	_vec.push_back(L"CW9_Boss_CinematicScript");
}

CScript* CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBridgeScript" == _strScriptName)
		return new CBridgeScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCinematicScript" == _strScriptName)
		return new CCinematicScript;
	if (L"CEnemyDamageLifeBarScript" == _strScriptName)
		return new CEnemyDamageLifeBarScript;
	if (L"CEnemyHitBoxScript" == _strScriptName)
		return new CEnemyHitBoxScript;
	if (L"CEnemyLifeBarScript" == _strScriptName)
		return new CEnemyLifeBarScript;
	if (L"CEntetElevatorScript" == _strScriptName)
		return new CEntetElevatorScript;
	if (L"CEvilPumpkinBombScript" == _strScriptName)
		return new CEvilPumpkinBombScript;
	if (L"CEvilPumpkinScript" == _strScriptName)
		return new CEvilPumpkinScript;
	if (L"CExitElevatorScript" == _strScriptName)
		return new CExitElevatorScript;
	if (L"CFlyingBookScript" == _strScriptName)
		return new CFlyingBookScript;
	if (L"CFXScript" == _strScriptName)
		return new CFXScript;
	if (L"CGameManagerScript" == _strScriptName)
		return new CGameManagerScript;
	if (L"CGhostScript" == _strScriptName)
		return new CGhostScript;
	if (L"CHallofEternity_Floor1_CinematicScript" == _strScriptName)
		return new CHallofEternity_Floor1_CinematicScript;
	if (L"CLevelChangeScript" == _strScriptName)
		return new CLevelChangeScript;
	if (L"CLifeScript" == _strScriptName)
		return new CLifeScript;
	if (L"CPhysics2DScript" == _strScriptName)
		return new CPhysics2DScript;
	if (L"CPlayButtonScript" == _strScriptName)
		return new CPlayButtonScript;
	if (L"CPlayerCameraScript" == _strScriptName)
		return new CPlayerCameraScript;
	if (L"CPlayerDamageLifeBarScript" == _strScriptName)
		return new CPlayerDamageLifeBarScript;
	if (L"CPlayerDetectScript" == _strScriptName)
		return new CPlayerDetectScript;
	if (L"CPlayerHitBoxScript" == _strScriptName)
		return new CPlayerHitBoxScript;
	if (L"CPlayerLifeBarScript" == _strScriptName)
		return new CPlayerLifeBarScript;
	if (L"CPlayerLifeTextScript" == _strScriptName)
		return new CPlayerLifeTextScript;
	if (L"CPlayerManaBarScript" == _strScriptName)
		return new CPlayerManaBarScript;
	if (L"CPlayerManaTextScript" == _strScriptName)
		return new CPlayerManaTextScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPlayerSkillScript" == _strScriptName)
		return new CPlayerSkillScript;
	if (L"CProjectile2DScript" == _strScriptName)
		return new CProjectile2DScript;
	if (L"CPyroGhostScript" == _strScriptName)
		return new CPyroGhostScript;
	if (L"CSkeletonHandScript" == _strScriptName)
		return new CSkeletonHandScript;
	if (L"CSoundManagerScript" == _strScriptName)
		return new CSoundManagerScript;
	if (L"CSpooksmenScript" == _strScriptName)
		return new CSpooksmenScript;
	if (L"CW9_Boss_CinematicScript" == _strScriptName)
		return new CW9_Boss_CinematicScript;
	return nullptr;
}

CScript* CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BRIDGESCRIPT:
		return new CBridgeScript;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
	case (UINT)SCRIPT_TYPE::CINEMATICSCRIPT:
		return new CCinematicScript;
	case (UINT)SCRIPT_TYPE::ENEMYDAMAGELIFEBARSCRIPT:
		return new CEnemyDamageLifeBarScript;
	case (UINT)SCRIPT_TYPE::ENEMYHITBOXSCRIPT:
		return new CEnemyHitBoxScript;
	case (UINT)SCRIPT_TYPE::ENEMYLIFEBARSCRIPT:
		return new CEnemyLifeBarScript;
	case (UINT)SCRIPT_TYPE::ENTETELEVATORSCRIPT:
		return new CEntetElevatorScript;
	case (UINT)SCRIPT_TYPE::EVILPUMPKINBOMBSCRIPT:
		return new CEvilPumpkinBombScript;
	case (UINT)SCRIPT_TYPE::EVILPUMPKINSCRIPT:
		return new CEvilPumpkinScript;
	case (UINT)SCRIPT_TYPE::EXITELEVATORSCRIPT:
		return new CExitElevatorScript;
	case (UINT)SCRIPT_TYPE::FLYINGBOOKSCRIPT:
		return new CFlyingBookScript;
	case (UINT)SCRIPT_TYPE::FXSCRIPT:
		return new CFXScript;
	case (UINT)SCRIPT_TYPE::GAMEMANAGERSCRIPT:
		return new CGameManagerScript;
	case (UINT)SCRIPT_TYPE::GHOSTSCRIPT:
		return new CGhostScript;
	case (UINT)SCRIPT_TYPE::HALLOFETERNITY_FLOOR1_CINEMATICSCRIPT:
		return new CHallofEternity_Floor1_CinematicScript;
	case (UINT)SCRIPT_TYPE::LEVELCHANGESCRIPT:
		return new CLevelChangeScript;
	case (UINT)SCRIPT_TYPE::LIFESCRIPT:
		return new CLifeScript;
	case (UINT)SCRIPT_TYPE::PHYSICS2DSCRIPT:
		return new CPhysics2DScript;
	case (UINT)SCRIPT_TYPE::PLAYBUTTONSCRIPT:
		return new CPlayButtonScript;
	case (UINT)SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return new CPlayerCameraScript;
	case (UINT)SCRIPT_TYPE::PLAYERDAMAGELIFEBARSCRIPT:
		return new CPlayerDamageLifeBarScript;
	case (UINT)SCRIPT_TYPE::PLAYERDETECTSCRIPT:
		return new CPlayerDetectScript;
	case (UINT)SCRIPT_TYPE::PLAYERHITBOXSCRIPT:
		return new CPlayerHitBoxScript;
	case (UINT)SCRIPT_TYPE::PLAYERLIFEBARSCRIPT:
		return new CPlayerLifeBarScript;
	case (UINT)SCRIPT_TYPE::PLAYERLIFETEXTSCRIPT:
		return new CPlayerLifeTextScript;
	case (UINT)SCRIPT_TYPE::PLAYERMANABARSCRIPT:
		return new CPlayerManaBarScript;
	case (UINT)SCRIPT_TYPE::PLAYERMANATEXTSCRIPT:
		return new CPlayerManaTextScript;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
	case (UINT)SCRIPT_TYPE::PLAYERSKILLSCRIPT:
		return new CPlayerSkillScript;
	case (UINT)SCRIPT_TYPE::PROJECTILE2DSCRIPT:
		return new CProjectile2DScript;
	case (UINT)SCRIPT_TYPE::PYROGHOSTSCRIPT:
		return new CPyroGhostScript;
	case (UINT)SCRIPT_TYPE::SKELETONHANDSCRIPT:
		return new CSkeletonHandScript;
	case (UINT)SCRIPT_TYPE::SOUNDMANAGERSCRIPT:
		return new CSoundManagerScript;
	case (UINT)SCRIPT_TYPE::SPOOKSMENSCRIPT:
		return new CSpooksmenScript;
	case (UINT)SCRIPT_TYPE::W9_BOSS_CINEMATICSCRIPT:
		return new CW9_Boss_CinematicScript;
	}
	return nullptr;
}

const wchar_t* CScriptMgr::GetScriptName(CScript* _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BRIDGESCRIPT:
		return L"CBridgeScript";
	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
	case SCRIPT_TYPE::CINEMATICSCRIPT:
		return L"CCinematicScript";
	case SCRIPT_TYPE::ENEMYDAMAGELIFEBARSCRIPT:
		return L"CEnemyDamageLifeBarScript";
	case SCRIPT_TYPE::ENEMYHITBOXSCRIPT:
		return L"CEnemyHitBoxScript";
	case SCRIPT_TYPE::ENEMYLIFEBARSCRIPT:
		return L"CEnemyLifeBarScript";
	case SCRIPT_TYPE::ENTETELEVATORSCRIPT:
		return L"CEntetElevatorScript";
	case SCRIPT_TYPE::EVILPUMPKINBOMBSCRIPT:
		return L"CEvilPumpkinBombScript";
	case SCRIPT_TYPE::EVILPUMPKINSCRIPT:
		return L"CEvilPumpkinScript";
	case SCRIPT_TYPE::EXITELEVATORSCRIPT:
		return L"CExitElevatorScript";
	case SCRIPT_TYPE::FLYINGBOOKSCRIPT:
		return L"CFlyingBookScript";
	case SCRIPT_TYPE::FXSCRIPT:
		return L"CFXScript";
	case SCRIPT_TYPE::GAMEMANAGERSCRIPT:
		return L"CGameManagerScript";
	case SCRIPT_TYPE::GHOSTSCRIPT:
		return L"CGhostScript";
	case SCRIPT_TYPE::HALLOFETERNITY_FLOOR1_CINEMATICSCRIPT:
		return L"CHallofEternity_Floor1_CinematicScript";
	case SCRIPT_TYPE::LEVELCHANGESCRIPT:
		return L"CLevelChangeScript";
	case SCRIPT_TYPE::LIFESCRIPT:
		return L"CLifeScript";
	case SCRIPT_TYPE::PHYSICS2DSCRIPT:
		return L"CPhysics2DScript";
	case SCRIPT_TYPE::PLAYBUTTONSCRIPT:
		return L"CPlayButtonScript";
	case SCRIPT_TYPE::PLAYERCAMERASCRIPT:
		return L"CPlayerCameraScript";
	case SCRIPT_TYPE::PLAYERDAMAGELIFEBARSCRIPT:
		return L"CPlayerDamageLifeBarScript";
	case SCRIPT_TYPE::PLAYERDETECTSCRIPT:
		return L"CPlayerDetectScript";
	case SCRIPT_TYPE::PLAYERHITBOXSCRIPT:
		return L"CPlayerHitBoxScript";
	case SCRIPT_TYPE::PLAYERLIFEBARSCRIPT:
		return L"CPlayerLifeBarScript";
	case SCRIPT_TYPE::PLAYERLIFETEXTSCRIPT:
		return L"CPlayerLifeTextScript";
	case SCRIPT_TYPE::PLAYERMANABARSCRIPT:
		return L"CPlayerManaBarScript";
	case SCRIPT_TYPE::PLAYERMANATEXTSCRIPT:
		return L"CPlayerManaTextScript";
	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
	case SCRIPT_TYPE::PLAYERSKILLSCRIPT:
		return L"CPlayerSkillScript";
	case SCRIPT_TYPE::PROJECTILE2DSCRIPT:
		return L"CProjectile2DScript";
	case SCRIPT_TYPE::PYROGHOSTSCRIPT:
		return L"CPyroGhostScript";
	case SCRIPT_TYPE::SKELETONHANDSCRIPT:
		return L"CSkeletonHandScript";
	case SCRIPT_TYPE::SOUNDMANAGERSCRIPT:
		return L"CSoundManagerScript";
	case SCRIPT_TYPE::SPOOKSMENSCRIPT:
		return L"CSpooksmenScript";
	case SCRIPT_TYPE::W9_BOSS_CINEMATICSCRIPT:
		return L"CW9_Boss_CinematicScript";
	}
	return nullptr;
}