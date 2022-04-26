#pragma once

#include <string>

#include "../spatial/spatial.hpp"

namespace StardustXRFusion {

class Model : public Spatial {
public:
	explicit Model(Spatial *parent, std::string relativePath, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, SKMath::vec3 scale = SKMath::vec3_one);

	void setMaterialProperty(uint32_t submesh, std::string propertyName, float value);
	void setMaterialProperty(uint32_t submesh, std::string propertyName, SKMath::color col);
	void setMaterialProperty(uint32_t submesh, std::string propertyName, std::string value);

	operator bool()const {
		return valid;
	}
protected:
	bool valid = false;
};

class ModelBuilder {
private:
    Spatial *_parent = nullptr;
    std::string _relativePath;
    SKMath::vec3 _origin = SKMath::vec3_zero;
    SKMath::quat _orientation = SKMath::quat_identity;
    SKMath::vec3 _scale = SKMath::vec3_one;
    ModelBuilder();
public:
    static ModelBuilder begin() {
        return {};
    }
    void deleteBuilder();
    ModelBuilder* parent(Spatial *parent);
    ModelBuilder* relativePath(std::string relativePath);
    ModelBuilder* origin(SKMath::vec3 origin);
    ModelBuilder* orientation(SKMath::quat orientation);
    ModelBuilder* scale(SKMath::vec3);

};
} // namespace StardustXRFusion
