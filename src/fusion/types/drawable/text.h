//
// Created by malek on 4/25/22.
//
#include "../../skmathstructs.h"
#pragma once
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif
enum stardust_text_align { // Shamelessly stolen from StereoKit (https://github.com/maluoi/StereoKit/blob/master/StereoKitC/stereokit.h#L1066-L1106=)
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
enum stardust_text_fit { // Shamelessly stolen from StereoKit (https://github.com/maluoi/StereoKit/blob/master/StereoKitC/stereokit.h#L979-L995=)
    Wrap     = 1 << 0,
    Clip     = 1 << 1,
    Squeeze  = 1 << 2,
    Exact    = 1 << 3,
    Overflow = 1 << 4,
};
typedef struct stardust_text {
    void *obj;
}stardust_text;

typedef struct stardust_text_builder {
    void *obj;
} stardust_text_builder;

stardust_text *stardust_text_create(stardust_spatial *parent, char *str);
void stardust_text_destroy(stardust_text *t);
void stardust_text_set_text(stardust_text *t, char* str);
void stardust_text_set_color(stardust_text *t, skmath_color color) ;


stardust_text_builder *stardust_text_builder_create();
void stardust_text_builder_destroy(stardust_text_builder *b);
stardust_text_builder *stardust_text_builder_parent(stardust_text_builder *b, stardust_spatial *parent);
stardust_text_builder *stardust_text_builder_text(stardust_text_builder *b, const char* text);
stardust_text_builder *stardust_text_builder_characterHeight(stardust_text_builder *b, float characterHeight);
stardust_text_builder *stardust_text_builder_origin(stardust_text_builder *b, skmath_vec3 vec3);
stardust_text_builder *stardust_text_builder_orientation(stardust_text_builder *b, skmath_quat quat);
stardust_text_builder *stardust_text_builder_fontPath(stardust_text_builder *b, const char* path);
stardust_text_builder *stardust_text_builder_textAlign(stardust_text_builder *b, enum stardust_text_align alignment);
stardust_text_builder *stardust_text_builder_bounds(stardust_text_builder *b, skmath_vec2 bounds);
stardust_text_builder *stardust_text_builder_fit(stardust_text_builder *b, enum stardust_text_fit fit);
stardust_text_builder *stardust_text_builder_boundsAlign(stardust_text_builder *b, enum  stardust_text_align boundsAlign);
stardust_text *stardust_text_builder_build(stardust_text_builder *b);

#ifdef __cplusplus
}
static stardust_text *createStardustTextFromText(StardustXRFusion::Text t) {
    stardust_text *text;
    text = (stardust_text *)malloc(sizeof(*text));
    text->obj = &t;
    return text;
}
static StardustXRFusion::Text::Align stardustConvertTextAlign(stardust_text_align alignment) {
    switch(alignment) {
        case XLeft: return StardustXRFusion::Text::Align::XLeft;
        case XRight: return StardustXRFusion::Text::Align::XRight;
        case XCenter: return StardustXRFusion::Text::Align::XCenter;

        case YTop: return StardustXRFusion::Text::Align::YTop;
            break;
        case YCenter: return StardustXRFusion::Text::Align::YCenter;
            break;
        case YBottom: return StardustXRFusion::Text::Align::YBottom;
            break;
        case Center: return StardustXRFusion::Text::Align::Center;
            break;
        case CenterLeft: return StardustXRFusion::Text::Align::CenterLeft;
            break;
        case CenterRight: return StardustXRFusion::Text::Align::CenterRight;
            break;
        case TopCenter: return StardustXRFusion::Text::Align::TopCenter;
            break;
        case TopLeft: return StardustXRFusion::Text::Align::TopLeft;
            break;
        case TopRight: return StardustXRFusion::Text::Align::TopRight;
            break;
        case BottomCenter: return StardustXRFusion::Text::Align::BottomCenter;
            break;
        case BottomLeft: return StardustXRFusion::Text::Align::BottomLeft;
            break;
        case BottomRight: return StardustXRFusion::Text::Align::BottomRight;
            break;
    }
}
static StardustXRFusion::Text::Fit stardustConvertTextFit(stardust_text_fit fit) {
    switch(fit) {

        case Wrap: return StardustXRFusion::Text::Fit::Wrap;
            break;
        case Clip: return StardustXRFusion::Text::Fit::Clip;
            break;
        case Squeeze: return StardustXRFusion::Text::Fit::Squeeze;
            break;
        case Exact: return StardustXRFusion::Text::Fit::Exact;
            break;
        case Overflow: return StardustXRFusion::Text::Fit::Overflow;
            break;
    }
}
#endif