# 1. On définit le nom du projet (wsi)
discover_lib()

target_sources(wsi PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/__private/xdg-shell-client-protocol.c
)

link_internal_libs(PUBLIC logger)
# 2. On trouve les paquets système nécessaires
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client wayland-egl)
pkg_check_modules(EGL REQUIRED egl)
pkg_check_modules(GL REQUIRED gl)

# 3. Linkage des libs externes
link_external_libs(PUBLIC 
    ${WAYLAND_CLIENT_LIBRARIES} 
    ${EGL_LIBRARIES} 
    ${GL_LIBRARIES}
)