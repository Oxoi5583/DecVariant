#pragma  once

#include <string>
#include <algorithm>
#include <assert.h>
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;