#include "text.hpp"
#include "../../flex.hpp"
#include "../../fusion_internal.hpp"
#include "text.h"
using namespace SKMath;

//C-Interface
stardust_text *stardust_text_create(stardust_spatial *parent, char *str) {
    stardust_text *t;
    StardustXRFusion::Text *obj;
    t = (stardust_text*)malloc(sizeof(*t));
    obj = new StardustXRFusion::Text(static_cast<StardustXRFusion::Spatial*>(parent->obj), std::string(str));
    t->obj = obj;
    return t;
}
void stardust_text_destroy(stardust_text *t) {
    if(t == nullptr) {
        fprintf(stderr, "error, tried to free null pointer of text object\n");
        return;
    }
    delete static_cast<StardustXRFusion::Text *>(t->obj);
    free(t);
}
void stardust_text_set_text(stardust_text *t, char* str) {
    static_cast<StardustXRFusion::Text *>(t->obj)->setText(std::string(str));
}
void stardust_text_set_color(stardust_text *t, skmath_color color) {
    static_cast<StardustXRFusion::Text *>(t->obj)->setColor(stardust_convert_skmath_color(color));
}


stardust_text_builder *stardust_text_builder_create() {
    stardust_text_builder *builder;
    builder = (stardust_text_builder*)malloc(sizeof(*builder));
    builder->obj = new StardustXRFusion::TextBuilder();
    return builder;
}
void stardust_text_builder_destroy(stardust_text_builder *b) {
    if(b == nullptr) {
        fprintf(stderr, "error, tried to free null point of a text builder object\n");
        return;
    }
    delete static_cast<StardustXRFusion::TextBuilder *>(b->obj);
    free(b);
}
stardust_text_builder *stardust_text_builder_parent(stardust_text_builder *b, stardust_spatial *parent) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->parent(static_cast<StardustXRFusion::Spatial *>(parent->obj));
    return b;
}
stardust_text_builder *stardust_text_builder_text(stardust_text_builder *b, const char* text) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->text(text);
    return b;
}
stardust_text_builder *stardust_text_builder_characterHeight(stardust_text_builder *b, float characterHeight) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->characterHeight(characterHeight);
    return b;
}
stardust_text_builder *stardust_text_builder_origin(stardust_text_builder *b, skmath_vec3 vec3) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->origin(stardust_convert_skmath_vec3(vec3));
    return b;
}
stardust_text_builder *stardust_text_builder_orientation(stardust_text_builder *b, skmath_quat quat) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->orientation(stardust_convert_skmath_quat(quat));
    return b;
}
stardust_text_builder *stardust_text_builder_fontPath(stardust_text_builder *b, const char* path) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->fontPath(path);
}
stardust_text_builder *stardust_text_builder_textAlign(stardust_text_builder *b, stardust_text_align alignment) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->textAlign(stardustConvertTextAlign(alignment));
}
stardust_text_builder *stardust_text_builder_bounds(stardust_text_builder *b, skmath_vec2 bounds) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->bounds(stardust_convert_skmath_vec2(bounds));
}
stardust_text_builder *stardust_text_builder_fit(stardust_text_builder *b, stardust_text_fit fit) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->fit(stardustConvertTextFit(fit));
}
stardust_text_builder *stardust_text_builder_boundsAlign(stardust_text_builder *b, stardust_text_align boundsAlign) {
    static_cast<StardustXRFusion::TextBuilder *>(b->obj)->boundsAlign(stardustConvertTextAlign(boundsAlign));
}
stardust_text *stardust_text_builder_build(stardust_text_builder *b) {
    return createStardustTextFromText(static_cast<StardustXRFusion::TextBuilder *>(b->obj)->build());
}

namespace StardustXRFusion {

//C++ implementation
Text::Text(Spatial *parent, std::string text, float characterHeight, SKMath::vec3 origin, SKMath::quat orientation, std::string fontPath, Align textAlign, SKMath::vec2 bounds, Fit fit, Align boundsAlign, SKMath::color color) : Spatial(true) {
//	if(!FileExists(relativePath))
//		return;
	nodePath = "/drawable/text";
	nodeName = GenerateID();
	messenger->sendSignal(
		"/drawable",
		"createText",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(orientation)
			FLEX_STRING(text)
			FLEX_STRING(fontPath != "" ? ConvertExeRelativePath(fontPath) : std::string(""))
			FLEX_FLOAT(characterHeight)
			FLEX_UINT(textAlign)
			FLEX_VEC2(bounds)
			FLEX_UINT(fit)
			FLEX_UINT(boundsAlign)
			FLEX_COLOR(color)
		)
	);
}

void Text::setText(std::string text) {
	messenger->sendSignal(
		getNodePath(),
		"setText",
		FLEX_ARG(FLEX_STRING(text))
	);
}

void Text::setColor(SKMath::color color) {
	messenger->sendSignal(
		getNodePath(),
		"setColor",
		FLEX_ARG(FLEX_COLOR(color))
	);
}


//TextBuilder Methods
TextBuilder TextBuilder::parent(Spatial *parent) {
    this->_parent = parent;
    return *this;
}
TextBuilder TextBuilder::text(std::string text) {
    this->_text = std::move(text);
    return *this;
}
TextBuilder TextBuilder::characterHeight(float characterHeight) {
    this->_characterHeight = characterHeight;
    return *this;
}
TextBuilder TextBuilder::origin(SKMath::vec3 origin) {
    this->_origin = origin;
    return *this;
}
TextBuilder TextBuilder::origin(float x, float y, float z) {
    return origin(SKMath::vec3{x, y, z});
}
TextBuilder TextBuilder::orientation(SKMath::quat orientation) {
    this->_orientation = orientation;
    return *this;
}
TextBuilder TextBuilder::orientation(float x, float y, float z) {
    return orientation(SKMath::quat_from_angles(x, y, z));
}
TextBuilder TextBuilder::fontPath(std::string fontPath) {
    this->_fontPath = std::move(fontPath);
    return *this;
}
TextBuilder TextBuilder::textAlign(Text::Align textAlign) {
    this->_textAlign = textAlign;
    return *this;
}
TextBuilder TextBuilder::bounds(SKMath::vec2 bounds) {
    this->_bounds = bounds;
    return *this;
}
TextBuilder TextBuilder::fit(Text::Fit fit) {
    this->_fit = fit;
    return *this;
}
TextBuilder TextBuilder::boundsAlign(Text::Align boundsAlign) {
    this->_boundsAlign = boundsAlign;
    return *this;
}
Text TextBuilder::build() {
    return {_parent, _text, _characterHeight, _origin, _orientation,  _fontPath, _textAlign, _bounds, _fit, _boundsAlign, _color};
}

Text* TextBuilder::buildRef() {
    return new Text(_parent, _text, _characterHeight, _origin, _orientation,  _fontPath, _textAlign, _bounds, _fit, _boundsAlign, _color);
}


} // namespace StardustXRFusion
