#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

//================================================================================

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;

    virtual void next() = 0;
    virtual T get() const = 0;
};

class BombIterator : public Iterator<Bomb*> {
public:

    BombIterator(std::vector<DynamicObject*>::iterator const& obj_it)
        : vec_bombs{ obj_it }   {
        if (get() == nullptr)
            next();
    }

    void next() override {
        while (dynamic_cast<Bomb*>(*vec_bombs) != nullptr) {
            vec_bombs++;
        }
    }

    Bomb* get() const override {
        return dynamic_cast<Bomb*>(*vec_bombs);
    }

private:
    std::vector<DynamicObject*>::iterator vec_bombs;
};
//=====================================================================

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    BombIterator FindAllBombs();

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};