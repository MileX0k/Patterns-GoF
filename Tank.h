#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"
#include "MessageBoxMediator.h"

class Tank : public DestroyableGroundObject
{
public:

	Tank(MessageBoxMediator* messageBox) : MessageBoxed{ messageBox } {}

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

private:

	const uint16_t score = 30;

	MessageBoxMediator* MessageBoxed;
};

