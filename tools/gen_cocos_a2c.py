#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/ui/cocos/gen/cocos_a2c.cpp: Framework::Cocos functions transcribed from the ARM64
by a2c.py (CALL_FALLBACK: other calls go to the guest through objmgr's a2c_call, i.e. straight to
native replacements where they exist). Unnamed functions are named as tools/genlib.py does
(`anon:<prev symbol>#k`, `lambda:<enclosing>#k.slot`), so the list holds for any lib.
Lib: SOA_LIB, default work/libSOA-3.7.0.so (tools/genlib.py); the output header records it.
Usage: tools/gen_cocos_a2c.py port/src/native/ui/cocos/gen/cocos_a2c.cpp"""
import importlib.util
import os
import sys

import genlib  # (before a2c: the default lib is 3.7.0's)

_spec = importlib.util.spec_from_file_location('a2c', os.path.join(os.path.dirname(os.path.abspath(__file__)), 'a2c.py'))
a2c = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(a2c)
a2c.EXCLUSIVE = True

# (symbol or 0xaddr:size, body name)
SPEC = [
    ('_ZN9Framework5Cocos11CCocosLabel8DrawSelfEv', 'label_draw_self'),
    # CCocosLabel's text layout helper (local function: splits the text into lines and tagged
    # runs and puts them into the CDirectAofTextRenderer), only called by Label::DrawSelf.
    ('anon:_ZN9Framework5Cocos11CCocosLabel8DrawSelfEv#1', 'label_put_text'),
    ('_ZN9Framework5Cocos17CCocosProgressBar8DrawSelfEv', 'progress_bar_draw_self'),
    ('_ZN9Framework5Cocos11CCocosScene21_pSearchRendererLightERKNS0_8Blending13tRenderResult12tRenderStateE', 'search_renderer_light'),
    ('_ZN9Framework5Cocos11CCocosScene22_pSearchRendererLight2ERKNS0_8Blending13tRenderResult12tRenderStateE', 'search_renderer_light2'),
    # ListView / ScrollView (PageView and the Particle / SpriteNew UnisonParent stay guest: no
    # reachable screen has one to test them on): pre-draw (item layout, culling, limit-mode item
    # recycling through the view's std::function), scroll positions and physics.
    ('_ZN9Framework5Cocos14CCocosListView11PreDrawSelfEf', 'list_view_predraw_self'),
    ('_ZN9Framework5Cocos14CCocosListView13ForeachUpdateERKNSt6__ndk18functionIFvPNS0_10CCocosNodeEiiEEE', 'list_view_foreach_update'),
    ('_ZN9Framework5Cocos14CCocosListView15UpdateAlignmentEv', 'list_view_update_alignment'),
    ('_ZN9Framework5Cocos14CCocosListView25UpdateAlignment_LimitModeEv', 'list_view_update_alignment_limit_mode'),
    ('_ZN9Framework5Cocos16CCocosScrollView11PreDrawSelfEf', 'scroll_view_predraw_self'),
    ('_ZN9Framework5Cocos16CCocosScrollView12CullChildrenEv', 'scroll_view_cull_children'),
    ('_ZN9Framework5Cocos16CCocosScrollView16ResetInertiaRateEv', 'scroll_view_reset_inertia_rate'),
    ('_ZN9Framework5Cocos16CCocosScrollView18PreDrawSelf_BeforeEf', 'scroll_view_predraw_self_before'),
    ('_ZN9Framework5Cocos16CCocosScrollView18ReactionBounceBackEv', 'scroll_view_reaction_bounce_back'),
    ('_ZN9Framework5Cocos16CCocosScrollView18SetBounceBackValueEf', 'scroll_view_set_bounce_back_value'),
    ('_ZN9Framework5Cocos16CCocosScrollView18_DragCallback_CoreEPNS0_10CCocosNodeE', 'scroll_view_drag_callback_core'),
    ('_ZN9Framework5Cocos16CCocosScrollView19SetVerticalPositionEf', 'scroll_view_set_vertical_position'),
    ('_ZN9Framework5Cocos16CCocosScrollView21SetHorizontalPositionEf', 'scroll_view_set_horizontal_position'),
    ('_ZN9Framework5Cocos16CCocosScrollView26SetVirticalPositionOnClampEf', 'scroll_view_set_vertical_position_on_clamp'),
    ('_ZN9Framework5Cocos16CCocosScrollView37SetVirticalPositionDirectAreaPositionEf', 'scroll_view_set_vertical_position_direct_area'),
    ('_ZNK9Framework5Cocos16CCocosScrollView19GetVerticalPositionEb', 'scroll_view_get_vertical_position'),
    ('_ZNK9Framework5Cocos16CCocosScrollView21GetHorizontalPositionEv', 'scroll_view_get_horizontal_position'),
    # Event-scene UI: the scene objects' Cocos layout sync (UnisonParent), the character
    # image node (face overlay), the typewriter's shown text.
    ('_ZN13EventScenario20CEventScenarioSprite12UnisonParentEv', 'es_sprite_unison_parent'),
    ('_ZN13EventScenario23CEventScenarioCharacter12UnisonParentEv', 'es_character_unison_parent'),
    ('_ZN13EventScenario24CEventScenarioBackGround12UnisonParentEv', 'es_background_unison_parent'),
    ('_ZN13EventScenario33CCocosImageEventScenarioCharacter11PreDrawSelfEf', 'es_chara_image_predraw_self'),
    ('_ZN13EventScenario33CCocosImageEventScenarioCharacter8DrawSelfEv', 'es_chara_image_draw_self'),
    ('_ZN13EventScenario33CCocosImageEventScenarioCharacter20SetFaceImageResourceERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS5_22CSTLStringAllocatorInfEEEEE', 'es_chara_image_set_face'),
    ('_ZN13EventScenario18CEventScenarioBase13CMessagePrint10UpdateTextEv', 'es_message_print_update_text'),
    # Backlog lines (the stage-direction variant stays guest: no tested scene has one): a new label (a copy of the template message label) with the logged text and
    # speaker, added to the backlog's scroll view; returns its height.
    ('_ZN13EventScenario21CEventScenarioBackLog20CreateLogMessageNodeERKNS0_7LogDataE', 'es_backlog_create_node'),
    # CCocosNode's touch listener callbacks (the lambdas SetEventListenerTouchCallback stores
    # in its CCocosEventListenerTouch; operator() of each __func) and the hit tests.
    ('lambda:N9Framework5Cocos10CCocosNode29SetEventListenerTouchCallbackEv#0.6', 'node_touch_cancel_all'),
    ('lambda:N9Framework5Cocos10CCocosNode29SetEventListenerTouchCallbackEv#1.6', 'node_touch_began'),
    ('lambda:N9Framework5Cocos10CCocosNode29SetEventListenerTouchCallbackEv#2.6', 'node_touch_moved'),
    ('lambda:N9Framework5Cocos10CCocosNode29SetEventListenerTouchCallbackEv#3.6', 'node_touch_ended'),
    ('lambda:N9Framework5Cocos10CCocosNode29SetEventListenerTouchCallbackEv#4.6', 'node_touch_cancelled'),
    ('_ZNK9Framework5Cocos10CCocosNode8HitCheckERKNS_8CVector2E', 'node_hit_check_point'),
    ('_ZNK9Framework5Cocos10CCocosNode8HitCheckERKNS_5CRectE', 'node_hit_check_rect'),
    # Particles (emitter update, spawn, quads), the slider, and per-frame scene helpers.
    ('_ZN9Framework5Cocos14CCocosParticle11PreDrawSelfEf', 'particle_predraw_self'),
    ('_ZN9Framework5Cocos14CCocosParticle14UpdateParticleEf', 'particle_update'),
    ('_ZN9Framework5Cocos14CCocosParticle12AddParticlesEi', 'particle_add'),
    ('_ZN9Framework5Cocos14CCocosParticle13CParticleData12copyParticleEii', 'particle_copy'),
    ('_ZN9Framework5Cocos14CCocosParticle8DrawSelfEv', 'particle_draw_self'),
    ('_ZNK9Framework5Cocos14CCocosParticle14GetRenderCountEv', 'particle_render_count'),
    ('_ZN9Framework5Cocos12CCocosSlider11PreDrawSelfEf', 'slider_predraw_self'),
    ('_ZNK9Framework5Cocos12CCocosSlider8HitCheckERKNS_8CVector2E', 'slider_hit_check_point'),
    ('_ZNK9Framework5Cocos12CCocosSlider8HitCheckERKNS_5CRectE', 'slider_hit_check_rect'),
    ('_ZN9Framework5Cocos11CCocosScene21AddClipingEndRendererEPKNS0_10CCocosNodeE', 'scene_add_clip_end'),
    ('_ZNK9Framework5Cocos11CCocosScene19GetAspectFromLayoutERNS_8CVector2ERKNS0_16tLayoutComponentE', 'scene_aspect_from_layout'),
    ('_ZN9Framework5Cocos11CCocosScene15_PreComputeSelfEv', 'scene_precompute_self'),
    ('_ZNK9Framework5Cocos11CCocosPanel15GetClippingRectEv', 'panel_clipping_rect'),
    # The whole CCocosPanel::DrawSelf, used for the gradient background (mode 2; cocos_drawself.cpp
    # has the other modes hand-written).
    ('_ZN9Framework5Cocos11CCocosPanel8DrawSelfEv', 'panel_draw_self_full'),
    # CCocosDictionaryHelper: the typed lookups into ASON values the layout reader uses.
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper12F32ValueJsonERKN4Aska4ASON6AValueEPKcf', 'dh_f32value_137'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper12S32ValueJsonERKN4Aska4ASON6AValueEPKci', 'dh_s32value_293'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper14ArrayCountJsonERKN4Aska4ASON6AValueEPKci', 'dh_arraycount_293'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper14ArrayCountJsonERKN4Aska4ASON6AValueEi', 'dh_arraycount_172'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper16BooleanValueJsonERKN4Aska4ASON6AValueEPKcb', 'dh_booleanvalue_942'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper16pStringValueJsonERKN4Aska4ASON6AValueEPKcS8_', 'dh_pstringvalue_811'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper17IsObjectExistJsonERKN4Aska4ASON6AValueE', 'dh_isobjectexist_103'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper17IsObjectExistJsonERKN4Aska4ASON6AValueEPKc', 'dh_isobjectexist_453'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper17IsObjectExistJsonERKN4Aska4ASON6AValueEj', 'dh_isobjectexist_518'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper18rSubDictionaryJsonERKN4Aska4ASON6AValueEPKc', 'dh_rsubdictionary_453'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper18rSubDictionaryJsonERKN4Aska4ASON6AValueEPKci', 'dh_rsubdictionary_293'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper18rSubDictionaryJsonERKN4Aska4ASON6AValueEj', 'dh_rsubdictionary_518'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper21F32ValueFromArrayJsonERKN4Aska4ASON6AValueEPKcjf', 'dh_f32valuefromarray_92'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper21S32ValueFromArrayJsonERKN4Aska4ASON6AValueEPKcji', 'dh_s32valuefromarray_78'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper22BoolValueFromArrayJsonERKN4Aska4ASON6AValueEPKcjb', 'dh_boolvaluefromarray_91'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper24rDictionaryFromArrayJsonERKN4Aska4ASON6AValueEPcj', 'dh_rdictionaryfromarray_25'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper24rDictionaryFromArrayJsonERKN4Aska4ASON6AValueEj', 'dh_rdictionaryfromarray_518'),
    ('_ZN9Framework5Cocos22CCocosDictionaryHelper25pStringValueFromArrayJsonERKN4Aska4ASON6AValueEPKcjS8_', 'dh_pstringvaluefromarray_451'),
]
LOCAL_SPEC = {a: '0x%x:0x%x' % genlib.resolve_spec(a) for a, _ in SPEC if a.startswith(('0x', 'anon:', 'lambda:'))}
LOCAL = {int(LOCAL_SPEC[a].split(':')[0], 16): n for a, n in SPEC if a in LOCAL_SPEC}


def call_fallback(kind, target, reg):
    if target is not None and target in LOCAL:
        return f'A2C_NATIVE(b_{LOCAL[target]});'
    fn = f'LIB + {target:#x}' if target is not None else reg
    return f'A2C_CALL({fn});'


a2c.CALL_FALLBACK = call_fallback
for sym, name in SPEC:
    if sym not in LOCAL_SPEC:
        a2c.EXTRA_CALLS[sym] = f'A2C_NATIVE(b_{name});'
a2c.CALLS['memset'] = 'std::memset((void*)X(0), (int)W(1), (size_t)X(2));'
a2c.CALLS['memcpy'] = 'std::memcpy((void*)X(0), (const void*)X(1), (size_t)X(2));'
a2c.CALLS['memmove'] = 'std::memmove((void*)X(0), (const void*)X(1), (size_t)X(2));'
a2c.CALLS['strlen'] = 'X(0) = std::strlen((const char*)X(0));'

OUT = sys.argv[1]
out = ['// GENERATED by tools/gen_cocos_a2c.py from libSOA.so (a2c.py: CALL_FALLBACK + EXCLUSIVE) -- do not edit.',
       '// ' + genlib.stamp(),
       '// Framework::Cocos functions transcribed instruction by instruction (see cocos_transcribed.cpp for',
       '// how they are hooked, cocos_drawself_test.cpp for the tests).',
       '#include <cstring>',
       '',
       '#include "native/engine/math/aska_math_a2c.h"',
       '#include "native/engine/objmgr_a2c.h"',
       '',
       'namespace soa::objmgr::a2c_body {',
       'using namespace ::soa::aska::a2c;',
       'using ::soa::aska::Mat44;',
       'using ::soa::aska::Vec4;',
       '']
for sym, name in SPEC:
    out.append(f'void b_{name}(A64& r);')
out.append('')
for sym, name in SPEC:
    body = a2c.translate(LOCAL_SPEC.get(sym, sym), name)
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
