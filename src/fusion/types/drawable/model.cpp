#include "model.hpp"

#include "../../flex.hpp"
#include "../../fusion_internal.hpp"

using namespace SKMath;

namespace StardustXRFusion {

Model::Model(Spatial *parent, std::string relativePath, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale) : Spatial(true) {
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
			FLEX_QUAT(orientation)
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

void Model::setMaterialProperty(uint32_t submesh, std::string propertyName, color col) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setMaterialProperty",
		FLEX_ARGS(
			FLEX_ADD(submesh)
			FLEX_STRING(propertyName)
			FLEX_COLOR(col)
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

ModelBuilder *ModelBuilder::parent(Spatial *parent) {
    return nullptr;
}

ModelBuilder *ModelBuilder::relativePath(std::string relativePath) {
    return nullptr;
}

ModelBuilder *ModelBuilder::orientation(SKMath::quat orientation) {
    return nullptr;
}

ModelBuilder *ModelBuilder::origin(SKMath::vec3 origin) {
    return nullptr;
}

ModelBuilder *ModelBuilder::scale(SKMath::vec3) {
    return nullptr;
}


ModelBuilder::ModelBuilder() {
    //just to prevent use of constructor
}

void ModelBuilder::deleteBuilder() {
    delete this;
}
} // namespace StardustXRFusion
