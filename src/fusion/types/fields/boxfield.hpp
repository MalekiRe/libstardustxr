#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class BoxField : public Field {
public:
	BoxField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size);

	void setSize(SKMath::vec3 size);
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
