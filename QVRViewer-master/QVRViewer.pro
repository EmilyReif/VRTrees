#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T00:52:41
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = QVRViewer
TEMPLATE = app


SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/vrview.cpp \
    src/databinding.cpp \
    src/forestmaker.cpp \
    src/glwidget.cpp \
    src/settings.cpp \
    cs123_lib/errorchecker.cpp \
    cs123_lib/resourceloader.cpp \
    lsystem/lsystemgenerator.cpp \
    shapes/Cap.cpp \
    shapes/Cone.cpp \
    shapes/Cylinder.cpp \
    shapes/lsystemtree.cpp \
    shapes/ModeratelyComplexShape.cpp \
    shapes/OpenGLShape.cpp \
    shapes/Sphere.cpp \
    shapes/Square.cpp \
    shapes/Torus.cpp \
    src/glib/datatype/FBO.cpp \
    src/glib/datatype/IBO.cpp \
    src/glib/datatype/VAO.cpp \
    src/glib/datatype/VBO.cpp \
    src/glib/datatype/VBOAttribMarker.cpp \
    src/glib/textures/DepthBuffer.cpp \
    src/glib/textures/RenderBuffer.cpp \
    src/glib/textures/Texture.cpp \
    src/glib/textures/Texture2D.cpp \
    src/glib/textures/TextureParameters.cpp \
    src/glib/textures/TextureParametersBuilder.cpp \
    src/glib/GLDebug.cpp \
    extern/glew/src/glew.c \
    terrain/terrain.cpp \
    terrain/terrainshape.cpp \
    debug/moc_databinding.cpp \
    debug/moc_glwidget.cpp \
    debug/moc_mainwindow.cpp \
    debug/moc_vrview.cpp \
    debug/qrc_resources.cpp \
    debug/qrc_shaders.cpp \
    extern/openvr/samples/driver_sample/driver_sample.cpp \
    extern/openvr/samples/driver_sample/driverlog.cpp \
    extern/openvr/samples/hellovr_opengl/hellovr_opengl_main.cpp \
    extern/openvr/samples/helloworldoverlay/main.cpp \
    extern/openvr/samples/helloworldoverlay/openvroverlaycontroller.cpp \
    extern/openvr/samples/helloworldoverlay/overlaywidget.cpp \
    extern/openvr/samples/shared/lodepng.cpp \
    extern/openvr/samples/shared/Matrices.cpp \
    extern/openvr/samples/shared/pathtools.cpp \
    extern/openvr/samples/tracked_camera_openvr_sample/main.cpp \
    extern/openvr/samples/tracked_camera_openvr_sample/tracked_camera_openvr_sample.cpp \
    extern/openvr/src/vrcommon/dirtools_public.cpp \
    extern/openvr/src/vrcommon/envvartools_public.cpp \
    extern/openvr/src/vrcommon/hmderrors_public.cpp \
    extern/openvr/src/vrcommon/pathtools_public.cpp \
    extern/openvr/src/vrcommon/sharedlibtools_public.cpp \
    extern/openvr/src/vrcommon/strtools_public.cpp \
    extern/openvr/src/vrcommon/vrpathregistry_public.cpp \
    extern/openvr/src/jsoncpp.cpp \
    extern/openvr/src/openvr_api_public.cpp \
    glm/detail/dummy.cpp \
    glm/detail/glm.cpp \
    src/mainwindow.bak.cpp \
    extern/glew/auto/src/glew_head.c \
    extern/glew/auto/src/glew_init_gl.c \
    extern/glew/auto/src/glew_init_glx.c \
    extern/glew/auto/src/glew_init_tail.c \
    extern/glew/auto/src/glew_init_wgl.c \
    extern/glew/auto/src/glew_str_glx.c \
    extern/glew/auto/src/glew_str_head.c \
    extern/glew/auto/src/glew_str_tail.c \
    extern/glew/auto/src/glew_str_wgl.c \
    extern/glew/auto/src/glew_utils.c \
    extern/glew/auto/src/glewinfo_gl.c \
    extern/glew/auto/src/glewinfo_glx.c \
    extern/glew/auto/src/glewinfo_head.c \
    extern/glew/auto/src/glewinfo_tail.c \
    extern/glew/auto/src/glewinfo_wgl.c \
    extern/glew/src/glewinfo.c \
    extern/glew/src/visualinfo.c

