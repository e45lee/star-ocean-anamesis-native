"""Which model / animation symbols have a hand-written ("readable") implementation, and which
template instance implements each (port/src/native/models/models_anim.cpp).

readable_expr(demangled_name) returns the C++ expression of the function that implements the
symbol, or None if it stays a2c-transcribed. gen_models_a2c.py registers the symbol with that
function instead of its transcription (models_anim_tab.inc) and checks that all symbols mapped to
the same expression share one machine-code shape.
"""
import re

# node transform channels of TAaf<Channel>Controller
CHANNELS = {
    'TranslateX': 'AxisChannel<Node::kPosition, 0>',
    'TranslateY': 'AxisChannel<Node::kPosition, 1>',
    'TranslateZ': 'AxisChannel<Node::kPosition, 2>',
    'ScaleX': 'AxisChannel<Node::kScale, 0>',
    'ScaleY': 'AxisChannel<Node::kScale, 1>',
    'ScaleZ': 'AxisChannel<Node::kScale, 2>',
    'TranslateXYZ': 'VectorChannel<Node::kPosition>',
    'ScaleXYZ': 'VectorChannel<Node::kScale>',
    'RotateX': 'EulerAxisChannel<0>',
    'RotateY': 'EulerAxisChannel<1>',
    'RotateZ': 'EulerAxisChannel<2>',
    'RotateQuaternion': 'RotationChannel',
    'RotateXYZ': 'RotationChannel',
}
DIRECT = {'SetValueOfDirectAddr': 'set_direct', 'AddValueOfDirectAddr': 'add_direct', 'BlendValueOfDirectAddr': 'blend_direct'}
TO_TARGET = {'SetValueToTarget': 'set_to_target', 'AddValueToTarget': 'add_to_target', 'BlendValueToTarget': 'blend_to_target'}


MULTI = {
    'Aska::TAafMultiController<float, 2>::SetValueToTarget(void*, Aska::AafSetValueArg*)': 'MultiTarget<0x18, 8>',
    'Aska::TAafMultiController<float, 4>::SetValueToTarget(void*, Aska::AafSetValueArg*)': 'MultiTarget<0x18, 16>',
    'Aska::TAafMultiController<Aska::Vector, 2>::SetValueToTarget(void*, Aska::AafSetValueArg*)': 'MultiTarget<0x20, 32>',
    'Aska::TAafMultiController<Aska::Vector, 4>::SetValueToTarget(void*, Aska::AafSetValueArg*)': 'MultiTarget<0x20, 64>',
}


def parse(n):
    """-> (outer class, method, control point, value kind, interpolation, inner controller) or None"""
    m = re.match(r'(?:\w+ )?Aska::TAaf(\w+)<(.*)>::(\w+)\(', n)
    if not m:
        return None
    cls, args, meth = m.groups()
    cp = re.search(r'AafControlPoint_(\w+?)(?:_U\d+(?:EX2?)?)?, (true|false), ', args)
    if not cp:
        return None
    compressed = bool(re.search(r'AafControlPoint_\w+?_U\d', args))
    cp, frame_sort = cp.group(1), cp.group(2) == 'true'
    kind = cp.split('_')[0]  # Normal / Int / Vector / Vector4 / Quaternion
    interp = cp.split('_')[1] if '_' in cp else 'Hermite'
    # AafType<ControlPoint, true, ...> (frame-sorted evaluation) keeps the complement points inline
    inner = 'FrameSort' if frame_sort else 'Normal'
    return cls, meth, cp, kind, interp, inner, compressed, frame_sort


VALUE = {'Normal': 'Scalar', 'Int': 'Scalar', 'Vector': 'Vector3', 'Vector4': 'Vector4'}
BYTES = {'Normal': '4', 'Int': '4', 'Vector': '12, true', 'Vector4': '16', 'Quaternion': '16'}


def extrapolation(kind, interp):
    if kind == 'Quaternion':
        return 'StepTrack<16>' if interp == 'Step' else 'QuaternionTrack'
    if kind == 'Int':
        return 'StepTrack<4>' if interp == 'Step' else 'IntLinearTrack'
    if interp == 'Step':
        return f'StepTrack<{BYTES[kind]}>'
    return f'{interp}Track<{VALUE[kind]}>'


