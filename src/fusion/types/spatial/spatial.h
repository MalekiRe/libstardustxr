//
// Created by malek on 4/25/22.
//

#ifndef BUILD_SPATIAL_H
#define BUILD_SPATIAL_H
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct stardust_spatial {
        void *obj;
    } stardust_spatial;
    stardust_spatial *stardust_spatial_create();
    void stardust_spatial_destroy(stardust_spatial *spatial);

#ifdef __cplusplus
}
#endif

#endif //BUILD_SPATIAL_H
