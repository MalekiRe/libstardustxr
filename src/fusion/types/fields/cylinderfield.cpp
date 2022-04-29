#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "cylinderfield.hpp"



namespace StardustXRFusion {

CylinderField::CylinderField(Spatial *parent, Vec3 origin, Quat rotation, float length, float radius) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createCylinderField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_FLOAT(length)
			FLEX_FLOAT(radius)
		)
	);
}
//Builder
CylinderFieldBuilder CylinderFieldBuilder::parent(Spatial *parent){
    this->_parent = parent;
    return *this;
}
CylinderFieldBuilder CylinderFieldBuilder::origin(SKMath::vec3 origin){
    this->_origin = origin;
    return *this;
}
CylinderFieldBuilder CylinderFieldBuilder::orientation(SKMath::quat orientation){
    this->_orientation = orientation;
    return *this;
}
CylinderFieldBuilder CylinderFieldBuilder::length(float length){
    this->_length = length;
    return *this;
}
CylinderFieldBuilder CylinderFieldBuilder::radius(float radius){
    this->_radius = radius;
    return *this;
}
CylinderField CylinderFieldBuilder::build(){
    return {_parent, _origin, _orientation, _length, _radius};
}
} // namespace StardustXRFusion
