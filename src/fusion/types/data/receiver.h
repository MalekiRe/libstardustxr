//
// Created by malek on 4/26/22.
//
#pragma once
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif
typedef struct stardust_receiver {
    void *obj;
}stardust_receiver;

    stardust_receiver* stardust_receiver_create();
    void stardust_receiver_destroy(stardust_receiver* r);

#ifdef __cplusplus
}
#endif
