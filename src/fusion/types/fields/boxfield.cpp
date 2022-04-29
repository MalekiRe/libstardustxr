#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "boxfield.hpp"
#include "boxfield.h"

//C-Interface
stardust_boxfield *stardust_boxfield_create(stardust_spatial *s, skmath_vec3 origin, skmath_quat orientation, skmath_vec3 size) {
    stardust_boxfield *b;
    b = (stardust_boxfield *)malloc(sizeof(*b));
    b->obj = new StardustXRFusion::BoxField(static_cast<StardustXRFusion::Spatial *>(s->obj),
                                            stardust_convert_skmath_vec3(origin), stardust_convert_skmath_quat(orientation),
                                            stardust_convert_skmath_vec3(size));
    return b;
}
void stardust_boxfield_destroy(stardust_boxfield *b) {
    delete static_cast<StardustXRFusion::BoxField *>(b->obj);
    free(b);
}

stardust_field *stardust_boxfield_to_field_cast(stardust_boxfield *b) {
    return reinterpret_cast<stardust_field *>(b);
}



namespace StardustXRFusion {

BoxField::BoxField(Spatial *parent, Vec3 origin, Quat rotation, Vec3 size) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createBoxField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_VEC3(size)
		)
	);
}

void BoxField::setSize(Vec3 size) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSize",
		FLEX_ARG(
			FLEX_VEC3(size)
		)
	);
}
//Builder
BoxFieldBuilder BoxFieldBuilder::parent(Spatial *parent) {
    this->_parent = parent;
    return *this;
}
BoxFieldBuilder BoxFieldBuilder::origin(SKMath::vec3 origin) {
    this->_origin = origin;
    return *this;
}
BoxFieldBuilder BoxFieldBuilder::size(SKMath::vec3 size) {
    this->_size = size;
    return *this;
}
BoxFieldBuilder BoxFieldBuilder::orientation(SKMath::quat orientation) {
    this->_orientation = orientation;
    return *this;
}
BoxField BoxFieldBuilder::build() {
    return {_parent, _origin, _orientation, _size};
}


} // namespace StardustXRFusion
