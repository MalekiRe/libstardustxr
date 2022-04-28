#pragma once

#include <functional>

#include "../node.hpp"
#include "../../sk_math.hpp"
#include "spatial.h"
namespace StardustXRFusion {

class Spatial : public Node {
public:
	explicit Spatial();
	explicit Spatial(Spatial *parent, SKMath::vec3 origin = SKMath::vec3_zero, SKMath::quat orientation = SKMath::quat_identity, SKMath::vec3 scale = SKMath::vec3_one, bool translatable = true, bool rotatable = true, bool scalable = true, bool zoneable = false);

	void createLaunchAnchor(std::function<void(uint32_t)> callback);

	void getTransform(Spatial *space, std::function<void(SKMath::vec3, SKMath::quat, SKMath::vec3)> callback);

	void setOrigin(SKMath::vec3 origin, Spatial &space);
	void setOrigin(SKMath::vec3 origin);

	void setOrientation(SKMath::quat orientation, Spatial &space);
	void setOrientation(SKMath::quat orientation);

	void setPose(SKMath::pose_t pose, Spatial &space);
	void setPose(SKMath::pose_t pose);

	void setScale(SKMath::vec3 scale);

	void setSpatialParent(Spatial *space);
	void setSpatialParentInPlace(Spatial *space);

	void setZoneable(bool zoneable);


protected:
	Spatial(bool destroyable);
};

class SpatialBuilder {
private:
    Spatial *_parent;
    SKMath::vec3 _origin = SKMath::vec3_zero;
    SKMath::quat _orientation = SKMath::quat_identity;
    SKMath::vec3 _scale = SKMath::vec3_one;
    bool _translatable = true;
    bool _rotatable = true;
    bool _scalable = true;
    bool _zoneable = false;
public:
    SpatialBuilder parent(Spatial *parent);
    SpatialBuilder origin(SKMath::vec3 origin);
    SpatialBuilder orientation(SKMath::quat orientation);
    SpatialBuilder scale(SKMath::vec3 scale);
    SpatialBuilder translatable(bool translatable);
    SpatialBuilder rotatable(bool rotatable);
    SpatialBuilder scalable(bool scalable);
    SpatialBuilder zoneable(bool zoneable);
    Spatial build();
};
} // namespace StardustXRFusion
