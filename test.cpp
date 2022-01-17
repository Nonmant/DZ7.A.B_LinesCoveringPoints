#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                    "3 2\n"
                    "0 5\n"
                    "-3 2\n"
                    "7 10\n"
                    "1 6\n"
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "2 0 "
    );
}

TEST_CASE("zero length line", ""){
    std::stringstream input(
            "2 2\n"
            "1 1\n"
            "3 3\n"
            "1 2\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "1 0 "
    );
}

TEST_CASE("no lines", ""){
    std::stringstream input(
            "0 1\n"
            "1\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "0 "
    );
}

TEST_CASE("all negative coordinates", ""){
    std::stringstream input(
            "3 2\n"
            "-10 -5\n"
            "-6 -5\n"
            "-3 -1\n"
            "-5 -2\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "2 1 "
    );
}

TEST_CASE("2 points at the same place", ""){
    std::stringstream input(
            "1 2\n"
            "0 4\n"
            "2 2\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "1 1 "
    );
}
