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
    } spatial;
    spatial *stardust_spatial_create();
    void stardust_spatial_destroy(spatial *spatial);

#ifdef __cplusplus
}
#endif

#endif //BUILD_SPATIAL_H
