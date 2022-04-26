#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "sk_math.hpp"
#include "spherefield.hpp"

using namespace SKMath;

namespace StardustXRFusion {

SphereField::SphereField(Spatial *parent, SKMath::vec3 origin, float radius) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createSphereField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_FLOAT(radius)
		)
	);
}
//Builder
SphereFieldBuilder SphereFieldBuilder::parent(Spatial *parent) {
    this->_parent = parent;
    return *this;
}
SphereFieldBuilder SphereFieldBuilder::origin(SKMath::vec3 origin) {
    this->_origin = origin;
    return *this;
}
SphereFieldBuilder SphereFieldBuilder::radius(float radius) {
    this->_radius = radius;
    return *this;
}
SphereField SphereFieldBuilder::build() {
    return {_parent, _origin, _radius};
}
} // namespace StardustXRFusion
