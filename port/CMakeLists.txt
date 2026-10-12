cmake_minimum_required(VERSION 3.25)

# PC build of Mario Superstar Baseball on aurora. See port/README.md.
#   cmake -S port -B build/port -G Ninja && ninja -C build/port

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type" FORCE)
endif ()

if (APPLE AND NOT CMAKE_OSX_SYSROOT)
    execute_process(COMMAND xcrun --sdk macosx --show-sdk-path
            OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
            OUTPUT_STRIP_TRAILING_WHITESPACE)
endif ()

project(mssb LANGUAGES C CXX VERSION 0.1.0)
if (APPLE)
    enable_language(OBJC OBJCXX)
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

get_filename_component(MSSB_ROOT ${CMAKE_SOURCE_DIR}/.. ABSOLUTE)
set(AURORA_DIR ${CMAKE_SOURCE_DIR}/extern/aurora)

# aurora is used at strikers' revision: the submodule pins the pushed
# bigmah/aurora strikers-port head, and port/patches/aurora brings it to the
# tree strikers builds with (its local commit 3fbe54a). Patches apply once.
file(GLOB AURORA_PATCHES ${CMAKE_SOURCE_DIR}/patches/aurora/*.patch)
list(SORT AURORA_PATCHES)
foreach (patch ${AURORA_PATCHES})
    execute_process(COMMAND git apply --reverse --check ${patch}
            WORKING_DIRECTORY ${AURORA_DIR}
            RESULT_VARIABLE already_applied OUTPUT_QUIET ERROR_QUIET)
    if (NOT already_applied EQUAL 0)
        execute_process(COMMAND git apply ${patch}
                WORKING_DIRECTORY ${AURORA_DIR}
                RESULT_VARIABLE patch_result)
        if (NOT patch_result EQUAL 0)
            message(FATAL_ERROR "Failed to apply ${patch}")
        endif ()
        message(STATUS "Applied ${patch}")
    endif ()
endforeach ()

# Compiling the game only needs aurora's headers; the full aurora build
# (Dawn, SDL3, nod) is needed to link the executable (Phase 2).
option(MSSB_AURORA "Configure aurora (needed to link the mssb executable)" ON)
if (MSSB_AURORA)
    set(AURORA_ENABLE_DVD ON CACHE BOOL "" FORCE)
    set(AURORA_ENABLE_CARD ON CACHE BOOL "" FORCE)
    add_subdirectory(${AURORA_DIR} aurora EXCLUDE_FROM_ALL)
endif ()

include(${CMAKE_SOURCE_DIR}/sources.cmake)

# Include order matters on case-insensitive filesystems: aurora's
# <dolphin/...> must win over the decomp's include/Dolphin/... for the SDK.
# The decomp's own SDK headers forward to aurora's under TARGET_PC.
set(MSSB_INCLUDES
    ${CMAKE_SOURCE_DIR}/include
    ${AURORA_DIR}/include
    ${MSSB_ROOT}/include
)

set(MSSB_DEFS TARGET_PC NONMATCHING=1 VERSION=0 VERNUM=0 NDEBUG=1)

set(MSSB_COMMON_FLAGS
    -fno-strict-aliasing
    -fwrapv
    -fno-delete-null-pointer-checks
    -fsigned-char
    -ffp-contract=off
    -fno-strict-return
    -fno-finite-loops
    -fno-common
    -ferror-limit=0
    # Game sources declare memcpy/memset themselves: no fortify macros.
    -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0
)

# 64-bit problems: pointers must not be stored in 32-bit integers, and calls
# need prototypes (an implicit int return truncates pointers). Everything
# else stays quiet: the decomp is full of harmless MWCC-isms.
option(MSSB_WERROR_64 "Make the 64-bit pointer/int warnings errors" ON)
set(MSSB_64_WARNINGS
    shorten-64-to-32
    int-to-pointer-cast
    pointer-to-int-cast
    incompatible-function-pointer-types
    implicit-function-declaration
    int-conversion
)
set(MSSB_PORT_WARNINGS -Wno-everything)
foreach (w ${MSSB_64_WARNINGS})
    list(APPEND MSSB_PORT_WARNINGS -W${w})
    if (MSSB_WERROR_64)
        list(APPEND MSSB_PORT_WARNINGS -Werror=${w})
    endif ()
endforeach ()

# Game code from main.dol, game.rel, menus.rel and challenge.rel.
add_library(mssb_game OBJECT ${MSSB_GAME_SOURCES})
target_include_directories(mssb_game PRIVATE ${MSSB_INCLUDES})
target_compile_definitions(mssb_game PRIVATE ${MSSB_DEFS})
target_compile_options(mssb_game PRIVATE ${MSSB_COMMON_FLAGS} ${MSSB_PORT_WARNINGS}
    -include ${CMAKE_SOURCE_DIR}/include/port/prelude.h)

# PC-only code. The executable does not link yet (Phase 2): exclude it from
# the default target so `ninja` builds and checks the game objects.
file(GLOB_RECURSE PORT_SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)
add_executable(mssb EXCLUDE_FROM_ALL ${PORT_SOURCES} $<TARGET_OBJECTS:mssb_game>)
target_include_directories(mssb PRIVATE ${MSSB_INCLUDES})
target_compile_definitions(mssb PRIVATE ${MSSB_DEFS})
target_compile_options(mssb PRIVATE ${MSSB_COMMON_FLAGS} -Wno-everything)
if (MSSB_AURORA)
    target_link_libraries(mssb PRIVATE aurora::core aurora::gx aurora::vi aurora::pad
        aurora::si aurora::dvd aurora::card aurora::mtx aurora::os aurora::main)
endif ()
