#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/engine/gen/objmgr_a2c.cpp: ObjectManager culling and painting-list builders
transcribed from the ARM64 by a2c.py with its CALL_FALLBACK (guest calls through a2c_call) and EXCLUSIVE (exclusive
load/store pairs as host CAS). Usage: tools/gen_objmgr_a2c.py port/src/native/engine/gen/objmgr_a2c.cpp"""
import importlib.util
import os
import re
import sys

import genlib  # (before a2c / elfinfo: the default lib is 3.7.0's; tools/genlib.py)
_spec = importlib.util.spec_from_file_location('a2c', os.path.join(os.path.dirname(os.path.abspath(__file__)), 'a2c.py'))
a2c = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(a2c)
a2c.EXCLUSIVE = True  # bodies declare the exclusive monitor (ex_a_, ex_v_)


def call_fallback(kind, target, reg):
    """Any other guest call: through a2c_call with the whole argument register file (b / br are
    tail calls; a2c appends the goto L_ret)."""
    fn = f'LIB + {target:#x}' if target is not None else reg
    return f'A2C_CALL({fn});'


a2c.CALL_FALLBACK = call_fallback

# (symbol, body name). Every body takes and returns the full register file.
SPEC = [
    ('_ZN4Aska13ObjectManager18ViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm', 'view_frustum_culling'),
    ('_ZN4Aska13ObjectManager16MakePaintingListEi', 'make_painting_list'),
    ('_ZN4Aska13ObjectManager20MakePaintingListPostEv', 'make_painting_list_post'),
    ('_ZN4Aska13ObjectManager27MakeRenderInfoConditionListEPNS0_14RenderInfoCondEPtPiPbj', 'make_render_info_condition_list'),
    ('_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE', 'tom_quick_sort_ascend'),
    ('_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE', 'tom_quick_sort_descend'),
    ('_ZN4Aska13ObjectManager27MultithreadOcclusionCullingEPNS_6CameraEiibPPNS_16RenderableObjectES5_i', 'multithread_occlusion_culling'),
    ('_ZN4Aska13ObjectManager25AddPaintingListCandidatesEPNS_16RenderableObjectE', 'add_painting_list_candidates'),
    ('_ZN4Aska13ObjectManager32Prerender_VersatileAndMotionBlurEPPNS_16RenderableObjectEiPNS_6CameraE', 'prerender_versatile_and_motion_blur'),
    ('_ZN4Aska13ObjectManager19Prerender_MultiPassEPNS_8TLongIntImLi2EEEiPNS_26ObjectManagerJobDispatcherE', 'prerender_multi_pass'),
    ('_ZN4Aska13ObjectManager9PrerenderEv', 'prerender'),
    ('_ZN4Aska13ObjectManager11OnPostPaintEv', 'on_post_paint'),
    ('_ZN4Aska13ObjectManager7OnPaintEv', 'on_paint'),
    # Aska::TaskManager: the per-frame task loop (hooked from taskmgr.cpp)
    ('_ZN4Aska11TaskManager12MakeTaskListEv', 'task_make_task_list'),
    ('_ZN4Aska11TaskManager14OwnersKickTaskEv', 'task_owners_kick_task'),
    ('_ZNK4Aska11TaskManager18GetTotalTaskNumberEv', 'task_get_total_task_number'),
    ('_ZN4Aska11TaskManager3AddEPNS_4TaskE', 'task_add0'),
    ('_ZN4Aska11TaskManager3AddEPNS_4TaskEj', 'task_add'),
    ('_ZN4Aska11TaskManager6AddTopEPNS_4TaskE', 'task_add_top0'),
    ('_ZN4Aska11TaskManager6AddTopEPNS_4TaskEj', 'task_add_top'),
    ('_ZN4Aska11TaskManager6InsertEPNS_4TaskES2_', 'task_insert0'),
    ('_ZN4Aska11TaskManager6InsertEPNS_4TaskES2_j', 'task_insert'),
    ('_ZN4Aska11TaskManager11ChangeLevelEPNS_4TaskEj', 'task_change_level'),
    ('_ZN4Aska11TaskManager6DeleteEPNS_4TaskE', 'task_delete'),
    ('_ZN4Aska11TaskManager23IncrementTaskLevelCountEj', 'task_increment_level_count'),
    ('_ZN4Aska11TaskManager23DecrementTaskLevelCountEj', 'task_decrement_level_count'),
    ('_ZN4Aska11TaskManager16AddThreadBarrierEi', 'task_add_thread_barrier'),
    ('_ZN4Aska11TaskManager19DeleteThreadBarrierEi', 'task_delete_thread_barrier'),
    ('_ZN4Aska11TaskManager27IncrementThreadBarrierCountEi', 'task_increment_thread_barrier_count'),
    ('_ZN4Aska11TaskManager27DecrementThreadBarrierCountEi', 'task_decrement_thread_barrier_count'),
    ('_ZN4Aska11TaskManager19CreateEndNotifyListEi', 'task_create_end_notify_list'),
    ('_ZN4Aska11TaskManager12AddEndNotifyEPNS_7INotifyEm', 'task_add_end_notify'),
    ('_ZN4Aska11TaskManager15RemoveEndNotifyEPNS_7INotifyEm', 'task_remove_end_notify'),
    ('_ZN4Aska11TaskManager8IsCalledEPNS_4TaskE', 'task_is_called'),
    ('_ZN4Aska11TaskManager19PreAllocateTaskListEi', 'task_pre_allocate_task_list'),
    ('_ZN4Aska11TaskManager25DeletePreAllocateTaskListEv', 'task_delete_pre_allocate_task_list'),
    ('_ZN4Aska11TaskManager12MergeManagerEPS0_', 'task_merge_manager'),
    ('_ZN4Aska11TaskManager20ReleaseMergedManagerEv', 'task_release_merged_manager'),
    # Aska::SimpleMessageDispatcher: the multi-message posts (hooked from smd.cpp)
    ('_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS0_8ArgumentEia', 'smd_post_multi'),
    ('_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS0_10ArgumentExEia', 'smd_post_multi_ex'),
    ('_ZN4Aska23SimpleMessageDispatcher16PostSyncMessagesEPNS0_8ArgumentEiPia', 'smd_post_sync'),
    ('_ZN4Aska23SimpleMessageDispatcher16PostSyncMessagesEPNS0_10ArgumentExEiPia', 'smd_post_sync_ex'),
    ('_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS_4TaskEPNS0_19ArgumentWithBarrierEia', 'smd_post_multi_task'),
    ('_ZN4Aska23SimpleMessageDispatcher17PostMultiMessagesEPNS_4TaskEPNS0_21ArgumentWithBarrierExEia', 'smd_post_multi_task_ex'),
]

# Calls between transcribed bodies stay native (a copy of the register file: the callee may
# clobber only what the ABI lets it; x0/v0 come back). memset goes to the host.
for sym, name in SPEC:
    a2c.EXTRA_CALLS[sym] = f'A2C_NATIVE(b_{name});'
a2c.CALLS['memset'] = 'std::memset((void*)X(0), (int)W(1), (size_t)X(2));'
a2c.CALLS['memcpy'] = 'std::memcpy((void*)X(0), (const void*)X(1), (size_t)X(2));'

OUT = sys.argv[1]
out = ['// GENERATED by tools/gen_objmgr_a2c.py from libSOA.so (a2c.py: CALL_FALLBACK + EXCLUSIVE) -- do not edit.',
       '// ' + genlib.stamp(),
       '// Aska::ObjectManager culling, painting-list build and frame driver (Prerender, OnPaint,',
       '// OnPostPaint), transcribed instruction by',
       '// instruction (see objmgr.cpp for how they are hooked and called, objmgr_test.cpp for the tests).',
       '#include <cstring>',
       '',
       '#include "native/engine/math/aska_math_a2c.h"',
       '#include "native/engine/objmgr_a2c.h"',
       '',
       'namespace soa::objmgr::a2c_body {',
       'using namespace ::soa::aska::a2c;',
       '']
for sym, name in SPEC:
    out.append(f'void b_{name}(A64& r);')
out.append('')
for sym, name in SPEC:
    body = a2c.translate(sym, name)
    if '#error' in body:
        sys.exit(f'{sym}: untranslated instructions')
    out.append(f'void b_{name}(A64& r) {{')
    out.append('    u64 jt_ = 0, ex_a_ = 0, ex_v_ = 0;')
    out.append('    (void)jt_, (void)ex_a_, (void)ex_v_;')
    out.append(body.rstrip())
    out.append('}')
    out.append('')
out.append('}  // namespace soa::objmgr::a2c_body')
open(OUT, 'w').write('\n'.join(out) + '\n')
