
#Include the biicode Boost setup script
include(biicode/boost/setup)

ADD_BII_TARGETS()

# Enable C++11
INCLUDE(biicode/cmake/tools) # Include tools.cmake file from cmake block from the "biicode" user
ACTIVATE_CPP11(INTERFACE ${BII_BLOCK_TARGET})

# Link Boost system and filesystem libraries
bii_find_boost(COMPONENTS system filesystem REQUIRED)
target_link_libraries(${BII_BLOCK_TARGET} INTERFACE ${Boost_LIBRARIES})