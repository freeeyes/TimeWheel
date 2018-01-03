// TimeWheel.cpp : 定义控制台应用程序的入口点。
//

#include "TimeWheelLink.h"

bool g_IsClear = false;

//对象指针
class CEntey
{
public:
    CEntey()
    {
    };

    ~CEntey()
    {
    }
};

void TimeWheel_Timeout_Callback(vector<CEntey*> vecEntey)
{
    for (int i = 0; i < (int)vecEntey.size(); i++)
    {
        OUR_DEBUG((LM_INFO, "[TimeWheel_Timeout_Callback](%016x) is clear.\n", vecEntey[i]));
        g_IsClear = true;
    }
}

int ACE_TMAIN(int argc, ACE_TCHAR* argv[])
{
    CTimeWheelLink<CEntey> objTimeWheelLink;

    objTimeWheelLink.Init(3, 1, 2, TimeWheel_Timeout_Callback);

    CEntey objEntey1;
    CEntey objEntey2;

    objTimeWheelLink.Add_TimeWheel_Entey(&objEntey1);
    objTimeWheelLink.Add_TimeWheel_Entey(&objEntey2);

    ACE_Time_Value ttSleep(1, 0);

    while (true)
    {
        ACE_OS::sleep(ttSleep);

        objTimeWheelLink.Add_TimeWheel_Entey(&objEntey1);

        objTimeWheelLink.Tick();
    }

    return 0;
}

