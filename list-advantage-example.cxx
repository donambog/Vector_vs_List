#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>

// Function to measure the time taken for middle insertions in both containers
void compare_middle_insertions() {
    const int NUM_ELEMENTS = 100000;
    const int NUM_INSERTIONS = 10000;
    
    std::cout << "Testing middle insertions performance..." << std::endl;
    
    // Prepare containers with initial data
    std::vector<int> vec;
    std::list<int> lst;
    
    // Pre-fill containers with ordered data
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        vec.push_back(i);
        lst.push_back(i);
    }
    
    // Time vector middle insertions
    auto vec_start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        // Insert at the middle of the vector
        auto middle_it = vec.begin() + vec.size() / 2;
        vec.insert(middle_it, -i);
    }
    
    auto vec_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vec_duration = vec_end - vec_start;
    
    // Time list middle insertions
    auto lst_start = std::chrono::high_resolution_clock::now();
    
    auto middle_it = lst.begin();
    std::advance(middle_it, lst.size() / 2);
    
    for (int i = 0; i < NUM_INSERTIONS; i++) {
        // Insert at the middle of the list
        lst.insert(middle_it, -i);
    }
    
    auto lst_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> lst_duration = lst_end - lst_start;
    
    // Report results
    std::cout << "Vector middle insertions: " << vec_duration.count() << " ms" << std::endl;
    std::cout << "List middle insertions: " << lst_duration.count() << " ms" << std::endl;
    std::cout << "List is " << vec_duration.count() / lst_duration.count() 
              << " times faster for middle insertions" << std::endl;
}

int main() {
    std::cout << "Performance comparison: std::list vs std::vector for middle insertions" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    
    compare_middle_insertions();
    
    return 0;
}
