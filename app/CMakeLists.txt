# Define the executable target
add_executable(ChantsAdventure game.cpp)

# Link the GameMap library (which is created in src/CMakeLists.txt) to the executable
target_link_libraries(ChantsAdventure PRIVATE GameMap)

# Include directories for the executable (can also include headers from the src dir)
target_include_directories(ChantsAdventure PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../inc")
