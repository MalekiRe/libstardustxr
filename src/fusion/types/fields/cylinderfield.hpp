#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class CylinderField : public Field {
public:
	CylinderField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, float length, float radius);
};

class CylinderFieldBuilder {
private:
    Spatial *_parent = nullptr;
    SKMath::vec3 _origin;
    SKMath::quat _orientation;
    float _length;
    float _radius;
public:
    CylinderFieldBuilder parent(Spatial *parent);
    CylinderFieldBuilder origin(SKMath::vec3 origin);
    CylinderFieldBuilder orientation(SKMath::quat orientation);
    CylinderFieldBuilder length(float length);
    CylinderFieldBuilder radius(float radius);
    CylinderField build();
};

} // namespace StardustXRFusion
