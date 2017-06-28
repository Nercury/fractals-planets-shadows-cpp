cmake_minimum_required(VERSION 3.5)
project(fractals_planets_shadows_cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(SOURCE_FILES
        src/glst/GLST_Factory.cpp
        src/glst/GLST_Factory.h
        src/glst/GLST_Glyph.cpp
        src/glst/GLST_Glyph.h
        src/glst/GLST_std.h
        src/glst/GLST_Surface.cpp
        src/glst/GLST_Surface.h
        src/glst/GLST_Text.cpp
        src/glst/GLST_Text.h
        src/gui/Container.cpp
        src/gui/Container.h
        src/gui/DecoratedWindow.cpp
        src/gui/DecoratedWindow.h
        src/gui/DecoWindow.h
        src/gui/glgui.cpp
        src/gui/glgui.h
        src/gui/Gui.cpp
        src/gui/Gui.h
        src/gui/GuiBase.h
        src/gui/GuiLayer.cpp
        src/gui/GuiLayer.h
#        src/gui/GuiLayerBase.cpp
#        src/gui/GuiLayerBase.h
        src/gui/InputHandlerBase.cpp
        src/gui/InputHandlerBase.h
        src/gui/PopupMenu.cpp
        src/gui/PopupMenu.h
        src/gui/ScreenInfo.h
        src/gui/Theme.cpp
        src/gui/Theme.h
        src/gui/Window.cpp
        src/gui/Window.h
        src/gui/WindowBase.h
        src/gui/WindowEvents.cpp
        src/gui/WindowEvents.h
        src/gui/Windowless.cpp
        src/gui/Windowless.h
        src/math/Matrix.h
        src/math/Matrix.inline.h
        src/math/Plane.h
        src/math/Quaternion.h
        src/math/Quaternion.inline.h
        src/math/Vector.h
        src/math/Vector.inline.h
        src/math/Vector1.h
        src/math/Vector1.inline.h
        src/math/Vector2.h
        src/math/Vector2.inline.h
        src/math/Vector3.h
        src/math/Vector3.inline.h
        src/math/Vector4.h
        src/math/Vector4.inline.h
        src/a_conf.cpp
        src/a_conf.h
        src/a_unicode.cpp
        src/a_unicode.h
        src/a_win.h
        src/b_bind.h
        src/b_threading.cpp
        src/b_threading.h
        src/b_time.h
        src/Camera.cpp
        src/Camera.h
        src/Collision.cpp
        src/Collision.h
        src/dim.h
        src/Example.cpp
        src/Example.h
        src/Fractals.cpp
        src/Fractals.h
        src/GameBase.cpp
        src/GameBase.h
        src/glext.h
        src/L.cpp
        src/L.h
        src/Light.cpp
        src/Light.h
        src/main.cpp
        src/Planets.cpp
        src/Planets.h
        src/PolyObject.cpp
        src/PolyObject.h
        src/safep.hpp
        src/safep.inline.hpp
        src/sdlgl.cpp
        src/sdlgl.h
        src/Shader.cpp
        src/Shader.h
        src/ShaderManager.cpp
        src/ShaderManager.h
        src/ShaderParamBase.h
        src/ShaderParams.h
        src/Sphere.cpp
        src/Sphere.h
        src/Surface.cpp
        src/Surface.h
        src/Texture.cpp
        src/Texture.h
        src/TextureManager.cpp
        src/TextureManager.h
        src/TmpCollisionObj.cpp
        src/TmpCollisionObj.h
        src/Trecia.cpp
        src/Trecia.h
        src/TrMenu.cpp
        src/TrMenu.h
        src/TrMenuItem.cpp
        src/TrMenuItem.h
        src/types.h
        src/World.cpp
        src/World.h
        src/WorldObject.cpp
        src/WorldObject.h
        src/WrlModel.cpp
        src/WrlModel.h)


find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)

if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
    MESSAGE("SDL2 libraries ${SDL2_LIBRARIES}")
else()
    message(FATAL_ERROR "SDL2 was not found")
endif()

find_package(SDL2_ttf REQUIRED)
if(SDL2TTF_FOUND)
    include_directories(${SDL2TTF_INCLUDE_DIR})
    MESSAGE("SDL2_ttf libraries ${SDL2TTF_LIBRARY}")
else()
    message(FATAL_ERROR "SDL2_ttf was not found")
endif()

find_package(SDL2_image REQUIRED)
if(SDL2_image_FOUND)
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
    MESSAGE("SDL2_image libraries ${SDL2_IMAGE_LIBRARIES}")
else()
    message(FATAL_ERROR "SDL2_image was not found")
endif()

set(SDL2MAIN_LIBRARY "${SDL2_LIBRARY}")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS date_time system thread)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost was not found")
endif()

add_executable(fractals_planets_shadows_cpp ${SOURCE_FILES})

target_link_libraries(fractals_planets_shadows_cpp ${Boost_LIBRARIES})
target_link_libraries(fractals_planets_shadows_cpp
        ${SDL2_LIBRARIES} # link sdl
        ${SDL2TTF_LIBRARY} # link sdl
        ${SDL2_IMAGE_LIBRARIES} # link sdl
        ${OPENGL_LIBRARY} # OpenGL
        )

target_include_directories(fractals_planets_shadows_cpp PRIVATE "${PROJECT_SOURCE_DIR}/include")

add_custom_command(TARGET fractals_planets_shadows_cpp PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:fractals_planets_shadows_cpp>/fonts)

add_custom_command(TARGET fractals_planets_shadows_cpp PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/graphics $<TARGET_FILE_DIR:fractals_planets_shadows_cpp>/graphics)

add_custom_command(TARGET fractals_planets_shadows_cpp PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:fractals_planets_shadows_cpp>/shaders)

add_custom_command(TARGET fractals_planets_shadows_cpp PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:fractals_planets_shadows_cpp>/textures)