#pragma once

#include <iostream>
#include <chrono>

auto get_time()
{
    return std::chrono::high_resolution_clock::now();
}

void print_difference(std::chrono::high_resolution_clock::time_point t1,
    std::chrono::high_resolution_clock::time_point t2)
{
    uint64_t nano = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    uint64_t micro = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    uint64_t mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    uint64_t sec = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();

    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << sec << " seconds" << std::endl;
    std::cout << mili << " miliseconds" << std::endl;
    std::cout << micro << " microseconds" << std::endl;
    std::cout << nano << " nanoseconds" << std::endl << std::endl;
}