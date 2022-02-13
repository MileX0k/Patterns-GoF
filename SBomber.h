#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
//#include "SLevel.h"

class ICommand;
class SLevel;

class SBomber
{
public:

    SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    void ExecuteCommands();


private:
    void ScheduleCommand(ICommand* cmd);

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    void DropBomb();

    std::vector<ICommand*> pendingCommands;

    SLevel* level;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t deltaTime, fps;
};