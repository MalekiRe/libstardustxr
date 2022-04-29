#include "model.hpp"

#include <utility>

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"
#include "model.h"



//C-Interface
stardust_model *stardust_model_create(stardust_spatial *parent, char *str) {
    stardust_model *m;
    StardustXRFusion::Model *obj;

    m = (stardust_model *)malloc(sizeof(*m));
    obj = new StardustXRFusion::Model(static_cast<StardustXRFusion::Model *>(parent->obj), str);
    m->obj = obj;
    return (stardust_model *)m;
}
void stardust_model_destroy(stardust_model *t) {
    if(t == nullptr) {
        fprintf(stderr, "error, tried to free null pointer of model object\n");
        return;
    }
    delete static_cast<StardustXRFusion::Model *>(t->obj);
    free(t);
}
void set_material_property_float(stardust_model *m, int submesh, char* propertyName, float value) {
    static_cast<StardustXRFusion::Model *>(m->obj)->setMaterialProperty(submesh, propertyName, value);
}
void set_material_property_color(stardust_model *m,int submesh, char* propertyName, skmath_color col) {
    static_cast<StardustXRFusion::Model *>(m->obj)->setMaterialProperty(submesh, propertyName, stardust_convert_skmath_color(col));
}
void set_material_property_string(stardust_model *m, int submesh, char* propertyName, char* value) {
    static_cast<StardustXRFusion::Model *>(m->obj)->setMaterialProperty(submesh, propertyName, value);
}
namespace StardustXRFusion {

Model::Model(Spatial *parent, std::string relativePath, Vec3 origin, Quat rotation, Vec3 scale) : Spatial(true) {
	if(!FileExists(relativePath))
		return;
	nodePath = "/drawable/model";
	nodeName = GenerateID();
	messenger->sendSignal(
		"/drawable",
		"createModelFromFile",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(ConvertExeRelativePath(relativePath))
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_VEC3(scale)
		)
	);
	valid = true;
}

void Model::setMaterialProperty(uint32_t submesh, std::string propertyName, float value) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setMaterialProperty",
		FLEX_ARGS(
			FLEX_ADD(submesh)
			FLEX_STRING(propertyName)
			FLEX_FLOAT(value)
		)
	);
}

void Model::setMaterialProperty(uint32_t submesh, std::string propertyName, Color color) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setMaterialProperty",
		FLEX_ARGS(
			FLEX_ADD(submesh)
			FLEX_STRING(propertyName)
			FLEX_COLOR(color)
		)
	);
}

void Model::setMaterialProperty(uint32_t submesh, std::string propertyName, std::string value) {
	if(!FileExists(value))
		return;
	messenger->sendSignal(
		getNodePath().c_str(),
		"setMaterialProperty",
		FLEX_ARGS(
			FLEX_ADD(submesh)
			FLEX_STRING(propertyName)
			FLEX_STRING(ConvertExeRelativePath(value))
		)
	);
}

ModelBuilder ModelBuilder::parent(Spatial *parent) {
    this->_parent = parent;
    return *this;
}

ModelBuilder ModelBuilder::relativePath(std::string relativePath) {
    this->_relativePath = std::move(relativePath);
    return *this;
}

ModelBuilder ModelBuilder::orientation(SKMath::quat orientation) {
    this->_orientation = orientation;
    return *this;
}

ModelBuilder ModelBuilder::origin(SKMath::vec3 origin) {
    this->_origin = origin;
    return *this;
}

ModelBuilder ModelBuilder::scale(SKMath::vec3 scale) {
    this->_scale = scale;
    return *this;
}
Model ModelBuilder::build() {
    return Model(_parent, _relativePath, _origin, _orientation, _scale);
}

} // namespace StardustXRFusion
