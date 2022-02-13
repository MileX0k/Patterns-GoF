#pragma once

#include "MyTools.h"
#include "Bomb.h"
#include "Plane.h"
#include "SBomber.h"
#include "SLevel.h"


class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual void Execute() = 0;
};

class DropBombCmd : public ICommand {
public:
    DropBombCmd(SLevel* level) : level{ level } {}

	virtual void Execute() override {
        if (level->getBombsNumber() > 0)
        {
            MyTools::FileLoggerSingletone::getInstance().WriteToLog(std::string(__FUNCTION__) + " was invoked");

            Plane* pPlane = level->FindPlane();
            double x = pPlane->GetX() + 4;
            double y = pPlane->GetY() + 2;

            Bomb* pBomb = new Bomb;
            pBomb->SetDirection(0.3, 1);
            pBomb->SetSpeed(2);
            pBomb->SetPos(x, y);
            pBomb->SetWidth(SMALL_CRATER_SIZE);

            level->addDynamic(pBomb);
            level->decreaseBombNumber();
            level->modifyScore(-Bomb::BombCost);
        }

	}
private:
    SLevel* level;
};

class DeleteStaticObjCmd : public ICommand {
public:
    DeleteStaticObjCmd(GameObject* obj, SLevel* level) : obj{ obj },  level { level } {}

    virtual void Execute() override {
        level->removeStatic(obj);
    }

private:
    GameObject* obj;
    SLevel* level;
};

class DeleteDynamicObjCmd : public ICommand {
public:
    DeleteDynamicObjCmd(DynamicObject* obj, SLevel* level) : obj{ obj }, level{ level } {}

    virtual void Execute() override {
        level->removeDynamic(obj);
    }

private:
    DynamicObject* obj;
    SLevel* level;
};
