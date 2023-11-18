cmake_minimum_required(VERSION 3.26)
project(CandyCommon)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
find_package(spdlog CONFIG REQUIRED)
add_subdirectory(lib/rapidyaml)
add_subdirectory(lib/nativefiledialog)

set(CANDY_BASE_HEADERS include/candy/base/Assert.hpp
        include/candy/base/Base.hpp
        include/candy/base/CandyConcepts.hpp
        include/candy/base/Instrumentor.hpp
        include/candy/base/KeyCodes.hpp
        include/candy/base/Log.hpp
        include/candy/base/MouseCodes.hpp
        include/candy/base/PlatformDetection.hpp
        include/candy/base/PrimitiveTypes.hpp
        include/candy/base/RawBuffer.hpp
        include/candy/base/UUID.hpp
        include/candy/base/Version.hpp)

set(CANDY_BASE_SOURCES src/base/Log.cpp
        src/base/UUID.cpp src/base/Version.cpp)

set(CANDY_BASE_FILES ${CANDY_BASE_HEADERS} ${CANDY_BASE_SOURCES})

set(CANDY_COLLECTIONS_FILES include/candy/collections/Array2D.hpp
        include/candy/collections/Array3D.hpp
        include/candy/collections/GenericBuffer.hpp
        include/candy/collections/DualMap.hpp)

set(CANDY_MATH_HEADERS include/candy/math/Vector.hpp
        include/candy/math/Direction.hpp
        include/candy/math/Limit.hpp
        include/candy/math/Math.hpp
        include/candy/math/MathOps.hpp
        include/candy/math/Matrix.hpp
        include/candy/math/Quaternion.hpp
        include/candy/math/Random.hpp
        include/candy/math/Random.inl
        include/candy/math/Range.hpp
        include/candy/math/Rectangle.hpp
        include/candy/math/Transform.hpp
        include/candy/math/vector/Vector2Base.hpp
        include/candy/math/vector/Vector2Base.inl
        include/candy/math/vector/Vector3Base.hpp
        include/candy/math/vector/Vector3Base.inl
        include/candy/math/vector/Vector4Base.hpp
        include/candy/math/vector/Vector4Base.inl
        include/candy/math/vector/VectorBase.hpp
        include/candy/math/vector/VectorBaseStaticData.hpp
        include/candy/math/vector/VectorExpression.hpp
        include/candy/math/vector/VectorOperations.hpp
        include/candy/math/ray/Ray3.hpp
        include/candy/math/quaternion/QuaternionBase.hpp
        include/candy/math/quaternion/QuaternionBase.inl
        include/candy/math/matrix/specialization/Matrix3.hpp
        include/candy/math/matrix/base/MatrixExpression.hpp
        include/candy/math/direction/Direction2.hpp
        include/candy/math/direction/Direction3.hpp
        include/candy/math/matrix/specialization/Matrix4.hpp
        include/candy/math/geometry/Bounds2D.hpp
        include/candy/math/curve/BezierCurve.hpp
        include/candy/math/curve/BezierCurveQuadratic.hpp
        include/candy/math/curve/BezierCurveCubic.hpp
        include/candy/math/curve/BezierCurveFixed.hpp
        include/candy/math/geometry/Contour.hpp
        include/candy/math/geometry/Line.hpp
        include/candy/math/Color.hpp
        include/candy/math/color/ColorRGBA.inl
        include/candy/math/color/ColorRGBA.hpp
        include/candy/math/color/ColorBaseStaticData.hpp
        include/candy/math/color/ColorBase.hpp
)

set(CANDY_MATH_SOURCES
        src/math/matrix/Matrix3.cpp
        src/math/direction/Direction2.cpp
        src/math/direction/Direction3.cpp
        src/math/matrix/Matrix4.cpp
        src/math/Quaternion.cpp
        src/math/geometry/Bounds2D.cpp
        src/math/curve/BezierCurve.cpp
        src/math/curve/BezierCurveQuadratic.cpp
        src/math/curve/BezierCurveCubic.cpp
        src/math/geometry/Line.cpp)

set(CANDY_MATH_FILES ${CANDY_MATH_HEADERS} ${CANDY_MATH_SOURCES})

set(CANDY_NOISE_HEADERS include/candy/noise/PerlinNoise.hpp)
set(CANDY_NOISE_SOURCES src/noise/PerlinNoise.cpp)

set(CANDY_NOISE_FILES ${CANDY_NOISE_HEADERS} ${CANDY_NOISE_SOURCES})

set(CANDY_UTILS_HEADERS
        include/candy/utils/FrameTime.hpp
        include/candy/utils/IDManager.hpp
        include/candy/utils/Stopwatch.hpp
        include/candy/utils/FileUtils.hpp)

set(CANDY_UTILS_SOURCES src/utils/FrameTime.cpp src/utils/Stopwatch.cpp
        src/utils/FileUtils.cpp)

set(CANDY_UTILS_FILES ${CANDY_UTILS_HEADERS} ${CANDY_UTILS_SOURCES})

set(CANDY_COMMON_FILES ${CANDY_BASE_FILES} ${CANDY_COLLECTIONS_FILES} ${CANDY_MATH_FILES} ${CANDY_NOISE_FILES} ${CANDY_UTILS_FILES} include/CandyPch.hpp include/CandyPch.cpp)

option(CANDY_BUILD_SHARED "On- Build CandyEngine as a shared library. Off- Build CandyEngine as a static library." OFF)
option(CANDY_PROFILE "On- Enable profiling. Off- Disable profiling." OFF)
option(CANDY_ENABLE_LOGGING "On- Enable logging. Off- Disable logging." ON)



if (CANDY_BUILD_SHARED)
    add_library(CandyCommon SHARED ${CANDY_COMMON_FILES})
else()
    add_library(CandyCommon STATIC ${CANDY_COMMON_FILES})
endif()



if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(CandyCommon PROPERTIES OUTPUT_NAME CandyCommonDebug)
    set_target_properties(CandyCommon PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(CandyCommon PROPERTIES CXX_STANDARD 23)
    target_compile_definitions(CandyCommon PRIVATE CANDY_DEBUG=1)

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(CandyCommon PROPERTIES OUTPUT_NAME CandyCommonRelease)
    set_target_properties(CandyCommon PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(CandyCommon PROPERTIES CXX_STANDARD 23)
else()
    message("Some other build type.")
endif()

if (CANDY_PROFILE)
    target_compile_definitions(CandyCommon PUBLIC CANDY_PROFILE)
endif()

if(CANDY_ENABLE_LOGGING)
    target_compile_definitions(CandyCommon PUBLIC CANDY_ENABLE_LOGGING)
endif()


target_include_directories(CandyCommon PUBLIC include)
target_include_directories(CandyCommon PRIVATE lib/nativefiledialog/src/include)
target_link_libraries(CandyCommon PRIVATE ryml::ryml nfd)
target_link_libraries(CandyCommon PUBLIC spdlog::spdlog)
add_executable(CandyCommonExec main.cpp)
target_link_libraries(CandyCommonExec PUBLIC CandyCommon)
