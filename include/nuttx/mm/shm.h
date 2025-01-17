/****************************************************************************
 * include/nuttx/mm/shm.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_MM_SHM_H
#define __INCLUDE_NUTTX_MM_SHM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <nuttx/mm/gran.h>

#ifdef CONFIG_MM_SHM

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

#ifndef CONFIG_ARCH_ADDRENV
#  error CONFIG_ARCH_ADDRENV must be selected with CONFIG_MM_SHM
#endif

#ifndef CONFIG_BUILD_KERNEL
#  error CONFIG_BUILD_KERNEL must be selected with CONFIG_MM_SHM
#endif

#ifndef CONFIG_GRAN
#  error CONFIG_GRAN must be selected with CONFIG_MM_SHM
#endif

#ifndef CONFIG_MM_PGALLOC
#  error CONFIG_MM_PGALLOC must be selected with CONFIG_MM_SHM
#endif

/* Debug */

#ifdef CONFIG_DEBUG_SHM
#  define shmerr                    _err
#  define shminfo                   _info
#else
#  define shmerr                    merr
#  define shminfo                   minfo
#endif

/****************************************************************************
 * Public Type Definitions
 ****************************************************************************/

struct task_group_s; /* Forward declaration */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* This structure describes the virtual page allocator that is use to manage
 * the mapping of shared memory into the group/process address space.
 */

struct group_shm_s
{
  /* Handle returned by gran_initialize() when the virtual page allocator
   * was created.
   */

  GRAN_HANDLE gs_handle;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: shm_group_initialize
 *
 * Description:
 *   Initialize the group shared memory data structures when a new task
 *   group is initialized.
 *
 * Input Parameters:
 *   group - A reference to the new group structure to be initialized.
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int shm_group_initialize(FAR struct task_group_s *group);

/****************************************************************************
 * Name: shm_group_release
 *
 * Description:
 *   Release resources used by the group shared memory logic.  This function
 *   is called at the time at the group is destroyed.
 *
 * Input Parameters:
 *   group - A reference to the group structure to be un-initialized.
 *
 * Returned Value:
 *   None
 *
 ****************************************************************************/

void shm_group_release(FAR struct task_group_s *group);

/****************************************************************************
 * Name: shm_alloc
 *
 * Description:
 *   Allocate virtual memory region from the shared memory pool.
 *
 * Input Parameters:
 *   group - A reference to the group structure to be un-initialized.
 *   vaddr - Virtual start address where the allocation starts, if NULL, will
 *           seek and return an address that satisfies the 'size' parameter
 *   size - Size of the area to allocate
 *
 * Returned Value:
 *   Pointer to reserved vaddr, or NULL if out-of-memory
 *
 ****************************************************************************/

FAR void *shm_alloc(FAR struct task_group_s *group, FAR void *vaddr,
                    size_t size);

/****************************************************************************
 * Name: shm_free
 *
 * Description:
 *   Free a previously allocated virtual memory region back to the shared
 *   memory pool.
 *
 * Input Parameters:
 *   group - A reference to the group structure to be un-initialized.
 *   vaddr - Virtual start address where the allocation starts.
 *   size - Size of the allocated area.
 *
 ****************************************************************************/

void shm_free(FAR struct task_group_s *group, FAR void *vaddr, size_t size);

/****************************************************************************
 * Name: shmdt_priv
 *
 * Description:
 *   This is the shmdt internal implementation of the shm driver. It takes
 *   the task group struct as a parameter and can handle both normal detach
 *   and cleanup during process exit.
 *
 * Input Parameters:
 *   group   - A reference to the group structure from which to detach
 *   shmaddr - Virtual start address where the allocation starts.
 *   shmid   - Id of the allocation
 *
 ****************************************************************************/

int shmdt_priv(FAR struct task_group_s *group, FAR const void *shmaddr,
               int shmid);

#endif /* CONFIG_MM_SHM */
#endif /* __INCLUDE_NUTTX_MM_SHM_H */
