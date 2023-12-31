/*
 * Copyright (C) 2016 Shane Francis / Jens Andersen
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __QSEECOMFUNC_H_
#define __QSEECOMFUNC_H_

#include "QSEEComAPI.h"

#include <BufferAllocator/BufferAllocatorWrapper.h>
#include <dlfcn.h>
#include <fcntl.h>  // open function
#include <linux/ioctl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>  // close function

#define DMABUF_QCOM_QSEECOM_HEAP_NAME "qcom,qseecom"

// QCOM library functions
typedef int (*start_app_def)(struct QSEECom_handle **clnt_handle, const char *path, const char *fname, uint32_t sb_size);
typedef int (*shutdown_app_def)(struct QSEECom_handle **clnt_handle);
typedef int (*load_external_elf_def)(struct QSEECom_handle **clnt_handle, const char *path, const char *fname);
typedef int (*unload_external_elf_def)(struct QSEECom_handle **handle);
typedef int (*register_listener_def)(struct QSEECom_handle **handle, uint32_t lstnr_id, uint32_t sb_length, uint32_t flags);
typedef int (*unregister_listener_def)(struct QSEECom_handle *handle);
typedef int (*send_cmd_def)(struct QSEECom_handle *handle, void *send_buf, uint32_t sbuf_len, void *rcv_buf, uint32_t rbuf_len);
typedef int (*send_modified_cmd_def)(struct QSEECom_handle *handle, void *send_buf, uint32_t sbuf_len, void *resp_buf, uint32_t rbuf_len, struct QSEECom_ion_fd_info *ifd_data);
typedef int (*receive_req_def)(struct QSEECom_handle *handle, void *buf, uint32_t len);
typedef int (*send_resp_def)(struct QSEECom_handle *handle, void *send_buf, uint32_t len);
typedef int (*set_bandwidth_def)(struct QSEECom_handle *handle, bool high);
typedef int (*app_load_query_def)(struct QSEECom_handle *handle, char *app_name);

// Forward declarations
struct qsee_handle;

// Utility functions
typedef int32_t (*load_trustlet_def)(struct qsee_handle *qsee_handle, struct QSEECom_handle **clnt_handle, const char *path, const char *fname, uint32_t sb_size);

struct dmabuf_handle {
    int fd;
    void *map;
    size_t len;
};

typedef int (*dmabuf_alloc_def)(struct qsee_handle *qsee_handle, struct dmabuf_handle *dmabuf, size_t len);
typedef void (*dmabuf_free_def)(struct dmabuf_handle *dmabuf);

struct qsee_handle {
    void *_data;

    // QCOM lib functions
    start_app_def start_app;
    shutdown_app_def shutdown_app;
    load_external_elf_def load_external_elf;
    unload_external_elf_def unload_external_elf;
    register_listener_def register_listener;
    unregister_listener_def unregister_listener;
    send_cmd_def send_cmd;
    send_modified_cmd_def send_modified_cmd;
    receive_req_def receive_req;
    send_resp_def send_resp;
    set_bandwidth_def set_bandwidth;
    app_load_query_def app_load_query;
    // Utility functions provided by this library
    dmabuf_alloc_def dmabuf_alloc;
    dmabuf_free_def dmabuf_free;
    load_trustlet_def load_trustlet;
};

int qsee_open_handle(struct qsee_handle **handle);
int qsee_free_handle(struct qsee_handle **handle);

#endif
