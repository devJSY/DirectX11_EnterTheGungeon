#pragma once

enum class TASK_TYPE
{
    // Param1 : Layer Index, Param2 : Object Adress
    CREATE_OBJECT,

    // Param1 : Object Adress
    DELETE_OBJECT,

    // Param1 : LEVEL_TYPE
    LEVEL_CHANGE,

    // Param1 : Parent Object, Param2 : Child Object
    ADD_CHILD,

    // Param1 : Parent Object, Param2 : Child Object
    DISCONNECT_PARENT,

    // Param1 : Width , Param2 : Height
    WINDOW_RESIZE,
    
    // wParam : Asset_TYPE, lParam : Resource Adress
	DELETE_ASSET, 

    // No Param
    SCREENSHOT,

    // Param1 : MouseX , Param2 : MouseY
    MOUSE_COLOR_PICKING,

    // Param1 : MouseX , Param2 : MouseY
    MOUSE_RAY_PICKING,
};

struct FTask
{
    TASK_TYPE Type;
    UINT_PTR Param_1;
    UINT_PTR Param_2;
};

class CTaskMgr : public CSingleton<CTaskMgr>
{
    SINGLE(CTaskMgr);

private:
    vector<FTask> m_vecTask;

public:
    void tick();

    void AddTask(const FTask& _Task) { m_vecTask.push_back(_Task); }
};