# Aska::HierarchicalObject / HierarchicalObjectContainer / JointObject (models_hier.cpp)
HIERARCHY = {
    'Aska::HierarchicalObject::SetPosition(float, float, float)': 'set_position',
    'Aska::HierarchicalObject::SetPosition(Aska::Vector const*)': 'set_position_v',
    'Aska::HierarchicalObject::SetPosture(float, float, float)': 'set_posture_euler',
    'Aska::HierarchicalObject::SetPosture(Aska::Quaternion const*)': 'set_posture_q',
    'Aska::HierarchicalObject::SetPosture(float, float, float, float)': 'set_posture_xyzw',
    'Aska::HierarchicalObject::SetScale(float, float, float)': 'set_scale',
    'Aska::HierarchicalObject::SetScale(Aska::Vector const*)': 'set_scale_v',
    'Aska::HierarchicalObject::SetWorldMatrix(Aska::Matrix const*)': 'set_world_matrix',
    'Aska::HierarchicalObject::WorldMatrix() const': 'world_matrix',
    'Aska::HierarchicalObject::GetDefaultLevel() const': 'default_level',
    'Aska::HierarchicalObject::MakeMatrix()': 'make_matrix',
    'Aska::HierarchicalObjectContainer::MakeMatrix()': 'container_make_matrix',
    'Aska::HierarchicalObjectContainer::GetChildObjectCount() const': 'child_object_count',
    'Aska::HierarchicalObjectContainer::ChildObject(int) const': 'child_object',
    'Aska::JointObject::MakeMatrix()': 'joint_make_matrix',
}


BLEND = {
    'Aska::AafBlendManager::AddAaf(Aska::AafHandler*)': 'add_aaf',
    'Aska::AafBlendManager::SetPlayFrame(int, float)': 'set_play_frame',
    'Aska::AafBlendManager::SetWeight(int, float)': 'set_weight',
    'Aska::AafBlendManager::GetWeight(int) const': 'get_weight',
    'Aska::AafBlendManager::NormalizeWeights()': 'normalize_weights',
    'Aska::AafBlendManager::_CalcNotify::Handler(unsigned long)': 'calc_notify',
    'Aska::AafHandler::SetValues(float)': 'handler_set_values',
    'Aska::AafHandler::BlendValues(float, float)': 'handler_blend_values',
    'Aska::AafHandler::AddValues(float)': 'handler_add_values',
    'Aska::AafHandler::SetValues(float, int)': 'handler_set_values_loop',
    'Aska::AafHandler::SetValuesHighSpeed(float)': 'handler_set_values_high_speed',
    'Aska::AafHandler::SetValuesHighSpeed(float, int)': 'handler_set_values_high_speed_loop',
    'Aska::AafBlendManager::SetValues()': 'set_values',
}


AOF = {
    'Aska::AofObject::SetColorRate(Aska::Vector const*)': 'set_color_rate',
    'Aska::AofObject::SetSystemColorRate(Aska::Vector const*)': 'set_system_color_rate',
    'Aska::AofObject::SetColorOffset(Aska::Vector const*)': 'set_color_offset',
    'Aska::AofObject::SetSystemColorOffset(Aska::Vector const*)': 'set_system_color_offset',
    'Aska::AofObject::SystemColorRate() const': 'system_color_rate',
    'Aska::AofObject::EnableCastShadow(bool)': 'enable_cast_shadow',
    'Aska::AofObject::SetIBLAcceptanceNumber(unsigned int)': 'set_ibl_acceptance_number',
    'Aska::AofObject::GetBoundingBox(bool)': 'get_bounding_box',
    'Aska::AofObject::ComputeBoundingSphere(bool)': 'compute_bounding_sphere',
}


