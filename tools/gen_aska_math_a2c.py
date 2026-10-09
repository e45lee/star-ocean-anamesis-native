#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Generates port/src/native/engine/math/gen/aska_math_a2c.cpp from the ARM64 code via a2c.py."""
import importlib.util
import os
import subprocess
import sys

import genlib  # (before a2c: the default lib is 3.7.0's)

_spec = importlib.util.spec_from_file_location('a2c', os.path.join(os.path.dirname(os.path.abspath(__file__)), 'a2c.py'))
a2c = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(a2c)

OUT = sys.argv[1]

M, CM, V, CV, Q, CQ, M34, CM34 = 'Mat44*', 'const Mat44*', 'Vec4*', 'const Vec4*', 'Quat*', 'const Quat*', 'Mat34*', 'const Mat34*'
F, I, U = 'float', 'int', 'uint32_t'
VP, CVP, PP = 'void*', 'const void*', 'void**'  # geometry structs (Box, Sphere, Plane, Segment, AABB, culling shapes)
OP = 'const OrthoPlane*'
AX, ROW, BL = 'int /*axis 0..2*/', 'unsigned /*row 0..3*/', 'bool'
MR = 'Mat44@x8'

# (symbol, c name, return type, [arg types], group)  -- arg types map to x regs (pointers/ints)
# or s regs (float) in order; return 'Vec4@x8' means an indirect result through x8.
# (Matrix::Mul / MulFromLeft and ToColor[v] are hand-written in aska_math.cpp.)
SPEC = [
    # Aska::Matrix
    ('_ZNK4Aska6Matrix14InvertLowErrorEPS0_', 'mat_invert_low_error', 'bool', [CM, M], 'mat'),
    ('_ZN4Aska6Matrix14InvertLowErrorEv', 'mat_invert_low_error', 'bool', [M], 'mat'),
    ('_ZN4Aska6Matrix6InvertEv', 'mat_invert', 'void', [M], 'mat'),
    ('_ZNK4Aska6Matrix6PutPRSEPNS_6VectorEPNS_10QuaternionES2_', 'mat_put_prs', 'void', [CM, V, Q, V], 'mat'),
    ('_ZN4Aska6Matrix17SetLookAtMatrixXPEPKNS_6VectorES3_f', 'mat_set_look_at_xp', 'void', [M, CV, CV, F], 'mat'),
    ('_ZN4Aska6Matrix17SetLookAtMatrixXNEPKNS_6VectorES3_f', 'mat_set_look_at_xn', 'void', [M, CV, CV, F], 'mat'),
    ('_ZN4Aska6Matrix17SetLookAtMatrixYPEPKNS_6VectorES3_f', 'mat_set_look_at_yp', 'void', [M, CV, CV, F], 'mat'),
    ('_ZN4Aska6Matrix17SetLookAtMatrixYNEPKNS_6VectorES3_f', 'mat_set_look_at_yn', 'void', [M, CV, CV, F], 'mat'),
    ('_ZN4Aska6Matrix17SetLookAtMatrixZPEPKNS_6VectorES3_f', 'mat_set_look_at_zp', 'void', [M, CV, CV, F], 'mat'),
    ('_ZN4Aska6Matrix17SetLookAtMatrixZNEPKNS_6VectorES3_f', 'mat_set_look_at_zn', 'void', [M, CV, CV, F], 'mat'),
    ('_ZN4Aska6Matrix19SetLookAtMatrixZPUpEPKNS_6VectorES3_S3_f', 'mat_set_look_at_zp_up', 'void', [M, CV, CV, CV, F], 'mat'),
    ('_ZN4Aska6Matrix22CreateWithoutNormalizeEPKNS_10QuaternionE', 'mat_create_without_normalize', 'void', [M, CQ], 'mat'),
    ('_ZN4Aska6Matrix22CreateWithoutNormalizeEPKNS_10QuaternionEPKNS_6VectorE', 'mat_create_without_normalize', 'void', [M, CQ, CV], 'mat'),
    ('_ZN4Aska6Matrix19CreateWithNormalizeEPKNS_10QuaternionE', 'mat_create_with_normalize', 'void', [M, CQ], 'mat'),
    ('_ZN4Aska6Matrix19CreateWithNormalizeEPKNS_10QuaternionEPKNS_6VectorE', 'mat_create_with_normalize', 'void', [M, CQ, CV], 'mat'),
    ('_ZN4Aska6Matrix11SetRotationEPKNS_6VectorE14EnumRotateType', 'mat_set_rotation', 'void', [M, CV, I], 'mat'),
    ('_ZN4Aska6Matrix6RotateEPKNS_6VectorE14EnumRotateType', 'mat_rotate', 'void', [M, CV, I], 'mat'),
    ('_ZN4Aska6Matrix6RotateEPKNS_10QuaternionE', 'mat_rotate', 'void', [M, CQ], 'mat'),
    ('_ZN4Aska6Matrix23SetRotationByUnitVectorEPKNS_6VectorE', 'mat_set_rotation_by_unit_vector', 'void', [M, CV], 'mat'),
    ('_ZN4Aska6Matrix18RotateByUnitVectorEPKNS_6VectorE', 'mat_rotate_by_unit_vector', 'void', [M, CV], 'mat'),
    ('_ZN4Aska6Matrix7RotateYEf', 'mat_rotate_y', 'void', [M, F], 'mat'),
    ('_ZN4Aska6Matrix12SetTranslateEPKNS_6VectorE', 'mat_set_translate', 'void', [M, CV], 'mat'),
    ('_ZN4Aska6Matrix9TranslateEPKNS_6VectorE', 'mat_translate', 'void', [M, CV], 'mat'),
    ('_ZN4Aska6Matrix5ScaleEPKNS_6VectorE', 'mat_scale', 'void', [M, CV], 'mat'),
    ('_ZN4Aska6Matrix8MakeClipEffPNS_6VectorES2_', 'mat_make_clip', 'void', [M, F, F, V, V], 'mat'),
    ('_ZN4Aska6Matrix16MakeClipToScreenEfPNS_6VectorES2_ffff', 'mat_make_clip_to_screen', 'void', [M, F, V, V, F, F, F, F], 'mat'),
    ('_ZN4Aska6Matrix9MulVectorEPKNS_6VectorE', 'mat_mul_vector', 'void', [M, CV], 'mat'),
    ('_ZNK4Aska6Matrix9MulVectorEPS0_PKNS_6VectorE', 'mat_mul_vector', 'void', [CM, M, CV], 'mat'),
    ('_ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_', 'mat_apply_vector', 'void', [CM, V, CV], 'mat'),
    ('_ZN4Aska6Matrix37SetProjectionShadowMatrixForOmniLightEPKNS_6VectorES3_', 'mat_set_projection_shadow_omni', 'void', [M, CV, CV], 'mat'),
    ('_ZN4Aska6Matrix44SetProjectionShadowMatrixForDirectionalLightEPKNS_6VectorES3_', 'mat_set_projection_shadow_directional', 'void', [M, CV, CV], 'mat'),
    ('_ZN4Aska6Matrix4LerpEPKS0_S2_f', 'mat_lerp', 'void', [M, CM, CM, F], 'mat'),
    ('_ZN4Aska14MatrixCalcFuncEPNS_6MatrixEPKNS_6VectorEPKNS_10QuaternionES7_S4_S4_PKS0_', 'matrix_calc_func', 'void', [M, CV, CQ, CQ, CV, CV, CM], 'mat'),
    # Aska::Matrix34
    ('_ZN4Aska8Matrix346CreateEPKNS_10QuaternionE', 'mat34_create', 'void', [M34, CQ], 'mat34'),
    ('_ZN4Aska8Matrix346CreateEPKNS_10QuaternionEPKNS_6VectorE', 'mat34_create', 'void', [M34, CQ, CV], 'mat34'),
    ('_ZN4Aska8Matrix3419CreateWithNormalizeEPKNS_10QuaternionE', 'mat34_create_with_normalize', 'void', [M34, CQ], 'mat34'),
    ('_ZN4Aska8Matrix3419CreateWithNormalizeEPKNS_10QuaternionEPKNS_6VectorE', 'mat34_create_with_normalize', 'void', [M34, CQ, CV], 'mat34'),
    ('_ZN4Aska8Matrix3411SetRotationEPKNS_6VectorE14EnumRotateType', 'mat34_set_rotation', 'void', [M34, CV, I], 'mat34'),
    ('_ZN4Aska8Matrix3423SetRotationByUnitVectorEPKNS_6VectorE', 'mat34_set_rotation_by_unit_vector', 'void', [M34, CV], 'mat34'),
    ('_ZN4Aska8Matrix346RotateEPKNS_6VectorE14EnumRotateType', 'mat34_rotate', 'void', [M34, CV, I], 'mat34'),
    ('_ZN4Aska8Matrix3418RotateByUnitVectorEPKNS_6VectorE', 'mat34_rotate_by_unit_vector', 'void', [M34, CV], 'mat34'),
    ('_ZN4Aska8Matrix3412SetTranslateEPKNS_6VectorE', 'mat34_set_translate', 'void', [M34, CV], 'mat34'),
    ('_ZN4Aska8Matrix349TranslateEPKNS_6VectorE', 'mat34_translate', 'void', [M34, CV], 'mat34'),
    ('_ZN4Aska8Matrix3414InvertLowErrorEv', 'mat34_invert_low_error', 'void', [M34], 'mat34'),
    ('_ZN4Aska8Matrix349MulVectorEPKNS_6VectorE', 'mat34_mul_vector', 'void', [M34, CV], 'mat34'),
    ('_ZNK4Aska8Matrix349MulVectorEPS0_PKNS_6VectorE', 'mat34_mul_vector', 'void', [CM34, M34, CV], 'mat34'),
    ('_ZNK4Aska8Matrix3411ApplyVectorEPNS_6VectorEPKS1_', 'mat34_apply_vector', 'void', [CM34, V, CV], 'mat34'),
    ('_ZN4Aska8Matrix3417SetLookAtMatrixXPEPKNS_6VectorES3_f', 'mat34_set_look_at_xp', 'void', [M34, CV, CV, F], 'mat34'),
    ('_ZN4Aska8Matrix3417SetLookAtMatrixXNEPKNS_6VectorES3_f', 'mat34_set_look_at_xn', 'void', [M34, CV, CV, F], 'mat34'),
    ('_ZN4Aska8Matrix3417SetLookAtMatrixYPEPKNS_6VectorES3_f', 'mat34_set_look_at_yp', 'void', [M34, CV, CV, F], 'mat34'),
    ('_ZN4Aska8Matrix3417SetLookAtMatrixYNEPKNS_6VectorES3_f', 'mat34_set_look_at_yn', 'void', [M34, CV, CV, F], 'mat34'),
    ('_ZN4Aska8Matrix3417SetLookAtMatrixZPEPKNS_6VectorES3_f', 'mat34_set_look_at_zp', 'void', [M34, CV, CV, F], 'mat34'),
    ('_ZN4Aska8Matrix3417SetLookAtMatrixZNEPKNS_6VectorES3_f', 'mat34_set_look_at_zn', 'void', [M34, CV, CV, F], 'mat34'),
    ('_ZN4Aska8Matrix343MulEPKS0_S2_', 'mat34_mul', 'void', [M34, CM34, CM34], 'mat34'),
    # Framework::CMatrix / CQuaternion / CVector
    ('_ZN9Framework7CMatrix9TranslateERKNS_7CVectorE', 'cmat_translate', 'void', [M, CV], 'fw'),
    ('_ZN9Framework7CMatrix12AddTranslateERKNS_7CVectorE', 'cmat_add_translate', 'void', [M, CV], 'fw'),
    ('_ZNK9Framework7CMatrix9TranslateEv', 'cmat_get_translate', 'Vec4@x8', [CM], 'fw'),
    ('_ZN9Framework7CMatrix13AddTranslateXEf', 'cmat_add_translate_x', 'void', [M, F], 'fw'),
    ('_ZN9Framework7CMatrix13AddTranslateYEf', 'cmat_add_translate_y', 'void', [M, F], 'fw'),
    ('_ZN9Framework7CMatrix13AddTranslateZEf', 'cmat_add_translate_z', 'void', [M, F], 'fw'),
    ('_ZN9Framework7CMatrix23RotateYWithoutTranslateEf', 'cmat_rotate_y_without_translate', 'void', [M, F], 'fw'),
    ('_ZNK9Framework7CMatrix6AngleYEv', 'cmat_angle_y', 'float', [CM], 'fw'),
    ('_ZNK9Framework7CMatrix13ExtractRotateEv', 'cmat_extract_rotate', MR, [CM], 'fw'),
    ('_ZN9Framework7CMatrix13ExtractRotateERKS0_', 'cmat_extract_rotate_from', 'void', [M, CM], 'fw'),
    ('_ZN9Framework7CMatrix7InverseEv', 'cmat_inverse', 'void', [M], 'fw'),
    ('_ZN9Framework7CMatrix19InverseMathematicalEv', 'cmat_inverse_mathematical', 'void', [M], 'fw'),
    ('_ZN9Framework7CMatrix16LookAtMatrixZPUpERKNS_7CVectorES3_S3_f', 'cmat_look_at_zp_up', 'void', [M, CV, CV, CV, F], 'fw'),
    ('_ZN9Framework7CMatrix12SetRowVectorEjRKNS_7CVectorE', 'cmat_set_row_vector', 'void', [M, ROW, CV], 'fw'),
    ('_ZN9Framework7CMatrix10ApplyScaleEf', 'cmat_apply_scale', 'void', [M, F], 'fw'),
    ('_ZN9Framework7CMatrix10ApplyScaleERKNS_7CVectorE', 'cmat_apply_scale', 'void', [M, CV], 'fw'),
    ('_ZNK9Framework7CMatrix6PutPRSEPNS_7CVectorEPNS_11CQuaternionES2_', 'cmat_put_prs', 'void', [CM, V, Q, V], 'fw'),
    ('_ZNK9Framework7CMatrix14ExtractRotateXEv', 'cmat_extract_rotate_x', MR, [CM], 'fw'),
    ('_ZNK9Framework7CMatrix14ExtractRotateYEv', 'cmat_extract_rotate_y', MR, [CM], 'fw'),
    ('_ZNK9Framework7CMatrix14ExtractRotateZEv', 'cmat_extract_rotate_z', MR, [CM], 'fw'),
    ('_ZNK9Framework7CMatrix16ExtractTranslateEv', 'cmat_extract_translate', MR, [CM], 'fw'),
    ('_ZNK9Framework7CMatrix10QuaternionEv', 'cmat_quaternion', 'Vec4@x8', [CM], 'fw'),
    ('_ZNK9Framework7CMatrix10GetInverseEv', 'cmat_get_inverse', MR, [CM], 'fw'),
    ('_ZNK9Framework7CMatrix22GetInverseMathematicalEv', 'cmat_get_inverse_mathematical', MR, [CM], 'fw'),
    ('_ZN9Framework7CMatrix12MakeIdentityEv', 'cmat_make_identity', MR, [], 'fw'),
    ('_ZN9Framework7CMatrix13MakeTranslateERKNS_7CVectorE', 'cmat_make_translate', MR, [CV], 'fw'),
    ('_ZN9Framework7CMatrix14MakeTranslateXEf', 'cmat_make_translate_x', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix14MakeTranslateYEf', 'cmat_make_translate_y', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix14MakeTranslateZEf', 'cmat_make_translate_z', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix10MakeRotateERKNS_7CVectorEj', 'cmat_make_rotate', MR, [CV, I], 'fw'),
    ('_ZN9Framework7CMatrix11MakeRotateXEf', 'cmat_make_rotate_x', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix11MakeRotateYEf', 'cmat_make_rotate_y', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix11MakeRotateZEf', 'cmat_make_rotate_z', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix9MakeScaleERKNS_7CVectorE', 'cmat_make_scale', MR, [CV], 'fw'),
    ('_ZN9Framework7CMatrix10MakeScaleXEf', 'cmat_make_scale_x', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix10MakeScaleYEf', 'cmat_make_scale_y', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix10MakeScaleZEf', 'cmat_make_scale_z', MR, [F], 'fw'),
    ('_ZN9Framework7CMatrix18MakeLookAtMatrixZNERKNS_7CVectorES3_f', 'cmat_make_look_at_zn', MR, [CV, CV, F], 'fw'),
    ('_ZN9Framework7CMatrix20MakeLookAtMatrixZPUpERKNS_7CVectorES3_S3_f', 'cmat_make_look_at_zp_up', MR, [CV, CV, CV, F], 'fw'),
    ('_ZNK9Framework7CMatrix7IsLegalEv', 'cmat_is_legal', 'bool', [CM], 'fw'),
    ('_ZNK9Framework11CQuaternion6MatrixEv', 'cquat_matrix', MR, [CQ], 'fw'),
    ('_ZN9Framework11CQuaternion3SetERKNS_7CMatrixE', 'cquat_set', 'void', [Q, CM], 'fw'),
    ('_ZN9Framework11CQuaternion6CreateERKNS_7CVectorEf', 'cquat_create', 'void', [Q, CV, F], 'fw'),
    ('_ZN9Framework11CQuaternion6CreateERKNS_7CVectorES3_', 'cquat_create', 'void', [Q, CV, CV], 'fw'),
    ('_ZN9Framework7CVector22ToConstrainSelfInRangeERKS0_f', 'cvec_constrain_in_range', 'void', [V, CV, F], 'fw'),
    ('_ZN9Framework7CVector30ToConstrainSelfInRangeWithoutYERKS0_f', 'cvec_constrain_in_range_without_y', 'void', [V, CV, F], 'fw'),
    ('_ZN9Framework7CVector23ToConstrainSelfOutRangeERKS0_f', 'cvec_constrain_out_range', 'void', [V, CV, F], 'fw'),
    ('_ZN9Framework7CVector31ToConstrainSelfOutRangeWithoutYERKS0_f', 'cvec_constrain_out_range_without_y', 'void', [V, CV, F], 'fw'),
    ('_ZN9Framework7CVector15TransformNormalERKNS_7CMatrixE', 'cvec_transform_normal', 'void', [V, CM], 'fw'),
    ('_ZNK9Framework7CVector7IsLegalEv', 'cvec_is_legal', 'bool', [CV], 'fw'),
    # Aska::Vector (rest), Segment, Plane, AABB, Box, culling
    ('_ZN4Aska6Vector8GetEulerEPKNS_6MatrixE', 'vec_get_euler', 'void', [V, CM], 'geo'),
    ('_ZNK4Aska6Vector25SquaredDistanceToTriangleEPKS0_S2_S2_PS0_', 'vec_squared_distance_to_triangle', 'float', [CV, CV, CV, CV, V], 'geo'),
    ('_ZN4Aska6Vector17IsInsideWithAngleEPKS0_f', 'vec_is_inside_with_angle', 'bool', [V, CV, F], 'geo'),
    ('_ZNK4Aska7Segment15SquaredDistanceEPKNS_6VectorEPf', 'segment_squared_distance', 'float', [CVP, CV, V], 'geo'),
    ('_ZNK4Aska7Segment15SquaredDistanceEPKS0_PfS3_', 'segment_squared_distance', 'float', [CVP, CVP, V, V], 'geo'),
    ('_ZN4Aska5Plane11ApplyMatrixEPKNS_6MatrixE', 'plane_apply_matrix', 'void', [VP, CM], 'geo'),
    ('_ZNK4Aska5Plane15ComputeVerticesEPNS_6VectorEf', 'plane_compute_vertices', 'void', [CVP, VP, F], 'geo'),
    ('_ZN4Aska4AABB10SetCapsuleEPKNS_6VectorES3_f', 'aabb_set_capsule', 'void', [VP, CV, CV, F], 'geo'),
    ('_ZN4Aska4AABB16ClipIntersectionEPKS0_', 'aabb_clip_intersection', 'u64', [VP, CVP], 'geo'),
    ('_ZNK4Aska4AABB8SeparateERKNS_15OrthogonalPlaneEPS0_S4_', 'aabb_separate', 'bool', [CVP, OP, VP, VP], 'geo'),
    ('_ZN4Aska4AABB18SeparateByPositiveERKNS_15OrthogonalPlaneE', 'aabb_separate_by_positive', 'bool', [VP, OP], 'geo'),
    ('_ZN4Aska4AABB18SeparateByPositiveEif', 'aabb_separate_by_positive', 'bool', [VP, AX, F], 'geo'),
    ('_ZN4Aska4AABB18SeparateByNegativeERKNS_15OrthogonalPlaneE', 'aabb_separate_by_negative', 'bool', [VP, OP], 'geo'),
    ('_ZN4Aska4AABB18SeparateByNegativeEif', 'aabb_separate_by_negative', 'bool', [VP, AX, F], 'geo'),
    ('_ZN4Aska4AABB6SetBoxEPKNS_3BoxE', 'aabb_set_box', 'void', [VP, CVP], 'geo'),
    ('_ZN4Aska4AABB7SetConeEPKNS_6VectorES3_ff', 'aabb_set_cone', 'void', [VP, CV, CV, F, F], 'geo'),
    ('_ZN4Aska4AABB9SetSphereEPKNS_6SphereE', 'aabb_set_sphere', 'void', [VP, CVP], 'geo'),
    ('_ZNK4Aska4AABB11IsContainedEPKNS_6VectorEf', 'aabb_is_contained', 'bool', [CVP, CV, F], 'geo'),
    ('_ZNK4Aska4AABB12CalcDistanceEPKNS_5PlaneE', 'aabb_calc_distance', 'float', [CVP, CVP], 'geo'),
    ('_ZNK4Aska4AABB12CalcDistanceEPKNS_6VectorE', 'aabb_calc_distance', 'float', [CVP, CV], 'geo'),
    ('_ZNK4Aska11AABB_MinMax12CalcDistanceEPKNS_6VectorE', 'aabb_minmax_calc_distance', 'float', [CVP, CV], 'geo'),
    ('_ZNK4Aska4AABB15ComputeVerticesEPNS_6VectorE', 'aabb_compute_vertices', 'void', [CVP, VP], 'geo'),
    ('_ZNK4Aska4AABB15ComputeVerticesEPNS_6VectorEPKS1_', 'aabb_compute_vertices', 'void', [CVP, VP, CV], 'geo'),
    ('_ZNK4Aska4AABB15SquaredDistanceEPKNS_6VectorEPfS4_', 'aabb_squared_distance', 'float', [CVP, CV, V, V], 'geo'),
    ('_ZNK4Aska4AABB20CalcOverlappedStatusEPKNS_3BoxEf', 'aabb_calc_overlapped_status', 'int', [CVP, CVP, F], 'geo'),
    ('_ZNK4Aska4AABB20CalcOverlappedStatusEPKNS_6SphereEf', 'aabb_calc_overlapped_status_sphere', 'int', [CVP, CVP, F], 'geo'),
    ('_ZNK4Aska3Box7Case000EPNS_6VectorEPf', 'box_case000', 'void', [CVP, V, V], 'geo'),
    ('_ZNK4Aska3Box6Case00EiiiPNS_6VectorEPKS1_PfS5_', 'box_case00', 'void', [CVP, AX, AX, AX, V, CV, V, V], 'geo'),
    ('_ZNK4Aska3Box5Case0EiiiPNS_6VectorEPKS1_PfS5_', 'box_case0', 'void', [CVP, AX, AX, AX, V, CV, V, V], 'geo'),
    ('_ZNK4Aska3Box4FaceEiiiPNS_6VectorEPKS1_S4_PfS5_', 'box_face', 'void', [CVP, AX, AX, AX, V, CV, CV, V, V], 'geo'),
    ('_ZNK4Aska3Box11CaseNoZerosEPNS_6VectorEPKS1_PfS5_', 'box_case_no_zeros', 'void', [CVP, V, CV, V, V], 'geo'),
    ('_ZNK4Aska3Box15SquaredDistanceEPKNS_4LineEPfS4_S4_S4_', 'box_squared_distance_line', 'float', [CVP, CVP, V, V, V, V], 'geo'),
    ('_ZNK4Aska3Box15SquaredDistanceEPKNS_7SegmentEPfS4_S4_S4_', 'box_squared_distance_segment', 'float', [CVP, CVP, V, V, V, V], 'geo'),
    ('_ZNK4Aska3Box15SquaredDistanceEPKNS_6VectorEPfS4_S4_', 'box_squared_distance', 'float', [CVP, CV, V, V, V], 'geo'),
    ('_ZNK4Aska3Box15ComputeVerticesEPNS_6VectorE', 'box_compute_vertices', 'void', [CVP, VP], 'geo'),
    ('_ZNK4Aska3Box13ComputePlanesEPNS_5PlaneEb', 'box_compute_planes', 'void', [CVP, VP, BL], 'geo'),
    ('_ZNK4Aska3Box12CalcDistanceEPKNS_5PlaneE', 'box_calc_distance', 'float', [CVP, CVP], 'geo'),
    ('_ZNK4Aska3Box12CalcDistanceEPKNS_5PlaneEPKNS_6MatrixE', 'box_calc_distance', 'float', [CVP, CVP, CM], 'geo'),
    ('_ZNK4Aska3Box18CalcDistanceByAABBEPKNS_5PlaneEPKNS_6MatrixE', 'box_calc_distance_by_aabb', 'float', [CVP, CVP, CM], 'geo'),
    ('_ZNK4Aska3Box11IsContainedEPKNS_6VectorEPKNS_6MatrixEf', 'box_is_contained', 'bool', [CVP, CV, CM, F], 'geo'),
    ('_ZNK4Aska3Box20CalcOverlappedStatusEPKNS_6SphereEPKNS_6MatrixEf', 'box_calc_overlapped_status', 'int', [CVP, CVP, CM, F], 'geo'),
    ('_ZN4Aska3Box13IsIntersectedEPKS0_', 'box_is_intersected', 'bool', [VP, CVP], 'geo'),
    ('_ZN4Aska11AABBCullingEPNS_4AABBEPKNS_6VectorE', 'aabb_culling', 'bool', [VP, CVP], 'geo'),
    ('_ZN4Aska14FrustumCullingEPKNS_6VectorES2_PKNS_3BoxE', 'frustum_culling_box', 'bool', [CVP, CVP, CVP], 'geo'),
    ('_ZN4Aska14FrustumCullingEPKNS_6VectorES2_S2_', 'frustum_culling_sphere', 'bool', [CVP, CVP, CV], 'geo'),
    ('_ZN4Aska14FrustumCullingEPKNS_6VectorES2_S2_PKNS_3BoxE', 'frustum_culling_box', 'bool', [CVP, CVP, CV, CVP], 'geo'),
    ('_ZN4Aska14FrustumCullingEPKNS_6VectorES2_PKNS_11CullingConeE', 'frustum_culling_cone', 'bool', [CVP, CVP, CVP], 'geo'),
    ('_ZN4Aska14FrustumCullingEPKNS_6VectorES2_PKNS_15CullingCylinderE', 'frustum_culling_cylinder', 'bool', [CVP, CVP, CVP], 'geo'),
]


# Aska::Collision: the pure geometry tests (no CollisionHandler / INotify / result-info objects),
# generated from the export table. Return types come from the decompiler's signatures.
def collision_spec(mprefix='_ZN4Aska9Collision', dprefix='Aska::Collision::', cprefix='collision_', grp='col', extra_rets=None):
    import re as _re
    raw = subprocess.run(['nm', '-DS', genlib.lib_path()], capture_output=True, text=True).stdout.split('\n')
    rows = [l.split() for l in raw if f' T {mprefix}' in l]
    names = [r[3] for r in rows]
    dem = subprocess.run(['c++filt'], input='\n'.join(names), capture_output=True, text=True).stdout.split('\n')
    # return types, from the Ghidra decompile (tools/decomp.sh ... ' Aska::Collision::...')
    rets = {
        '_ZN4Aska9Collision12IntersectDotEPKNS_16CollisionHandlerEtPKNS_6VectorE': 'uint',
        '_ZN4Aska9Collision12IntersectDotEPKNS_3BoxEPKNS_6VectorE': 'bool',
        '_ZN4Aska9Collision12IntersectDotEPKNS_6VectorES3_': 'bool',
        '_ZN4Aska9Collision12IntersectDotEPKNS_7SegmentEfPKNS_6VectorE': 'bool',
        '_ZN4Aska9Collision17IntersectTriangleEPKNS_6VectorEPKNS_3RayE': 'bool',
        '_ZN4Aska9Collision17IntersectTriangleEPKNS_6VectorES3_PKNS_3RayE': 'bool',
        '_ZN4Aska9Collision18FindIntersectPointEPKNS_11AABB_MinMaxEPKNS_7SegmentEPPNS_6VectorE': 'long',
        '_ZN4Aska9Collision18FindIntersectPointEPKNS_4AABBEPKNS_7SegmentEPPNS_6VectorE': 'long',
        '_ZN4Aska9Collision18FindIntersectPointEPKNS_7SegmentEfPKNS_3RayEPPNS_6VectorE': 'ulong',
        '_ZN4Aska9Collision18FindIntersectPointEPKNS_7SegmentEfPKNS_4LineEPPNS_6VectorE': 'long',
        '_ZN4Aska9Collision19CalcSquaredDistanceEPKNS_6VectorES3_PS1_': 'void',
        '_ZN4Aska9Collision19CalcWeightMarginOBBEPKNS_3BoxES3_S3_': 'float',
        '_ZN4Aska9Collision22CalcWeightMarginSphereEPKNS_6VectorES3_S3_': 'float',
        '_ZN4Aska9Collision23CalcRoughIntersectPointEPKNS_3BoxEPKNS_6VectorEPS4_S7_': 'void',
        '_ZN4Aska9Collision23CalcRoughIntersectPointEPKNS_3BoxEPKNS_7SegmentEfPNS_6VectorES8_': 'void',
        '_ZN4Aska9Collision23CalcRoughIntersectPointEPKNS_3BoxES3_PNS_6VectorES5_': 'void',
        '_ZN4Aska9Collision23CalcRoughIntersectPointEPKNS_6VectorEPKNS_7SegmentEfPS1_S7_': 'void',
        '_ZN4Aska9Collision23CalcRoughIntersectPointEPKNS_6VectorES3_PS1_S4_': 'void',
        '_ZN4Aska9Collision23CalcRoughIntersectPointEPKNS_7SegmentEfS3_fPNS_6VectorES5_': 'void',
        '_ZN4Aska9Collision23FindRoughIntersectPointEPKNS_3BoxEPKNS_6VectorEPS4_S7_': 'bool',
        '_ZN4Aska9Collision23FindRoughIntersectPointEPKNS_3BoxEPKNS_7SegmentEfPNS_6VectorES8_': 'bool',
        '_ZN4Aska9Collision23FindRoughIntersectPointEPKNS_3BoxES3_PNS_6VectorES5_': 'bool',
        '_ZN4Aska9Collision23FindRoughIntersectPointEPKNS_6VectorEPKNS_7SegmentEfPS1_S7_': 'bool',
        '_ZN4Aska9Collision23FindRoughIntersectPointEPKNS_7SegmentEfS3_fPNS_6VectorES5_': 'bool',
        '_ZN4Aska9Collision28IntersectTriangleDoubleSidedEPKNS_6VectorEPKNS_3RayE': 'bool',
        '_ZN4Aska9Collision4ClipEffRfS1_': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxEPKNS_3BoxE': 'uint',
        '_ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxEPKNS_3RayE': 'undefined8',
        '_ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxEPKNS_6VectorE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxEPKNS_7SegmentE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_11AABB_MinMaxES3_': 'undefined8',
        '_ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_3BoxE': 'uint',
        '_ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_3RayE': 'uint',
        '_ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_4LineE': 'uint',
        '_ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_6VectorE': 'uint',
        '_ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtPKNS_7SegmentEf': 'uint',
        '_ZN4Aska9Collision9IntersectEPKNS_16CollisionHandlerEtS3_tPKNS_6MatrixE': 'uint',
        '_ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_3RayE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_4LineE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_6VectorE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_7SegmentE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_3BoxEPKNS_7SegmentEf': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_3BoxES3_': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_4AABBEPKNS_3RayE': 'undefined8',
        '_ZN4Aska9Collision9IntersectEPKNS_4AABBEPKNS_6VectorE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_4AABBEPKNS_7SegmentE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_3RayE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_4LineE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_7SegmentE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_6VectorEPKNS_7SegmentEf': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_6VectorES3_': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_7SegmentEfPKNS_3RayE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_7SegmentEfPKNS_4LineE': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_7SegmentEfS3_': 'bool',
        '_ZN4Aska9Collision9IntersectEPKNS_7SegmentEfS3_f': 'bool',
    }
    out_ = []
    for r, d in zip(rows, dem):
        sym, size = r[3], int(r[1], 16)
        if size < 8 or any(k in d for k in ('CollisionHandler', 'INotify', 'IntersectInfo')):
            continue
        name = d[len(dprefix):d.index('(')]
        argstr = d[d.index('(') + 1:d.rindex(')')]
        args = []
        for a in [x.strip() for x in argstr.split(',') if x.strip()]:
            if a == 'float':
                args.append(F)
            elif a.endswith('**'):
                args.append(PP)
            elif a.endswith('const*'):
                args.append(CVP)
            elif a.endswith('*') or a.endswith('&') or '(&)' in a:
                args.append(VP)
            else:
                raise ValueError(a)
        if extra_rets:
            rets.update(extra_rets)
        rt = {'bool': 'bool', 'uint': 'uint32_t', 'float': 'float', 'void': 'void', None: 'void'}.get(rets.get(sym), 'u64')
        def tshort(a):
            a = _re.sub(r'\(&\) \[(\d+)\]', r'x\1', a)
            a = a.replace('const', '').replace('*', '').replace('&', '').replace(' ', '').strip()
            return 'f' if a == 'float' else a.split('::')[-1].lower()
        suffix = '_'.join(tshort(a) for a in argstr.split(',') if a.strip())
        cname = cprefix + _re.sub(r'(?<!^)(?=[A-Z])', '_', name).lower() + '_' + suffix
        out_.append((sym, cname, rt, args, grp))
    return out_


SPEC += collision_spec()
# Framework::CCollision: the shape-vs-shape IsIntersect overloads (they wrap Aska::Collision).
SPEC += collision_spec('_ZN9Framework10CCollision', 'Framework::CCollision::', 'fwcollision_', 'fwcol', {
        '_ZN9Framework10CCollision11IsIntersectERKN4Aska16CollisionHandlerEtRKNS_4CRayE': 'void',
        '_ZN9Framework10CCollision11IsIntersectERKN4Aska16CollisionHandlerEtRKNS_7CSphereE': 'uint',
        '_ZN9Framework10CCollision11IsIntersectERKN4Aska16CollisionHandlerEtRKNS_8CSegmentE': 'undefined8',
        '_ZN9Framework10CCollision11IsIntersectERKN4Aska16CollisionHandlerEtRKNS_8CSegmentEf': 'void',
        '_ZN9Framework10CCollision11IsIntersectERKNS_4CBoxERKNS_4CRayERA2_NS_7CVectorERi': 'bool',
        '_ZN9Framework10CCollision11IsIntersectERKNS_4CBoxERKNS_7CSphereERNS_7CVectorES8_': 'uint',
        '_ZN9Framework10CCollision11IsIntersectERKNS_4CBoxERKNS_8CSegmentERA2_NS_7CVectorERi': 'bool',
        '_ZN9Framework10CCollision11IsIntersectERKNS_4CBoxERKNS_8CSegmentEfRA2_NS_7CVectorERi': 'uint',
        '_ZN9Framework10CCollision11IsIntersectERKNS_4CBoxES3_RA4_NS_7CVectorERS4_': 'uint',
        '_ZN9Framework10CCollision11IsIntersectERKNS_7CSphereERKNS_4CRayERA2_NS_7CVectorERi': 'bool',
        '_ZN9Framework10CCollision11IsIntersectERKNS_7CSphereERKNS_8CSegmentERA2_NS_7CVectorERi': 'bool',
        '_ZN9Framework10CCollision11IsIntersectERKNS_7CSphereERKNS_8CSegmentEfRNS_7CVectorE': 'uint',
        '_ZN9Framework10CCollision11IsIntersectERKNS_7CSphereES3_': 'uint',
        '_ZN9Framework10CCollision11IsIntersectERKNS_7CSphereES3_RNS_7CVectorE': 'uint',
        '_ZN9Framework10CCollision11IsIntersectERKNS_8CSegmentEfRKNS_4CRayERA2_NS_7CVectorERi': 'bool',
        '_ZN9Framework10CCollision11IsIntersectERKNS_8CSegmentEfS3_RA2_NS_7CVectorERi': 'bool',
        '_ZN9Framework10CCollision11IsIntersectERKNS_8CSegmentEfS3_fRNS_7CVectorE': 'uint',
})

if len(sys.argv) > 2:
    SPEC = [s for s in SPEC if s[4] in sys.argv[2].split(',')]


# Symbols with a readable (hand-written) implementation in port/src/native/engine/math/aska_math_rd*.cpp
# (registered there with RD("sym", fn) / RD_SRET): their transcription is still emitted (it is
# the second reference of the 3-way test in aska_math_test.cpp and reachable via a2c_hook_for),
# but neither the typed entry point nor the guest hook registration.
import glob as _glob
import re as _re2_mod
READABLE = set()
for _f in _glob.glob(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'port/src/native/engine/math/aska_math_rd*.cpp')):
    READABLE |= set(_re2_mod.findall(r'\bRDO?(?:_SRET)?\("(\w+)"', open(_f).read()))


def c_sig(name, ret, args):
    params = []
    if ret == 'Vec4@x8':
        params.append('Vec4* result')
    if ret == 'Mat44@x8':
        params.append('Mat44* result')
    for k, a in enumerate(args):
        params.append(f'{a} a{k}')
    rt = 'void' if ret in ('void', 'Vec4@x8', 'Mat44@x8') else 'uint64_t' if ret == 'u64' else ret
    return rt, f'{name}({", ".join(params)})'


out = []
out.append('''// GENERATED by tools/gen_aska_math_a2c.py (a2c.py) from libSOA.so's ARM64 code: do not edit by hand; regenerate.
// ''' + genlib.stamp() + '''
//
// Aska engine math, native (part 2): Aska::Matrix / Matrix34 operations, MatrixCalcFunc and colour
// packing, transcribed instruction by instruction (see aska_math_a2c.h for why and how). Each
// function has a typed C++ entry point (declared in aska_math.h) and a guest hook; tests are in
// aska_math_test.cpp.
#pragma GCC optimize("fp-contract=off")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wuninitialized"
#include <cstdlib>
#include <cstring>
#include <string>

#include <soa/env.h>

#include "soaruntime/core/cpu.h"
#include "native/engine/math/aska_math.h"
#include "native/engine/math/aska_math_a2c.h"
#include "native/common/native.h"

namespace soa::aska {
namespace {
using namespace a2c;
using a2c::u64;
using detail::count_call;
using detail::HookCounter;
// Debugging switches (environment, port/README.md "Environment"; read through soa/env.h):
// SOA_ASKA_MATH_OFF="grp,grp" disables groups (mat, mat34, vec, fw, geo); SOA_ASKA_MATH_SKIP=
// "sym1,sym2" disables single mangled symbols (for bisecting).
bool a2c_group_on(const char* g) {
    for (auto& off : ::soa::env::env_list("SOA_ASKA_MATH_OFF"))
        if (off == g) return false;
    return true;
}
bool a2c_sym_on(const char* g, const char* sym) {
    if (!a2c_group_on(g)) return false;
    const char* e = ::soa::env::env_str("SOA_ASKA_MATH_SKIP");
    return !(e && strstr(e, sym));
}
}  // namespace
''')
decls = []
seen = {}
tnames = []
for sym, name, ret, args, grp in SPEC:
    cnt = seen.get(name, 0)
    seen[name] = cnt + 1
    tnames.append(f't_{name}_{cnt}')
    a2c.EXTRA_CALLS[sym] = f't_{name}_{cnt}(r);'
# Bodies of 4-byte tail-call trampolines ("SYM+0x4": unnamed local functions) are transcribed
# too, discovered by translating everything once and collecting the unresolved call targets.
import re as _re2
_syms_sorted = sorted(v[0] for v in a2c.syms.values())
def _extent(addr):
    import bisect
    i = bisect.bisect_right(_syms_sorted, addr)
    return _syms_sorted[i] - addr if i < len(_syms_sorted) else 0x400
locals_ = {}
while True:
    missing = set()
    for sym, name, ret, args, grp in SPEC:
        body = a2c.translate(sym, 'x')
        missing |= set(_re2.findall(r'#error "a2c: (?:tail )?call ([A-Za-z0-9_]+\+0x4):', body))
    for (addr, sz) in list(locals_.values()):
        body = a2c.translate(f'0x{addr:x}:{sz:x}', 'x')
        missing |= set(_re2.findall(r'#error "a2c: (?:tail )?call ([A-Za-z0-9_]+\+0x4):', body))
    # calls to exported 4-byte trampolines ("b SYM+4"): call the body directly
    for sym, name, ret, args, grp in SPEC:
        body = a2c.translate(sym, 'x')
        for t in _re2.findall(r'#error "a2c: (?:tail )?call ([A-Za-z0-9_]+):', body):
            if t in a2c.syms and a2c.syms[t][1] == 4 and t not in a2c.EXTRA_CALLS:
                addr = a2c.syms[t][0] + 4
                key = f'{t}+0x4'
                locals_.setdefault(key, (addr, _extent(addr)))
                a2c.EXTRA_CALLS[key] = f't_local_{addr:x}(r);'
                a2c.EXTRA_CALLS[t] = f't_local_{addr:x}(r);'
                missing.add('changed')
    missing -= set(locals_)
    if not missing:
        break
    for m in missing:
        if m == 'changed':
            continue
        base = a2c.syms[m.split('+')[0]][0]
        addr = base + 4
        locals_[m] = (addr, _extent(addr))
        a2c.EXTRA_CALLS[m] = f't_local_{addr:x}(r);'
_bad = [e for e in SPEC if '#error' in a2c.translate(e[0], 'x')]
for e in _bad:
    print(f'NOTE: {e[0]} not transcribable (unsupported instruction or call); left to the JIT', file=sys.stderr)
SPEC = [e for e in SPEC if e not in _bad]
_seen_n = {}
tnames = []
for sym, name, ret, args, grp in SPEC:
    cnt = _seen_n.get(name, 0)
    _seen_n[name] = cnt + 1
    tnames.append(f't_{name}_{cnt}')
    a2c.EXTRA_CALLS[sym] = f't_{name}_{cnt}(r);'
for e in _bad:
    a2c.EXTRA_CALLS.pop(e[0], None)
for tn in tnames:
    out.append(f'static void {tn}(A64& r);')
for m, (addr, sz) in sorted(locals_.items(), key=lambda kv: kv[1][0]):
    out.append(f'static void t_local_{addr:x}(A64& r);')
for m, (addr, sz) in sorted(locals_.items(), key=lambda kv: kv[1][0]):
    out.append(f'// local function behind the {m.split("+")[0]} trampoline')
    out.append(f'static void t_local_{addr:x}(A64& r) {{')
    out.append('    u64 jt_ = 0;')
    out.append('    (void)jt_;')
    out.append(a2c.translate(f'0x{addr:x}:{sz:x}', f't_local_{addr:x}').rstrip())
    out.append('}')
seen = {}
for sym, name, ret, args, grp in SPEC:
    cnt = seen.get(name, 0)
    seen[name] = cnt + 1
    tname = f't_{name}_{cnt}'
    body = a2c.translate(sym, tname)
    if '#error' in body:
        print(f'WARNING: {sym} has untranslated instructions', file=sys.stderr)
    out.append(f'static void {tname}(A64& r) {{')
    out.append('    u64 jt_ = 0;')
    out.append('    (void)jt_;')
    out.append(body.rstrip())
    out.append('}')
    rt, sig = c_sig(name, ret, args)
    decls.append(f'{rt} {sig};')
    readable = sym in READABLE
    # typed entry point
    lines = [f'{rt} {sig} {{', '    A64 r;', '    alignas(16) unsigned char stack_[2048];', '    r.x[31] = (u64)(stack_ + sizeof stack_);']
    xi = si = 0
    if ret in ('Vec4@x8', 'Mat44@x8'):
        lines.append('    r.x[8] = (u64)result;')
    for k, a in enumerate(args):
        if a == F:
            lines.append(f'    r.v[{si}] = V4{{{{a{k}, 0, 0, 0}}}};')
            si += 1
        elif a in (I, U, AX, ROW, BL):
            lines.append(f'    r.x[{xi}] = (u64)(uint32_t)a{k};')
            xi += 1
        else:
            if xi >= 8:  # stack argument
                lines.append(f'    std::memcpy((void*)(r.x[31] + {8 * (xi - 8)}), &a{k}, 8);')
            else:
                lines.append(f'    r.x[{xi}] = (u64)a{k};')
            xi += 1
    if xi > 8:
        lines.insert(4, f'    r.x[31] -= {((xi - 8) * 8 + 15) // 16 * 16};')
    lines.append(f'    {tname}(r);')
    if ret == 'bool':
        lines.append('    return r.x[0] & 1;')
    elif ret in ('uint32_t', 'int'):
        lines.append(f'    return ({ret})r.x[0];')
    elif ret == 'u64':
        lines.append('    return r.x[0];')
    elif ret == 'float':
        lines.append('    return r.v[0].f[0];')
    lines.append('}')
    if not readable:
        out.extend(lines)
    # hook
    # Hook: load the argument registers (and x0/v0), run on the guest stack, write back x0/v0.
    h = [f'static HookCounter cnt_{tname}("{sym}");',
         f'static void h_{tname}(Cpu& c) {{', f'    count_call(cnt_{tname});', '    A64 r;',
         '    r.x[31] = c.sp();  // runs on the guest stack, like the original']
    xi = si = 0
    if ret in ('Vec4@x8', 'Mat44@x8'):
        h.append('    r.x[8] = c.x(8);')
    for a in args:
        if a == F:
            h.append(f'    {{ V128 q = c.v({si}); std::memcpy(&r.v[{si}], &q, 16); }}')
            si += 1
        else:
            if xi < 8:
                h.append(f'    r.x[{xi}] = c.x({xi});')
            xi += 1
    if xi == 0:
        h.append('    r.x[0] = c.x(0);')
    if si == 0:
        h.append('    { V128 q = c.v(0); std::memcpy(&r.v[0], &q, 16); }')
    h.append(f'    {tname}(r);')
    # x0 and v0 are written back whatever the declared return type: the transcribed body leaves
    # them exactly as the original would, so an undeclared result can't be lost.
    h.append('    c.set_x(0, r.x[0]);')
    h.append('    { V128 q; std::memcpy(&q, &r.v[0], 16); c.set_v(0, q); }')
    h.append('}')
    if readable:
        h.append(f'// {sym}: registered by its readable version (aska_math_rd*.cpp)')
    else:
        h.append(f'static bool on_{tname}() {{ return a2c_sym_on("{grp}", "{sym}"); }}')
        h.append(f'NATIVE_FUNCTION_IF("{sym}", h_{tname}, "aska math", on_{tname});')
    out.extend(h)
# test table: kinds per argument, the guest symbol, and an invoker running the transcribed body
kinds = {M: 'M', CM: 'M', V: 'V', CV: 'V', Q: 'Q', CQ: 'Q', M34: '3', CM34: '3', F: 'f', I: 'i', U: 'u',
         VP: 'X', CVP: 'X', PP: 'P', OP: 'O', AX: 'a', ROW: 'r', BL: 'z'}
# hook lookup (benchmarks)
out.append('HostFn a2c_hook_for(const char* sym) {')
seen3 = {}
for sym, name, ret, args, grp in SPEC:
    cnt = seen3.get(name, 0)
    seen3[name] = cnt + 1
    out.append(f'    if (!strcmp(sym, "{sym}")) return h_t_{name}_{cnt};')
out.append('    return nullptr;')
out.append('}')
out.append('const A2cTest* a2c_tests(int* n) {')
out.append('    static const A2cTest t[] = {')
seen2 = {}
for sym, name, ret, args, grp in SPEC:
    cnt = seen2.get(name, 0)
    seen2[name] = cnt + 1
    tname = f't_{name}_{cnt}'
    ks = ''.join(kinds[a] for a in args)
    if sum(1 for a in args if a != F) > 8:
        continue  # stack arguments: covered through its callers
    rk = {'void': 'v', 'bool': 'b', 'uint32_t': 'u', 'int': 'u', 'float': 'f', 'Vec4@x8': 'V', 'Mat44@x8': 'M', 'u64': '*'}[ret]
    out.append(f'        {{"{sym}", "{ks}", \'{rk}\', [](const uint64_t* x, const float* s, uint64_t x8, uint64_t* x0, float* s0) {{')
    out.append('             A64 r; alignas(16) unsigned char stack_[2048]; r.x[31] = (u64)(stack_ + sizeof stack_);')
    out.append('             for (int i = 0; i < 8; i++) r.x[i] = x[i], r.v[i] = V4{{s[i], 0, 0, 0}};')
    out.append(f'             r.x[8] = x8; {tname}(r); *x0 = r.x[0]; *s0 = r.v[0].f[0]; }}}},')
out.append('    };')
out.append('    *n = sizeof t / sizeof t[0];')
out.append('    return t;')
out.append('}')
out.append('}  // namespace soa::aska')
open(OUT, 'w').write('\n'.join(out) + '\n')
open(OUT.replace('.cpp', '.decls.txt'), 'w').write('\n'.join(decls) + '\n') if os.environ.get('A2C_DECLS') else None
