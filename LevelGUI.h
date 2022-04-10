#pragma once

#include <stdint.h>

#include "GameObject.h"
#include<vector>
#include<string_view>

class LevelGUI : public GameObject {
public:

    LevelGUI() : bombsNumber(0), score(0), passedTime(0), fps(0), height(0) { }

    void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
    
    void __fastcall SetHeight(uint16_t heightN) { height = heightN; };
    
    inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() const override;

    void DisplayMessage(uint16_t x, uint16_t y, float duration, std::string_view message);

private:

    uint16_t height;
    uint16_t finishX = 109;

    uint64_t passedTime, fps;
    uint16_t bombsNumber;
    int16_t score;

    struct Message
    {
        float lifeLeft;
        std::string text;
        uint16_t x, y;
    };

    std::vector<Message> messages;
};



