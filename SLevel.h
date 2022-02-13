#pragma once
#include "SBomber.h"
#include <functional>

class SLevel
{
public:
    SLevel() = default;
    ~SLevel();

    Ground* FindGround() const;
    Plane* FindPlane() const;
    LevelGUI* FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    int16_t getScore() const {
        return score;
    }
    int16_t getBombsNumber() const {
        return bombsNumber;
    }

    void modifyScore(int16_t diff) {
        score += diff;
    }

    void decreaseBombNumber() {
        bombsNumber--;
    }

    void addStatic(GameObject* obj) {
        vecStaticObj.push_back(obj);
    }

    void addDynamic(DynamicObject* obj) {
        vecDynamicObj.push_back(obj);
    }

    void removeStatic(GameObject* obj) {
        auto it = vecStaticObj.begin();
        for (; it != vecStaticObj.end(); it++)
        {
            if (*it == obj)
            {
                vecStaticObj.erase(it);
                break;
            }
        }
    }

    void removeDynamic(DynamicObject* obj) {
        auto it = vecDynamicObj.begin();
        for (; it != vecDynamicObj.end(); it++)
        {
            if (*it == obj)
            {
                vecDynamicObj.erase(it);
                break;
            }
        }
    }


    void forEachStatic(std::function<void(GameObject&) > cb) {
        for (auto* obj : vecStaticObj) {
            if (obj != nullptr) {
                cb(*obj);
            }
        }
    }

    void forEachDynamic(std::function<void(DynamicObject&) > cb) {
        for (auto* obj : vecDynamicObj) {
            if (obj != nullptr) {
                cb(*obj);
            }
        }
    }


private:
    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    uint16_t bombsNumber = 10;
    int16_t score;
};

