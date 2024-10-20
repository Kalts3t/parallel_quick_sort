#include <algorithm>
#include <future>
#include <iostream>
#include <list>

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input) {
    if(input.empty()) {
        return input;
    }
    std::list<T> result,lower_bound;
    const T& pivot = *input.begin();
    auto divide_point = std::partition(input.begin(), input.end(),[&](const T& x) {
        return x<pivot;
    });
    lower_bound.splice(lower_bound.begin(),input,input.begin(),divide_point);
    std::future<T> lower_result_future(
        std::async(&parallel_quick_sort<T>,std::move(lower_bound))
    );
    auto higher_bound(parallel_quick_sort<T>(input));
    result.splice(result.begin(),lower_result_future.get());
    result.splice(result.end(),higher_bound);
    return result;
}
