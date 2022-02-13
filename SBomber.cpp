
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "ICommand.h"
#include "SLevel.h"


using namespace std;
using namespace MyTools;

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    level(new SLevel)

{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    level->addDynamic(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, level->getBombsNumber(), level->getScore());
    const uint16_t maxX = GetMaxX();
    const uint16_t maxY = GetMaxY(); 
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    level->addStatic(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    level->addStatic(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    level->addStatic(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    level->addStatic(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    level->addStatic(pHouse);
}

SLevel::~SLevel()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }
}

void SBomber::MoveObjects()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    level->forEachDynamic(
        [this](auto& obj) {
            obj.Move(deltaTime);
        }
    );
};

void SBomber::CheckObjects()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    if (level->FindPlane()->GetX() > level->FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround() 
{
    vector<Bomb*> vecBombs = level->FindAllBombs();
    Ground* pGround = level->FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            ScheduleCommand(new DeleteDynamicObjCmd{ vecBombs[i], level });
        }
    }

}

void SBomber::CheckDestoyableObjects(Bomb * pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = level->FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            level->modifyScore(vecDestoyableObjects[i]->GetScore()) ;
            ScheduleCommand(new DeleteStaticObjCmd{ vecDestoyableObjects[i], level });
        }
    }
}

vector<DestroyableGroundObject*> SLevel::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SLevel::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<Bomb*> SLevel::FindAllBombs() const
{
    vector<Bomb*> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane* SLevel::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SLevel::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);
    
    switch (c) {

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        level->FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        level->FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        ScheduleCommand(new DropBombCmd{ level });
        break;

    case 'B':
        ScheduleCommand(new DropBombCmd{ level });
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    
    level->forEachDynamic(
        [this](auto& obj) {
            obj.Draw();
        }
    );

    level->forEachStatic(
        [this](auto& obj) {
            obj.Draw();
        }
    );

    GotoXY(0, 0);
    fps++;

    level->FindLevelGUI()->SetParam(passedTime, fps, level->getBombsNumber(), level->getScore());
}

void SBomber::TimeStart()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::ScheduleCommand(ICommand* cmd) {
    pendingCommands.push_back(cmd);
}
void SBomber::ExecuteCommands() {
    for (auto* cmd : pendingCommands) {
        cmd->Execute();
        delete cmd;
    }
}
