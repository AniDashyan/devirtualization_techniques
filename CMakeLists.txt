cmake_minimum_required(VERSION 3.10)
project(devirtualization_techniques)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES main.cpp)

# Create four different executables to test combinations
add_executable(devirt_enabled_final ${SOURCES})      # -fdevirtualize + FINAL
add_executable(devirt_enabled_nofinal ${SOURCES})    # -fdevirtualize + no FINAL
add_executable(devirt_disabled_final ${SOURCES})     # -fno-devirtualize + FINAL
add_executable(devirt_disabled_nofinal ${SOURCES})   # -fno-devirtualize + no FINAL

if(MSVC)
    set(COMMON_FLAGS /O2 /W4 /Zi)
else()
    set(COMMON_FLAGS -O2 -Wall -Wextra -g)
endif()

target_compile_options(devirt_enabled_final PRIVATE
    ${COMMON_FLAGS}
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fdevirtualize>
)
target_compile_definitions(devirt_enabled_final PRIVATE ENABLE_FINAL=1)

target_compile_options(devirt_enabled_nofinal PRIVATE
    ${COMMON_FLAGS}
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fdevirtualize>
)
target_compile_definitions(devirt_enabled_nofinal PRIVATE ENABLE_FINAL=0)

target_compile_options(devirt_disabled_final PRIVATE
    ${COMMON_FLAGS}
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fno-devirtualize>
)
target_compile_definitions(devirt_disabled_final PRIVATE ENABLE_FINAL=1)

target_compile_options(devirt_disabled_nofinal PRIVATE
    ${COMMON_FLAGS}
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fno-devirtualize>
)
target_compile_definitions(devirt_disabled_nofinal PRIVATE ENABLE_FINAL=0)

# Custom target for comprehensive benchmark
add_custom_target(benchmark
    COMMAND ${CMAKE_COMMAND} -E echo "=== Comprehensive Performance Comparison ==="
    COMMAND ${CMAKE_COMMAND} -E echo "1. Devirtualization ENABLED + final ENABLED:"
    COMMAND $<TARGET_FILE:devirt_enabled_final>
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "2. Devirtualization ENABLED + final DISABLED:"
    COMMAND $<TARGET_FILE:devirt_enabled_nofinal>
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "3. Devirtualization DISABLED + final ENABLED:"
    COMMAND $<TARGET_FILE:devirt_disabled_final>
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "4. Devirtualization DISABLED + final DISABLED:"
    COMMAND $<TARGET_FILE:devirt_disabled_nofinal>
    DEPENDS devirt_enabled_final devirt_enabled_nofinal devirt_disabled_final devirt_disabled_nofinal
)