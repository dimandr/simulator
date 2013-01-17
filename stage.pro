VPATH += ../stage
INCLUDEPATH += \
                VPATH/libstage \
                VPATH/libstage/alhoritm \
                VPATH/libstage/alhoritm/astar \

QT           += \
            opengl

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS hellogl.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)

SOURCES += \
    window.cpp \
    qtlogo.cpp \
    glwidget.cpp \
    libstage/worldfile.cc \
    libstage/worldgui.cc \
    libstage/world.cc \
    libstage/vis_strip.cc \
    libstage/typetable.cc \
    libstage/texture_manager.cc \
    libstage/stage.cc \
    libstage/region.cc \
    libstage/powerpack.cc \
    libstage/model_ranger.cc \
    libstage/model_position.cc \
    libstage/model_lightindicator.cc \
    libstage/model_gripper.cc \
    libstage/model_fiducial.cc \
    libstage/model_draw.cc \
    libstage/model_camera.cc \
    libstage/model_callbacks.cc \
    libstage/model_blobfinder.cc \
    libstage/model_blinkenlight.cc \
    libstage/model_actuator.cc \
    libstage/model.cc \
    libstage/logentry.cc \
    libstage/glutgraphics.cc \
    libstage/gl.cc \
    libstage/file_manager.cc \
    libstage/color.cc \
    libstage/canvas.cc \
    libstage/camera.cc \
    libstage/blockgroup.cc \
    libstage/block.cc \
    libstage/ancestor.cc \
    main.cc \
    libstage/option.cc \
    thread.cpp \
    interfaceWindow.cpp \
    libstage/alhoritm/wander.cc \
    #libstage/alhoritm/source.cc \
    #libstage/alhoritm/sink.cc \
    #libstage/alhoritm/rasterize.cc \
    libstage/alhoritm/pioneer_flocking.cc \
    #libstage/alhoritm/lasernoise.cc \
    #libstage/alhoritm/fasr2.cc \
    #libstage/alhoritm/fasr.cc \
    libstage/alhoritm/dynamic.cc \
    libstage/alhoritm/source.cc \
    libstage/alhoritm/sink.cc \
    libstage/alhoritm/fasr.cc

HEADERS += \
    qtlogo.h \
    glwidget.h \
    libstage/worldfile.hh \
    libstage/stage.hh \
    window.hh \
    libstage/world.hh \
    libstage/texture_manager.hh \
    libstage/region.hh \
    libstage/file_manager.hh \
    libstage/canvas.hh \
    libstage/option.hh \
    thread.h \
    interfaceWindow.h

OTHER_FILES += \
    libstage/rgb.txt \
    libstage/CMakeLists.txt