# Readable rewrites of formerly transcribed functions (models_rd_*.cpp, models_rd.h)
RD = {
    'Aska::SkinMatrices::MakeSkinMatrices()': 'Skin::make_skin_matrices',
    'Aska::SkinMatricesBase::KickPalette(Aska::Matrix34*)': 'Skin::kick_palette',
    'Aska::SkinMatricesSimple::MakeSkinMatrices()': 'Skin::make_skin_matrices_simple',
    'void Function_UpdateHierarchicallyByUsingStack<256, false>(Aska::HierarchicalObjectContainer*)': 'HierWalk::update_hierarchically',
    'Aska::HierarchicalObjectContainer::OpenIterator()': 'HierWalk::open_iterator',
    'Aska::HierarchicalObjectContainer::AddToIterator()': 'HierWalk::add_to_iterator',
    'Aska::HierarchicalObjectContainer::IterateMakeMatrix()': 'HierWalk::iterate_make_matrix',
    'Aska::AofObject::CalcBoundingExtent(bool)': 'Aof::calc_bounding_extent',
    'Aska::AofObject::PreliminarilyPrepare(Aska::LightManager*)': 'Aof::preliminarily_prepare',
    'Aska::AofHandler::MakeRenderContext(Aska::RenderContext*, Aska::AofObject*, Aska::RENDERINFO const*, Aska::RenderPass*, Aska::CommandBufferManager*)': 'Aof::make_render_context',
    'Aska::AofObject::PrepareForRendering_Preliminary()': 'Aof::prepare_preliminary',
    'Aska::AofObject::PrepareForRendering(Aska::RENDERINFO const*)': 'Aof::prepare_for_rendering',
    'Aska::AofObject::GetColorPass(Aska::RENDERINFO const*)': 'Aof::get_color_pass',
    'Aska::LightManager::MakeLightContext(Aska::AofObject*, Aska::LightManager::LightContext*, unsigned char*)': 'LightCtx::make_light_context',
    'Aska::AafCalcCommonFunctor::CalcAndSetSubFunctor<Aska::AafCalcType<(Aska::kTYPE_AAFCALCCNTR)0, (Aska::kTYPE_AAFCALCANDSET)0, (Aska::kTYPE_AAFCALCSPEED)0, (Aska::kTYPE_AAFCALC)0, (Aska::kTYPE_AAFLOOPCONDITION)0>, false, false, (Aska::kTYPE_AAFCALCCNTR)0>::operator()(Aska::AafHandler*, Aska::IAnimatable*, Aska::IController*, float, float, unsigned int)': 'Functor::calc_and_set_sub',
}


