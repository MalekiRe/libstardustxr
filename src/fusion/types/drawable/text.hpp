#pragma once

#include <string>
#include <utility>

#include "../spatial/spatial.hpp"



namespace StardustXRFusion {

class Text : public Spatial {
public:
	enum Align { // Shamelessly stolen from StereoKit (https://github.com/maluoi/StereoKit/blob/master/StereoKitC/stereokit.h#L1066-L1106=)
		XLeft        = 1 << 0,
		YTop         = 1 << 1,
		XCenter      = 1 << 2,
		YCenter      = 1 << 3,
		XRight       = 1 << 4,
		YBottom      = 1 << 5,
		Center       = XCenter | YCenter,
		CenterLeft   = XLeft   | YCenter,
		CenterRight  = XRight  | YCenter,
		TopCenter    = XCenter | YTop,
		TopLeft      = XLeft   | YTop,
		TopRight     = XRight  | YTop,
		BottomCenter = XCenter | YBottom,
		BottomLeft   = XLeft   | YBottom,
		BottomRight  = XRight  | YBottom,
	};
	enum Fit { // Shamelessly stolen from StereoKit (https://github.com/maluoi/StereoKit/blob/master/StereoKitC/stereokit.h#L979-L995=)
		Wrap     = 1 << 0,
		Clip     = 1 << 1,
		Squeeze  = 1 << 2,
		Exact    = 1 << 3,
		Overflow = 1 << 4,
	};

	explicit Text(Spatial *parent, std::string text = "Text", float characterHeight = 1.f, Vec3 origin = Vec3::Zero, Quat orientation = Quat::Identity, std::string fontPath = "", Align textAlign = Align::TopLeft, Vec2 bounds = Vec2::Zero, Fit fit = Fit::Overflow, Align boundsAlign = Align::TopLeft, Color color = Color::White);

	void setText(std::string text);
	void setColor(Color color);
};

class TextBuilder {
private:
    Spatial *_parent = nullptr;
    std::string _text = "null";
    float _characterHeight = 2.f;
    SKMath::vec3 _origin = SKMath::vec3_zero;
    SKMath::quat _orientation = SKMath::quat_identity;
    std::string _fontPath;
    Text::Align _textAlign = Text::Align::TopLeft;
    SKMath::vec2 _bounds = SKMath::vec2_zero;
    Text::Fit _fit = Text::Fit::Overflow;
    Text::Align _boundsAlign = Text::Align::TopLeft;
    SKMath::color _color = {1,1,1,1};
public:
    TextBuilder parent(Spatial *parent);
    TextBuilder text(std::string text);
    TextBuilder characterHeight(float characterHeight);
    TextBuilder origin(SKMath::vec3 origin);
    TextBuilder origin(float x, float y, float z);
    TextBuilder orientation(SKMath::quat orientation);
    TextBuilder orientation(float x, float y, float z);
    TextBuilder fontPath(std::string fontPath);
    TextBuilder textAlign(Text::Align textAlign);
    TextBuilder bounds(SKMath::vec2 bounds);
    TextBuilder fit(Text::Fit fit);
    TextBuilder boundsAlign(Text::Align boundsAlign);
    Text build();
    Text* buildRef();

};

} // namespace StardustXRFusion
