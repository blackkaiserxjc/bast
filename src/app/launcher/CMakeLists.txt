find_package(Boost REQUIRED COMPONENTS date_time filesystem iostreams)

set(bast_launcher_SRCS main.cpp)

add_executable(bast_launcher ${bast_launcher_SRCS})
target_link_libraries(bast_launcher Boost::date_time Boost::filesystem Boost::iostreams)
