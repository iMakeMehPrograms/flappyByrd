#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>

#define TICKRATE 100
#define TIMEOUT 36000

extern std::vector<void (*)()> tickCalls;

extern void (*starter)();

extern void (* inputer)();

extern std::ofstream debugout;

extern bool end;

template <typename T> extern void log(T data);