def readable_expr(n):
    if n in RD:
        return RD[n]
    if n in MULTI:
        return MULTI[n] + '::set_to_target'
    if n in AOF:
        return 'AofObject::' + AOF[n]
    if n in BLEND:
        return 'BlendManager::' + BLEND[n]
    if n == 'Aska::AafKeyframeData_Quaternion_Linear_U32EX::GetValue(float*) const':
        return 'PackedQuaternion::get_value_u32ex'
    if n == 'Aska::AafKeyframeData_Quaternion_Linear_U48EX::GetValue(float*) const':
        return 'PackedQuaternion::get_value_u48ex'
    if n in HIERARCHY:
        return 'Hierarchy::' + HIERARCHY[n]
    p = parse(n)
    if not p:
        return None
    cls, meth, cp, kind, interp, inner, compressed, frame_sort = p
    if cls == 'Controller' and meth == 'GetType':
        ids = {'Normal': 0, 'Normal_Step': 1}
        return f'TypeId<{ids[cp]}>::get_type' if cp in ids else None
    if cls == 'ControllerCompressionLayer' and meth == 'GetValue':
        return 'CompressionLayer::get_value'
    if cls in ('RotateXYZController', 'NormalRotateXYZController') and meth in ('CalcValue', 'CalcValueHighSpeed') and kind == 'Vector':
        if kind + ('_' + interp if interp != 'Hermite' else '') != cp:
            return None
        if frame_sort:
            return f'EulerFrameSortTrack<Vector3{interp}>::calc_value'
        code = re.search(r'AafControlPoint_\w+?_(U16|U24), ', n)
        if code:
            return f'EulerKeyframeTrack<CompressedTrack<Vector3{interp}, false, {code.group(1)}Code>>::calc_value'
        if compressed:
            return None
        return f'EulerKeyframeTrack<KeyframeTrack<Vector3{interp}, false>>::calc_value'
    if cls == 'FrameSortController' and meth == 'CalcValue':
        track = {'Normal': 'Scalar', 'Vector': 'Vector3', 'Int': 'Int', 'Vector4': 'Vector4', 'Quaternion': 'Quaternion'}.get(kind)
        if track:
            return f'FrameSortTrack<{track}{interp}>::calc_value'
        return None
    ex = re.search(r'AafControlPoint_Quaternion_Linear_(U32EX|U48EX|U48EX2), false, false, 0u', n)
    if cls == 'NormalController' and meth in ('CalcValue', 'CalcValueSub', 'SetControlPoints') and ex:
        code = {'U32EX': 'U32Ex', 'U48EX': 'U48Ex', 'U48EX2': 'U48Ex2'}[ex.group(1)]
        fn = {'CalcValue': 'calc_value', 'CalcValueSub': 'calc_value_sub', 'SetControlPoints': 'set_control_points'}[meth]
        return f'PackedQuaternionTrack<{code}Code>::{fn}'
    if cls == 'NormalController' and meth in ('CalcValue', 'CalcValueSub', 'SetControlPoints') and compressed:
        code = re.search(r'AafControlPoint_\w+?_(U16|U24), ', n)
        track = {'Normal': 'Scalar', 'Vector': 'Vector3', 'Vector4': 'Vector4', 'Quaternion': 'Quaternion'}.get(kind)
        if code and track and kind + ('_' + interp if interp != 'Hermite' else '') == cp:
            fn = {'CalcValue': 'calc_value', 'CalcValueSub': 'calc_value_sub', 'SetControlPoints': 'set_control_points'}[meth]
            return f'CompressedTrack<{track}{interp}, {"true" if frame_sort else "false"}, {code.group(1)}Code>::{fn}'
        return None
    if cls == 'NormalController' and meth in ('CalcValue', 'CalcValueSub') and not compressed:
        track = {'Normal': 'Scalar', 'Vector': 'Vector3', 'Vector4': 'Vector4', 'Quaternion': 'Quaternion', 'Int': 'Int'}.get(kind)
        if track and kind + ('_' + interp if interp != 'Hermite' else '') == cp:
            return f'KeyframeTrack<{track}{interp}, {"true" if frame_sort else "false"}>::{"calc_value" if meth == "CalcValue" else "calc_value_sub"}'
        return None
    if meth in ('CalcValueByLinearAtPreOutOfRange', 'CalcValueByLinearAtPostOutOfRange'):
        which = 'linear_pre' if 'Pre' in meth else 'linear_post'
        if cls == 'Controller':
            t = extrapolation(kind, interp)
            if t == 'QuaternionTrack':
                which = 'linear_pre'  # the guest uses one function for both
            return f'{t}::{which}'
        if cls == 'FrameSortRotateXYZController' and kind == 'Vector':
            return f'EulerTrack<{extrapolation(kind, interp)}>::{which}'
        return None
    if meth == 'CalcValueConstant':
        if cls in ('NormalController', 'FrameSortController'):
            return f'ConstantValue<{BYTES[kind]}>::calc_value_constant'
        if cls == 'RotateXYZController' and kind == 'Vector':
            return 'ConstantEuler::calc_value_constant'
        return None
    if meth == 'CalcValueComplement':
        inl = 'true' if inner == 'FrameSort' else 'false'
        if cls in ('NormalController', 'FrameSortController'):
            if kind == 'Quaternion':
                return f'ComplementQuaternion<{inl}, 24>::calc_value_complement'
            return f'ComplementHermite<{VALUE[kind]}, {inl}>::calc_value_complement'
        if cls == 'RotateXYZController' and kind == 'Vector':
            return f'ComplementQuaternion<{inl}, 36>::calc_value_complement'
        return None
    if cls.endswith('Controller') and cls[:-len('Controller')] in CHANNELS:
        ch = CHANNELS[cls[:-len('Controller')]]
        if meth in DIRECT:
            return f'{ch}::{DIRECT[meth]}'
        if meth in TO_TARGET:
            inline = cls in ('RotateXController', 'RotateYController', 'RotateZController')
            return f'NodeController<{ch}{", true" if inline else ""}>::{TO_TARGET[meth]}'
        return None
    if meth == 'SetValueToTarget':
        if cls == 'VectorElementController':
            lane = re.search(r'AafType<Aska::AafControlPoint_\w+, (?:true|false), (?:true|false), (\d)u>', n)
            return f'VectorElementTarget<{lane.group(1)}>::set_to_target' if lane else None
        if cls == 'UVElementController':
            lane = re.search(r'AafType<Aska::AafControlPoint_\w+, (?:true|false), (?:true|false), (\d)u>', n)
            off = '0x50' if not compressed else '0x70' if interp == 'Hermite' and frame_sort else '0x60'
            return f'UVElementTarget<{off}, {lane.group(1)}>::set_to_target' if lane else None
        if cls == 'DiffuseController':
            return 'DiffuseTarget::set_to_target'
        if cls in ('U8Controller', 'U16Controller', 'U32Controller'):
            return f'IntegerTarget<{cls[0].lower()}{cls[1:-len("Controller")].lower()}>::set_to_target'
    if cls == 'Controller' and meth == 'SetValueToTarget':
        return 'AnimatableTarget<Scalar>::set_to_target'
    if cls == 'Controller' and meth == 'AddValueToTarget':
        if kind == 'Vector4':
            return 'NoAdd::add_to_target'
        return f'AnimatableTarget<{VALUE.get(kind, "Quat")}>::add_to_target'
    return None
