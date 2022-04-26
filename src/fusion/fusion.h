//
// Created by malek on 4/25/22.
//
#include "types/spatial/spatial.h"
#include <stdbool.h>
#ifndef BUILD_FUSION_H
#define BUILD_FUSION_H
#ifdef __cplusplus
extern "C" {
#endif
    spatial *stardust_get_root();
    bool stardust_setup();
    void stardust_run_event_loop();
#ifdef __cplusplus
}
#endif
#endif //BUILD_FUSION_H
