find_package(Threads REQUIRED)

add_library(landrop_core STATIC
    src/net.cpp
)

target_include_directories(landrop_core PUBLIC include)
target_link_libraries(landrop_core PUBLIC Threads::Threads)

if(WIN32)
    target_link_libraries(landrop_core PUBLIC ws2_32)
endif()

if(MSVC)
    target_compile_options(landrop_core PRIVATE /W4)
else()
    target_compile_options(landrop_core PRIVATE -Wall -Wextra)
endif()
