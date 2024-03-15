#pragma once

enum class TASK_TYPE
{
    // Param1 : Layer Index, Param2 : Object Address
    CREATE_OBJECT,

    // Param1 : Object Address
    DELETE_OBJECT,

    // Param1 : Level Address
    CHANGE_LEVEL,

    // Param1 : Level, Param2 : LEVEL_STATE
    CHANGE_LEVELSTATE,

    // Param1 : Parent Object, Param2 : Child Object
    ADD_CHILD,

    // Param1 : Width , Param2 : Height
    WINDOW_RESIZE,

    // Param1 : Asset_TYPE, Param2 : Asset Address
    DELETE_ASSET,

    // No Param
    SCREENSHOT,

    // Param1 : MouseX , Param2 : MouseY
    MOUSE_COLOR_PICKING,

    // Param1 : MouseX , Param2 : MouseY
    MOUSE_RAY_PICKING,

    // Param1 : MouseX , Param2 : MouseY
    MOUSE_COLLISION2D_PICKING,

    // Param1 : Object, Param2 : COMPONENT_TYPE
    ADD_COMPONENT,

    // Param1 : Object, Param2 : COMPONENT_TYPE
    REMOVE_COMPONENT,

    // Param1 : Object, Param2 : Script Address
    REMOVE_SCRIPT,

    // Param1 : Object, Param2 : Layer Index
    CHANGE_LAYER,

    // Param1 : Object
    CLONE_OBJECT,

    // Param1 : Object, Param2 : Event Type - 0 : Add, 1 : Remove, 2 : Regenerate
    PHYSICS2D_EVNET
};

struct tTask
{
    TASK_TYPE Type;
    UINT_PTR Param_1;
    UINT_PTR Param_2;
};

class CTaskMgr : public CSingleton<CTaskMgr>
{
    SINGLE(CTaskMgr);

private:
    vector<tTask> m_vecTask;

public:
    void tick();

    void AddTask(const tTask& _Task) { m_vecTask.push_back(_Task); }

private:
    void CREATE_OBJECT(const tTask& _Task);
    void DELETE_OBJECT(const tTask& _Task);
    void CHANGE_LEVEL(const tTask& _Task);
    void CHANGE_LEVELSTATE(const tTask& _Task);
    void ADD_CHILD(const tTask& _Task);
    void WINDOW_RESIZE(const tTask& _Task);
    void DELETE_ASSET(const tTask& _Task);
    void SCREENSHOT(const tTask& _Task);
    void MOUSE_COLOR_PICKING(const tTask& _Task);
    void MOUSE_RAY_PICKING(const tTask& _Task);
    void MOUSE_COLLISION2D_PICKING(const tTask& _Task);
    void ADD_COMPONENT(const tTask& _Task);
    void REMOVE_COMPONENT(const tTask& _Task);
    void REMOVE_SCRIPT(const tTask& _Task);
    void CHANGE_LAYER(const tTask& _Task);
    void CLONE_OBJECT(const tTask& _Task);
    void PHYSICS2D_EVNET(const tTask& _Task);
};
