// Internal interfaces between port/src files (C++).
#pragma once

#include <chrono>

// vi_frame.cpp: when the next VI retrace is due, and how many have happened.
std::chrono::steady_clock::time_point port_retrace_deadline();
unsigned int port_retrace_count();

extern "C" {
// os.cpp
void port_threads_init(void);
void port_wait_retrace(unsigned int count);
void port_retrace_notify(void);
}
