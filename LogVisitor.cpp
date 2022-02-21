#include "LogVisitor.h"

#include "Bomb.h"
#include "Plane.h"


void LogVisitor::Log(const Bomb& bomb) const {
	MyTools::WriteToLog("The bomb is located: { x: " +
		std::to_string(bomb.GetX()) + ", y: " +
		std::to_string(bomb.GetY()) + " }\n");
}

void LogVisitor::Log(const Plane& plane) const {
	MyTools::WriteToLog("The plane is located: { x: " +
		std::to_string(plane.GetX()) + ", y: " +
		std::to_string(plane.GetY()) + " }");
}