HEADERS  += src/mainwindow.h \
    src/modelformats.h \
    src/vrview.h \
    src/databinding.h \
    src/forestmaker.h \
    src/glwidget.h \
    src/settings.h \
    cs123_lib/errorchecker.h \
    cs123_lib/resourceloader.h \
    cs123_lib/sphere.h \
    lsystem/lsystemgenerator.h \
    shapes/Cap.h \
    shapes/Cone.h \
    shapes/Cylinder.h \
    shapes/lsystemtree.h \
    shapes/ModeratelyComplexShape.h \
    shapes/OpenGLShape.h \
    shapes/Sphere.h \
    shapes/Square.h \
    shapes/Torus.h \
    src/glib/datatype/FBO.h \
    src/glib/datatype/IBO.h \
    src/glib/datatype/VAO.h \
    src/glib/datatype/VBO.h \
    src/glib/datatype/VBOAttribMarker.h \
    src/glib/shaders/ShaderAttribLocations.h \
    src/glib/textures/DepthBuffer.h \
    src/glib/textures/RenderBuffer.h \
    src/glib/textures/Texture.h \
    src/glib/textures/Texture2D.h \
    src/glib/textures/TextureParameters.h \
    src/glib/textures/TextureParametersBuilder.h \
    src/glib/GLDebug.h \
    terrain/terrain.h \
    terrain/terrainshape.h \
    extern/glew/auto/src/glew_head.h \
    extern/glew/auto/src/glew_license.h \
    extern/glew/auto/src/glew_tail.h \
    extern/glew/auto/src/glew_utils.h \
    extern/glew/auto/src/glxew_head.h \
    extern/glew/auto/src/glxew_mid.h \
    extern/glew/auto/src/glxew_tail.h \
    extern/glew/auto/src/khronos_license.h \
    extern/glew/auto/src/mesa_license.h \
    extern/glew/auto/src/wglew_head.h \
    extern/glew/auto/src/wglew_mid.h \
    extern/glew/auto/src/wglew_tail.h \
    extern/glew/include/GL/glew.h \
    extern/glew/include/GL/glxew.h \
    extern/glew/include/GL/wglew.h \
    extern/openvr/headers/openvr.h \
    extern/openvr/headers/openvr_capi.h \
    extern/openvr/headers/openvr_driver.h \
    extern/openvr/samples/driver_sample/driverlog.h \
    extern/openvr/samples/helloworldoverlay/openvroverlaycontroller.h \
    extern/openvr/samples/helloworldoverlay/overlaywidget.h \
    extern/openvr/samples/shared/compat.h \
    extern/openvr/samples/shared/lodepng.h \
    extern/openvr/samples/shared/Matrices.h \
    extern/openvr/samples/shared/pathtools.h \
    extern/openvr/samples/shared/Vectors.h \
    extern/openvr/samples/thirdparty/glew/glew-1.11.0/include/GL/glew.h \
    extern/openvr/samples/thirdparty/glew/glew-1.11.0/include/GL/glxew.h \
    extern/openvr/samples/thirdparty/glew/glew-1.11.0/include/GL/wglew.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/begin_code.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/close_code.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_assert.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_atomic.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_audio.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_bits.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_blendmode.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_clipboard.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_android.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_iphoneos.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_macosx.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_minimal.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_pandora.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_psp.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_windows.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_winrt.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_config_wiz.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_copying.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_cpuinfo.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_egl.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_endian.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_error.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_events.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_filesystem.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_gamecontroller.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_gesture.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_haptic.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_hints.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_joystick.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_keyboard.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_keycode.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_loadso.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_log.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_main.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_messagebox.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_mouse.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_mutex.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_name.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_opengl.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_opengles.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_opengles2.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_pixels.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_platform.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_power.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_quit.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_rect.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_render.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_revision.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_rwops.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_scancode.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_shape.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_stdinc.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_surface.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_system.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_syswm.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_assert.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_common.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_compare.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_crc32.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_font.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_fuzzer.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_harness.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_images.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_log.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_md5.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_test_random.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_thread.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_timer.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_touch.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_types.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_version.h \
    extern/openvr/samples/thirdparty/sdl2-2.0.3/include/SDL_video.h \
    extern/openvr/samples/tracked_camera_openvr_sample/tracked_camera_openvr_sample.h \
    extern/openvr/src/json/json-forwards.h \
    extern/openvr/src/json/json.h \
    extern/openvr/src/vrcommon/dirtools.h \
    extern/openvr/src/vrcommon/envvartools.h \
    extern/openvr/src/vrcommon/hmderrors.h \
    extern/openvr/src/vrcommon/pathtools.h \
    extern/openvr/src/vrcommon/sharedlibtools.h \
    extern/openvr/src/vrcommon/strtools.h \
    extern/openvr/src/vrcommon/vrpathregistry.h \
    extern/openvr/src/ivrclientcore.h \
    glm/detail/_features.hpp \
    glm/detail/_fixes.hpp \
    glm/detail/_literals.hpp \
    glm/detail/_noise.hpp \
    glm/detail/_swizzle.hpp \
    glm/detail/_swizzle_func.hpp \
    glm/detail/_vectorize.hpp \
    glm/detail/func_common.hpp \
    glm/detail/func_exponential.hpp \
    glm/detail/func_geometric.hpp \
    glm/detail/func_integer.hpp \
    glm/detail/func_matrix.hpp \
    glm/detail/func_noise.hpp \
    glm/detail/func_packing.hpp \
    glm/detail/func_trigonometric.hpp \
    glm/detail/func_vector_relational.hpp \
    glm/detail/hint.hpp \
    glm/detail/intrinsic_common.hpp \
    glm/detail/intrinsic_exponential.hpp \
    glm/detail/intrinsic_geometric.hpp \
    glm/detail/intrinsic_integer.hpp \
    glm/detail/intrinsic_matrix.hpp \
    glm/detail/intrinsic_trigonometric.hpp \
    glm/detail/intrinsic_vector_relational.hpp \
    glm/detail/precision.hpp \
    glm/detail/setup.hpp \
    glm/detail/type_float.hpp \
    glm/detail/type_gentype.hpp \
    glm/detail/type_half.hpp \
    glm/detail/type_int.hpp \
    glm/detail/type_mat.hpp \
    glm/detail/type_mat2x2.hpp \
    glm/detail/type_mat2x3.hpp \
    glm/detail/type_mat2x4.hpp \
    glm/detail/type_mat3x2.hpp \
    glm/detail/type_mat3x3.hpp \
    glm/detail/type_mat3x4.hpp \
    glm/detail/type_mat4x2.hpp \
    glm/detail/type_mat4x3.hpp \
    glm/detail/type_mat4x4.hpp \
    glm/detail/type_vec.hpp \
    glm/detail/type_vec1.hpp \
    glm/detail/type_vec2.hpp \
    glm/detail/type_vec3.hpp \
    glm/detail/type_vec4.hpp \
    glm/gtc/constants.hpp \
    glm/gtc/epsilon.hpp \
    glm/gtc/matrix_access.hpp \
    glm/gtc/matrix_integer.hpp \
    glm/gtc/matrix_inverse.hpp \
    glm/gtc/matrix_transform.hpp \
    glm/gtc/noise.hpp \
    glm/gtc/packing.hpp \
    glm/gtc/quaternion.hpp \
    glm/gtc/random.hpp \
    glm/gtc/reciprocal.hpp \
    glm/gtc/type_precision.hpp \
    glm/gtc/type_ptr.hpp \
    glm/gtc/ulp.hpp \
    glm/gtx/associated_min_max.hpp \
    glm/gtx/bit.hpp \
    glm/gtx/closest_point.hpp \
    glm/gtx/color_space.hpp \
    glm/gtx/color_space_YCoCg.hpp \
    glm/gtx/compatibility.hpp \
    glm/gtx/component_wise.hpp \
    glm/gtx/constants.hpp \
    glm/gtx/dual_quaternion.hpp \
    glm/gtx/epsilon.hpp \
    glm/gtx/euler_angles.hpp \
    glm/gtx/extend.hpp \
    glm/gtx/extented_min_max.hpp \
    glm/gtx/fast_exponential.hpp \
    glm/gtx/fast_square_root.hpp \
    glm/gtx/fast_trigonometry.hpp \
    glm/gtx/gradient_paint.hpp \
    glm/gtx/handed_coordinate_space.hpp \
    glm/gtx/inertia.hpp \
    glm/gtx/int_10_10_10_2.hpp \
    glm/gtx/integer.hpp \
    glm/gtx/intersect.hpp \
    glm/gtx/io.hpp \
    glm/gtx/log_base.hpp \
    glm/gtx/matrix_cross_product.hpp \
    glm/gtx/matrix_interpolation.hpp \
    glm/gtx/matrix_major_storage.hpp \
    glm/gtx/matrix_operation.hpp \
    glm/gtx/matrix_query.hpp \
    glm/gtx/mixed_product.hpp \
    glm/gtx/multiple.hpp \
    glm/gtx/noise.hpp \
    glm/gtx/norm.hpp \
    glm/gtx/normal.hpp \
    glm/gtx/normalize_dot.hpp \
    glm/gtx/number_precision.hpp \
    glm/gtx/optimum_pow.hpp \
    glm/gtx/orthonormalize.hpp \
    glm/gtx/perpendicular.hpp \
    glm/gtx/polar_coordinates.hpp \
    glm/gtx/projection.hpp \
    glm/gtx/quaternion.hpp \
    glm/gtx/random.hpp \
    glm/gtx/raw_data.hpp \
    glm/gtx/reciprocal.hpp \
    glm/gtx/rotate_normalized_axis.hpp \
    glm/gtx/rotate_vector.hpp \
    glm/gtx/scalar_relational.hpp \
    glm/gtx/simd_mat4.hpp \
    glm/gtx/simd_quat.hpp \
    glm/gtx/simd_vec4.hpp \
    glm/gtx/spline.hpp \
    glm/gtx/std_based_type.hpp \
    glm/gtx/string_cast.hpp \
    glm/gtx/transform.hpp \
    glm/gtx/transform2.hpp \
    glm/gtx/ulp.hpp \
    glm/gtx/unsigned_int.hpp \
    glm/gtx/vec1.hpp \
    glm/gtx/vector_angle.hpp \
    glm/gtx/vector_query.hpp \
    glm/gtx/wrap.hpp \
    glm/virtrev/xstream.hpp \
    glm/common.hpp \
    glm/exponential.hpp \
    glm/ext.hpp \
    glm/fwd.hpp \
    glm/geometric.hpp \
    glm/glm.hpp \
    glm/integer.hpp \
    glm/mat2x2.hpp \
    glm/mat2x3.hpp \
    glm/mat2x4.hpp \
    glm/mat3x2.hpp \
    glm/mat3x3.hpp \
    glm/mat3x4.hpp \
    glm/mat4x2.hpp \
    glm/mat4x3.hpp \
    glm/mat4x4.hpp \
    glm/matrix.hpp \
    glm/packing.hpp \
    glm/trigonometric.hpp \
    glm/vec2.hpp \
    glm/vec3.hpp \
    glm/vec4.hpp \
    glm/vector_relational.hpp \
    src/mainwindow.bak.h \
    ui_mainwindow.h

