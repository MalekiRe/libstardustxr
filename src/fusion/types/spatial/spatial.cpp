#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "sk_math.hpp"
#include "spatial.hpp"
#include "spatial.h"
using namespace SKMath;
//C-Interface
stardust_spatial *stardust_spatial_create() {
    stardust_spatial *s;
    StardustXRFusion::Spatial *obj;

    s = (stardust_spatial *)malloc(sizeof(*s));
    obj = new StardustXRFusion::Spatial(StardustXRFusion::Root());
    s->obj = obj;
    return (stardust_spatial *)s;
}
void stardust_spatial_destroy(stardust_spatial *s) {
    if(s == nullptr) {
        fprintf(stderr, "error, tried to free null pointer of spatial object\n");
        return;
    }
    delete static_cast<StardustXRFusion::Spatial *>(s->obj);
    free(s);
}
namespace StardustXRFusion {


//C++ Implementation
Spatial::Spatial(bool destroyable) : Node(destroyable) {}

Spatial::Spatial() : Node(false) {
	this->nodeName = "";
	this->nodePath = "";
}

Spatial::Spatial(Spatial *parent, SKMath::vec3 origin, SKMath::quat orientation, SKMath::vec3 scale, bool translatable, bool rotatable, bool scalable, bool zoneable) :
Node(true) {
	nodePath = "/spatial/spatial";
	nodeName = GenerateID();
	messenger->sendSignal(
		"/spatial",
		"createSpatial",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_VEC3(scale)
			FLEX_BOOL(translatable)
			FLEX_BOOL(rotatable)
			FLEX_BOOL(scalable)
			FLEX_BOOL(zoneable)
		)
	);
}

void Spatial::createLaunchAnchor(std::function<void (uint32_t)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"createLaunchAnchor",
		FLEX_ARG(FLEX_NULL),
		[callback](flexbuffers::Reference data) {
			callback(data.AsUInt32());
		}
	);
}

void Spatial::setOrigin(vec3 origin, Spatial &space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING(space.getNodePath())
			FLEX_VEC3(origin)
			FLEX_NULL
			FLEX_NULL
		)
	);
}
void Spatial::setOrigin(vec3 origin) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_NULL
			FLEX_VEC3(origin)
			FLEX_NULL
			FLEX_NULL
		)
	);
}

void Spatial::setOrientation(quat orientation, Spatial &space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING(space.getNodePath())
			FLEX_NULL
			FLEX_QUAT(orientation)
			FLEX_NULL
		)
	);
}
void Spatial::setOrientation(quat orientation) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_NULL
			FLEX_NULL
			FLEX_QUAT(orientation)
			FLEX_NULL
		)
	);
}

void Spatial::setPose(pose_t pose, Spatial &space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING(space.getNodePath())
			FLEX_VEC3(pose.position)
			FLEX_QUAT(pose.orientation)
			FLEX_NULL
		)
	);
}
void Spatial::setPose(pose_t pose) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_NULL
			FLEX_VEC3(pose.position)
			FLEX_QUAT(pose.orientation)
			FLEX_NULL
		)
	);
}

void Spatial::setScale(SKMath::vec3 scale) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setTransform",
		FLEX_ARGS(
			FLEX_STRING("")
			FLEX_NULL
			FLEX_NULL
			FLEX_VEC3(scale)
		)
	);
}

void Spatial::getTransform(Spatial *space, std::function<void(SKMath::vec3, SKMath::quat, SKMath::vec3)> callback) {
	messenger->executeRemoteMethod(
		getNodePath().c_str(),
		"getTransform",
		FLEX_ARG(FLEX_STRING(space ? space->getNodePath() : std::string(""))),
		[callback](flexbuffers::Reference data) {
			flexbuffers::Vector vec = data.AsVector();
			callback(SK_VEC3(vec[0].AsTypedVector()), SK_QUAT(vec[1].AsTypedVector()), SK_VEC3(vec[2].AsTypedVector()));
		}
	);
}

void Spatial::setSpatialParent(Spatial *space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSpatialParent",
		FLEX_ARG(
			FLEX_STRING(space ? space->getNodePath() : std::string(""))
		)
	);
}

void Spatial::setSpatialParentInPlace(Spatial *space) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setSpatialParentInPlace",
		FLEX_ARG(
			FLEX_STRING(space ? space->getNodePath() : std::string(""))
		)
	);
}

void Spatial::setZoneable(bool zoneable) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"setZoneable",
		FLEX_ARG(
			FLEX_BOOL(zoneable)
		)
	);
}

    SpatialBuilder SpatialBuilder::parent(Spatial *parent) {
        this->_parent = parent;
        return *this;
    }

    SpatialBuilder SpatialBuilder::origin(SKMath::vec3 origin) {
        this->_origin = origin;
        return *this;
    }

    SpatialBuilder SpatialBuilder::orientation(SKMath::quat orientation) {
        this->_orientation = orientation;
        return *this;
    }

    SpatialBuilder SpatialBuilder::scale(SKMath::vec3 scale) {
        this->_scale = scale;
        return *this;
    }

    SpatialBuilder SpatialBuilder::translatable(bool translatable) {
        this->_translatable = translatable;
        return *this;
    }

    SpatialBuilder SpatialBuilder::rotatable(bool rotatable) {
        this->_rotatable = rotatable;
        return *this;
    }

    SpatialBuilder SpatialBuilder::scalable(bool scalable) {
        this->_scalable = scalable;
        return *this;
    }

    SpatialBuilder SpatialBuilder::zoneable(bool zoneable) {
        this->_zoneable = zoneable;
        return *this;
    }

    Spatial SpatialBuilder::build() {
        return {_parent, _origin, _orientation, _scale, _translatable, _rotatable, _scalable, _zoneable};
    }
} // namespace StardustXRFusion
