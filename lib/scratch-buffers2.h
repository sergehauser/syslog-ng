/*
 * Copyright (c) 2017 Balabit
 * Copyright (c) 2017 Balazs Scheidler <balazs.scheidler@balabit.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#ifndef SCRATCH_BUFFERS2_H_INCLUDED
#define SCRATCH_BUFFERS2_H_INCLUDED 1

#include "syslog-ng.h"

typedef gint32 ScratchBuffersMarker;

GString *scratch_buffers2_alloc(void);
GString *scratch_buffers2_alloc_and_mark(ScratchBuffersMarker *marker);
void scratch_buffers2_mark(ScratchBuffersMarker *marker);
void scratch_buffers2_reclaim_allocations(void);
void scratch_buffers2_reclaim_marked(ScratchBuffersMarker marker);

gint scratch_buffers2_get_global_allocation_count(void);
gint scratch_buffers2_get_local_allocation_count(void);
glong scratch_buffers2_get_local_allocation_bytes(void);
gint scratch_buffers2_get_local_usage_count(void);
void scratch_buffers2_update_stats(void);

/* lazy stats update */
void scratch_buffers2_lazy_update_stats(void);

/* garbage collector */
void scratch_buffers2_explicit_gc(void);

void scratch_buffers2_allocator_init(void);
void scratch_buffers2_allocator_deinit(void);
void scratch_buffers2_automatic_gc_init(void);
void scratch_buffers2_automatic_gc_deinit(void);

void scratch_buffers2_global_init(void);
void scratch_buffers2_global_deinit(void);

#endif
