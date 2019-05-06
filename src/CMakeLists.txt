
add_executable(opencv-bench-app
    main.cpp
)

target_link_libraries(opencv-bench-app
    PRIVATE
spdlog::spdlog
${OpenCV_LIBS}
)
