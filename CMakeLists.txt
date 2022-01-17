project(DZ)

add_executable(main
        funcs.cpp
        main.cpp
        )

add_executable(test
        funcs.cpp
        test.cpp
        )
target_include_directories(
        test
        PUBLIC ./include/Catch/single_include/catch2/
        )
