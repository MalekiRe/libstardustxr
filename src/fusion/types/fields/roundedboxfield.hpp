#pragma once

#include "field.hpp"

namespace StardustXRFusion {

class RoundedBoxField : public Field {
public:
	explicit RoundedBoxField(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 size);
};
class RoundedBoxFieldBuilder {
private:
    Spatial *_parent = nullptr;
    SKMath::vec3 _origin;
    SKMath::quat _orientation;
    SKMath::vec3 _size;
public:
    RoundedBoxFieldBuilder parent(Spatial *parent);
    RoundedBoxFieldBuilder origin(SKMath::vec3 origin);
    RoundedBoxFieldBuilder orientation(SKMath::quat orientation);
    RoundedBoxFieldBuilder size(SKMath::vec3 size);
    RoundedBoxField build();
};
} // namespace StardustXRFusion
