#pragma once

#include "MyTools.h"

class LogVisitor
{
public:
	void Log(class Bomb const& bomb) const;
	void Log(class Plane const& bomb) const;
};

