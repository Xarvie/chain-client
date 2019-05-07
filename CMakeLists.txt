PROJECT(chain-client)
cmake_minimum_required (VERSION 3.2)
list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake/macros")
include(AutoCollect)
set(CMAKE_CXX_STANDARD 17)
# cd build
# cmake .. -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DCMAKE_CXX_FLAGS="-static"
PickIncludeDirectories(
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    INCLUDEDIRS
    # Exclude
    ${CMAKE_CURRENT_SOURCE_DIR}/build)

PickSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}/code
    CODEFILES
    # Exclude
    ${CMAKE_CURRENT_SOURCE_DIR}/build)

PickIncludeDirectories(
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/chain-net/code/chain-net
        INCLUDEDIRS
        # Exclude
        ${CMAKE_CURRENT_SOURCE_DIR}/build)

PickSourceFiles(
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/chain-net/code/chain-net
        CODEFILES
        # Exclude
        ${CMAKE_CURRENT_SOURCE_DIR}/build)

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    PickIncludeDirectories(
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/mingw64/include
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    PickIncludeDirectories(
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/linux/include
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSE()
    PickIncludeDirectories(
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/bsd/include
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ENDIF()

#sdl2
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    PickIncludeDirectories(
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/mingw64/include/SDL2
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    PickIncludeDirectories(
            #${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/linux/include
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSE()
    PickIncludeDirectories(
            #${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/bsd/include
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ENDIF()

#sdl2_image
IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    PickIncludeDirectories(
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2_image/mingw64/include/SDL2
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    PickIncludeDirectories(
            #${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/linux/include
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSE()
    PickIncludeDirectories(
            #${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/bsd/include
            INCLUDEDIRS
            # Exclude
            ${CMAKE_CURRENT_SOURCE_DIR}/build)
ENDIF()

MakeFilter(
    ${CMAKE_CURRENT_SOURCE_DIR}/code)


set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -static -mwindows -static-libgcc")#-Wl,--no-undefined

ADD_EXECUTABLE(chain-client
    ${CODEFILES})
target_include_directories(chain-client
        PUBLIC ${INCLUDEDIRS})

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
    
    file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR}/)
    file(COPY ${CMAKE_SOURCE_DIR}/thirdparty/sdl2_image/mingw64/bin/libjpeg-9.dll DESTINATION ${CMAKE_BINARY_DIR}/)
    file(COPY ${CMAKE_SOURCE_DIR}/thirdparty/sdl2_image/mingw64/bin/libpng16-16.dll DESTINATION ${CMAKE_BINARY_DIR}/)
    file(COPY ${CMAKE_SOURCE_DIR}/thirdparty/sdl2_image/mingw64/bin/libtiff-5.dll DESTINATION ${CMAKE_BINARY_DIR}/)
    file(COPY ${CMAKE_SOURCE_DIR}/thirdparty/sdl2_image/mingw64/bin/libwebp-7.dll DESTINATION ${CMAKE_BINARY_DIR}/)
    file(COPY ${CMAKE_SOURCE_DIR}/thirdparty/sdl2_image/mingw64/bin/zlib1.dll DESTINATION ${CMAKE_BINARY_DIR}/)

    target_link_libraries(chain-client pthread ws2_32
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/mingw64/lib/libflatbuffers.a
        libmingw32.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/mingw64/lib/libSDL2main.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2/mingw64/lib/libSDL2.a
        ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sdl2_image/mingw64/lib/libSDL2_image.a
        m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 setupapi version uuid 
        
)
ELSEIF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(chain-client pthread
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/linux/lib/libflatbuffers.a)
    #TODO
ELSE()
    target_link_libraries(chain-client pthread
            ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/flatbuffers/bsd/lib/libflatbuffers.a)
    #TODO
ENDIF()


