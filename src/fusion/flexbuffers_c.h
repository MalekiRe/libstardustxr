//
// Created by malek on 4/26/22.
//
#include <flatbuffers/flexbuffers.h>
#pragma once
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif
    typedef struct flex_buffers_reference {
        void *obj;
    } flex_buffers_reference;

#ifdef __cplusplus
}
    static flex_buffers_reference *createFromFlexBuffer(flexbuffers::Reference ref) {
        flex_buffers_reference *flex;
        flex = (flex_buffers_reference *)(malloc(sizeof(*flex)));
        flex->obj = &ref;
        return flex;
    }
    static void deleteFromFlexBuffer(flex_buffers_reference *ref) {
        free(ref);
    }
#endif