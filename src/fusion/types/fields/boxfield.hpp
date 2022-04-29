#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class BoxField : public Field {
public:
	explicit BoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size);

	void setSize(Vec3 size);
};

class BoxFieldBuilder {
private:
    Spatial *_parent;
    SKMath::vec3 _origin;
    SKMath::quat _orientation;
    SKMath::vec3 _size;
public:
    BoxFieldBuilder parent(Spatial *parent);
    BoxFieldBuilder origin(SKMath::vec3 origin);
    BoxFieldBuilder size(SKMath::vec3 size);
    BoxFieldBuilder orientation(SKMath::quat orientation);
    BoxField build();
};

} // namespace StardustXRFusion
