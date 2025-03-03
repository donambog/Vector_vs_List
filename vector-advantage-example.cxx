#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <string>

// Function to measure the time taken for traversal and random access in both containers
void compare_traversal_and_access() {
    const int NUM_ELEMENTS = 10000000; // 10 million elements
    const int NUM_ACCESSES = 1000000;  // 1 million accesses
    
    std::cout << "Testing traversal and access performance..." << std::endl;
    
    // Prepare containers with initial data
    std::vector<int> vec(NUM_ELEMENTS);
    std::list<int> lst(NUM_ELEMENTS);
    
    // Fill containers with data
    std::iota(vec.begin(), vec.end(), 0);  // Fill with 0, 1, 2, ...
    std::iota(lst.begin(), lst.end(), 0);
    
    // Time vector traversal (iteration)
    auto vec_start = std::chrono::high_resolution_clock::now();
    
    long long vec_sum = 0;
    for (const auto& value : vec) {
        vec_sum += value;
    }
    
    auto vec_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vec_traversal = vec_end - vec_start;
    
    // Time list traversal (iteration)
    auto lst_start = std::chrono::high_resolution_clock::now();
    
    long long lst_sum = 0;
    for (const auto& value : lst) {
        lst_sum += value;
    }
    
    auto lst_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> lst_traversal = lst_end - lst_start;
    
    // Time vector random access
    vec_start = std::chrono::high_resolution_clock::now();
    
    long long vec_access_sum = 0;
    for (int i = 0; i < NUM_ACCESSES; ++i) {
        int index = rand() % NUM_ELEMENTS;
        vec_access_sum += vec[index];
    }
    
    vec_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vec_access = vec_end - vec_start;
    
    // Time list random access (much slower, so we'll do fewer)
    lst_start = std::chrono::high_resolution_clock::now();
    
    long long lst_access_sum = 0;
    const int REDUCED_ACCESSES = 10000; // Reduced to avoid excessive runtime
    
    for (int i = 0; i < REDUCED_ACCESSES; ++i) {
        int index = rand() % NUM_ELEMENTS;
        auto it = lst.begin();
        std::advance(it, index);
        lst_access_sum += *it;
    }
    
    lst_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> lst_access = lst_end - lst_start;
    
    // Scale list access time to match the same number of operations
    double scaled_lst_access = lst_access.count() * (NUM_ACCESSES / static_cast<double>(REDUCED_ACCESSES));
    
    // Report results
    std::cout << "Vector traversal: " << vec_traversal.count() << " ms" << std::endl;
    std::cout << "List traversal: " << lst_traversal.count() << " ms" << std::endl;
    std::cout << "Vector is " << lst_traversal.count() / vec_traversal.count() 
              << " times faster for traversal" << std::endl;
    
    std::cout << "\nVector random access: " << vec_access.count() << " ms" << std::endl;
    std::cout << "List random access (scaled): " << scaled_lst_access << " ms" << std::endl;
    std::cout << "Vector is " << scaled_lst_access / vec_access.count() 
              << " times faster for random access" << std::endl;
}

int main() {
    std::cout << "Performance comparison: std::vector vs std::list for traversal and access" << std::endl;
    std::cout << "=======================================================================" << std::endl;
    
    compare_traversal_and_access();
    
    return 0;
}
