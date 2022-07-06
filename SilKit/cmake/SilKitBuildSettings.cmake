# Copyright (c) Vector Informatik GmbH. All rights reserved.
function(silkit_enable_asan isOn)
    if(NOT isOn)
        return()
    endif()
    message(STATUS "SILKIT -- Enabling Address Sanitizer")
    if(MSVC)
        add_compile_options(/fsanitize=address)
    else()
        #clang, gcc
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer )
        #ensures that -lasan is linked in as first library
        add_link_options(-fsanitize=address)
    endif()
endfunction()

function(silkit_enable_ubsan isOn)
    if(NOT isOn)
        return()
    endif()
    if(MSVC)
        message(STATUS "SILKIT -- UBSAN not supported on MSVC")
    else()
        message(STATUS "SILKIT -- Enabling Undefined Behavior Sanitizer")
        #clang, gcc
        add_compile_options(-fsanitize=undefined) 
        #ensures that -lasan is linked in as first library
        add_link_options(-fsanitize=undefined)
    endif()
endfunction()

function(silkit_enable_threadsan isOn)
    if(NOT isOn)
        return()
    endif()
    if(MSVC)
        message(STATUS "SILKIT -- Thread Sanitizer not supported on MSVC")
    else()
        message(STATUS "SILKIT -- Enabling Thread Sanitizer")
        #clang, gcc
        add_compile_options(-fsanitize=thread -fno-omit-frame-pointer -g3) 
        #ensures that -lasan is linked in as first library
        add_link_options(-fsanitize=thread -fno-omit-frame-pointer -g3)
    endif()
endfunction()

# Clean warning defaults set in CMAKE_*_FLAGS by CMake < 3.15
function(silkit_clean_default_compileflags)
    if(MSVC)
        foreach (flag_var
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)

            # Clean /W3 to avoid /W3 /W4 override warnings
            string(REPLACE "/W3" "" ${flag_var} "${${flag_var}}")
            set(${flag_var} "${${flag_var}}" PARENT_SCOPE)
        endforeach()
    endif()
endfunction()

function(silkit_enable_warnings isOn)
    # Conditionally treat warnings as errors
    set(_warnAsError "")
    if (${isOn})
        if(MSVC_VERSION GREATER 1919)
            set(_warnAsError "/WX")
        elseif(UNIX OR MINGW)
            #assume compiler is clang or gcc
            set(_warnAsError "-Werror")
        endif()
    endif()

    # actual warning flags per platform/compiler
    if(MSVC)
        set(_flags 
            /W4
            /wd4100 # disable unreferenced formal parameter
            ${_warnAsError}
            )
    elseif(MINGW)
        set(_flags
            -pedantic
            -Wall
            -Wextra
            -Wcast-align
            -Wpacked
            -Wno-implicit-fallthrough   

            -Wno-shadow                 # Appears in ThirdParty/spdlog/include/spdlog/common.h:214:9
            -Wno-format                 # MinGW-gcc does not recognize %zu
            -Wno-unused-parameter       # follow up of the %zu format bug, a lot of unused parameters
            -Wstrict-overflow=1         # > 1 fails in fmt-6.1.0
            ${_warnAsError}
            )
    else()
        set(_flags
            -pedantic
            -Wall
            -Wextra
            -Wcast-align
            -Wpacked
            -Wno-implicit-fallthrough   
            -Wformat=2

            -Wno-shadow                 # Appears in ThirdParty/spdlog/include/spdlog/common.h:214:9
            -Wno-format-nonliteral      # Warning in fmt-6.1.0/include/fmt/chrono.h:392:48
            -Wstrict-overflow=1         # > 1 fails in fmt-6.1.0
            ${_warnAsError}
            )

    endif()
    add_compile_options(${_flags})
endfunction()

macro(silkit_check_reproducible)
    if(NOT DEFINED ENV{SOURCE_DATE_EPOCH})
        message(STATUS "SILKIT - Reproducible build: SOURCE_DATE_EPOCH is not set!"
           " Set it to 'git log -1 --format=%ct -r origin/master'")
    else()
        message(STATUS "SILKIT - Reproducible build: SOURCE_DATE_EPOCH=$ENV{SOURCE_DATE_EPOCH}")
    endif()
    if(NOT "$ENV{LC_ALL}" STREQUAL  "C")
        message(STATUS "SILKIT - Reproducible build: LC_ALL is not set to 'C': '$ENV{LC_ALL}'")
    else()
        message(STATUS "SILKIT - Reproducible build: LC_ALL=C")
    endif()
    if(NOT "$ENV{TZ}" STREQUAL  "UTC")
        message(STATUS "SILKIT - Reproducible build: TZ is not set to 'UTC': '$ENV{TZ}'")
    else()
        message(STATUS "SILKIT - Reproducible build: TZ=UTC")
    endif()

endmacro()