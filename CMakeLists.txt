cmake_minimum_required(VERSION 3.8)

project(SC_Uplink_Downlink)

set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)
find_package(Crow CONFIG REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(SC_Uplink_Downlink Source.cpp)
target_link_libraries(SC_Uplink_Downlink ${Boost_LIBRARIES} Threads::Threads Crow::Crow)
