#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

    virtual void Accept(LogVisitor const& v) const {
        v.Log(*this);
    }

private:

};

