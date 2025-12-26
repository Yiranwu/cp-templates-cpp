//
// Created by Andrew Wu on 9/22/24.
//

#ifndef TIMING_H
#define TIMING_H

#include "../../template/cp_template.h"


#if 0
auto start_time = std::chrono::high_resolution_clock::now();
// op_to_time
auto end_time = std::chrono::high_resolution_clock::now();
std::cout << std::chrono::duration<double, std::milli>(end_time - start_time).count() << " ms" << std::endl;
#endif

#endif //TIMING_H
