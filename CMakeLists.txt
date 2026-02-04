cmake_minimum_required(VERSION 3.10)

project(makeItWork)

add_executable(main 
    src/main.cpp
    src/audio.cpp 
    src/bullets.cpp
    src/console.cpp 
    src/enemies.cpp 
    src/fileHandeling.cpp 
    src/player.cpp 
)

target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(main PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2_mixer.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/libSDL2main.a"
    winmm
    setupapi
    imm32
    version
)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets" 
    "$<TARGET_FILE_DIR:main>/assets"
    
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/data" 
    "$<TARGET_FILE_DIR:main>/data"
    
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/bin/SDL2_mixer.dll" 
    "${CMAKE_CURRENT_SOURCE_DIR}/bin/SDL2.dll" 
    "$<TARGET_FILE_DIR:main>"
    
    COMMENT "Copying assets folder build DIR...\nCopying data folder to build DIR...\nCopying DLL files to build DIR..."
)
