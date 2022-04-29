#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "roundedboxfield.hpp"
#include "types/fields/boxfield.hpp"



namespace StardustXRFusion {

RoundedBoxField::RoundedBoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createRoundedBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_VEC3(size)
		)
	);
}

RoundedBoxFieldBuilder RoundedBoxFieldBuilder::parent(Spatial *parent) {
    this->_parent = parent;
    return *this;
}

RoundedBoxFieldBuilder RoundedBoxFieldBuilder::origin(SKMath::vec3 origin) {
    this->_origin = origin;
    return *this;
}

RoundedBoxFieldBuilder RoundedBoxFieldBuilder::orientation(SKMath::quat orientation) {
    this->_orientation = orientation;
    return *this;
}

RoundedBoxFieldBuilder RoundedBoxFieldBuilder::size(SKMath::vec3 size) {
    this->_size = size;
    return *this;
}

RoundedBoxField RoundedBoxFieldBuilder::build() {
    return {_parent, _origin, _orientation, _size};
}
} // namespace StardustXRFusion
