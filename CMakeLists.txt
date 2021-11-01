# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# Define project name
project(vector_project)

AUX_SOURCE_DIRECTORY(.   PROJECT_FILES)

list(APPEND project_sources
    ${PROJECT_FILES}
)

message(status ${project_sources})

include_directories(${AIPU_SDK_LAYERLIB_INCLUDE_DIR})
# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} ${project_sources})

# Link your application with OpenCV libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
