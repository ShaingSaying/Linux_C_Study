/* shm base function
* hxw 20180709
*/

#ifndef __SHM_BASE_H__
#define __SHM_BASE_H__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>
//#include "logger.h"

#ifdef __cplusplus
extern "C" {
#endif

int gen_shm(const char *file_name, int size);
int attach_shm(int shmid, void **shm);
int attach_shm_by_filename(const char *file_name, void **shm);
int detach_shm(void *shm);
int rm_shm(int shmid);


#ifdef __cplusplus
}
#endif

#endif
