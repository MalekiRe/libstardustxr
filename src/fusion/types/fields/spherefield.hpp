#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class SphereField : public Field {
public:
	explicit SphereField(Spatial *parent, SKMath::vec3 origin, float radius);
};

class SphereFieldBuilder {
private:
    Spatial *_parent = nullptr;
    SKMath::vec3 _origin;
    float _radius;
public:
    SphereFieldBuilder parent(Spatial *parent);
    SphereFieldBuilder origin(SKMath::vec3 origin);
    SphereFieldBuilder radius(float radius);
    SphereField build();
};

} // namespace StardustXRFusion
