#include <iostream>
#include <string>
#include <cstdlib>
#include <omp.h>
#include <stdio.h>

#include "InputFile.h"
#include "Driver.h"

int main(int argc, char *argv[])
{
    double start = omp_get_wtime(); //timer start

    if (argc != 2) {
        std::cerr << "Usage: deqn <filename>" << std::endl;
        exit(1);
    }

    const char* filename = argv[1];
    InputFile input(filename);

    std::string problem_name(filename);

    int len = problem_name.length();

    if(problem_name.substr(len - 3, 3) == ".in")
        problem_name = problem_name.substr(0, len-3);

    // Strip out leading path
    size_t last_sep = problem_name.find_last_of("/");

    if (last_sep != std::string::npos) {
        last_sep = last_sep + 1;
    } else {
        last_sep = 0;
    }

    problem_name = problem_name.substr(last_sep, problem_name.size());

    Driver driver(&input, problem_name);

    driver.run();

    double end = omp_get_wtime(); // timer stop
    printf("Time spend is %f\n", end - start);    

    return 0;
}