FORMS    += src/mainwindow.ui

DEFINES +=  _CRT_NO_VA_START_VALIDATION
DEFINES += GLEW_STATIC
DEFINES += GLM_SWIZZLE GLM_FORCE_RADIANS



# from http://stackoverflow.com/a/10058744
# Copies the given files to the destination directory
defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        CONFIG( debug, debug|release ) {
            DDIR = $${OUT_PWD}/debug
        } else {
            DDIR = $${OUT_PWD}/release
        }

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}


win32 {
    RC_FILE = win32.rc

    contains(QT_ARCH, i386) {
message("32 bit build")
        LIBS += -L$$PWD/extern/openvr/lib/win32/ \
                -lopenvr_api -lopengl32 -lglu32
        copyToDestdir($${PWD}/extern/openvr/bin/win32/openvr_api.dll)
    } else {
message("64 bit build")
        LIBS += -L$$PWD/extern/openvr/lib/win64/ \
                -lopenvr_api -lopengl32 -lglu32
        copyToDestdir($${PWD}/extern/openvr/bin/win64/openvr_api.dll)
    }
}

INCLUDEPATH += $$PWD/extern/openvr/headers $$PWD/extern/glew/include
INCLUDEPATH += glm
DEPENDPATH += glm


# from http://stackoverflow.com/a/25193580
isEmpty(TARGET_EXT) {
    win32 {
        TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

win32 {
    DEPLOY_COMMAND = windeployqt
}
macx {
    DEPLOY_COMMAND = macdeployqt
}

CONFIG( debug, debug|release ) {
    # debug
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/debug/$${TARGET}$${TARGET_CUSTOM_EXT}))
} else {
    # release
    DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}$${TARGET_CUSTOM_EXT}))
}

QMAKE_POST_LINK += $${DEPLOY_COMMAND} $${DEPLOY_TARGET} $$escape_expand(\\n\\t)

RESOURCES += \
    resources.qrc \
    shaders/shaders.qrc \
    images/images.qrc

DISTFILES += \
    win32.rc \
    viewer.ico \
    shaders/deferredShadingFirst.frag \
    shaders/deferredShadingSecond.frag \
    shaders/deferredShadingFirst.vert \
    shaders/quad.vert
