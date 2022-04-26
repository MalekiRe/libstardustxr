//
// Created by malek on 4/25/22.
//

#ifndef BUILD_SPATIAL_H
#define BUILD_SPATIAL_H
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct spatial {
        void *obj;
    }spatial;
//    typedef struct spatial;

    spatial *spatial_create();
    void mather_destroy(spatial *s);

#ifdef __cplusplus
}
#endif

#endif //BUILD_SPATIAL_H
