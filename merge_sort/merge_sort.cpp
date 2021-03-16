#include <vector>
#include <iterator>
#include <algorithm>
#include <utility>
#include <iostream>

template <typename T, typename U>
void merge (T begin, T mid, T end, U begin_buffer)
{
    T  low  = begin;
    T  high = mid;
    U  buf  = begin_buffer;
    while (low < mid && high < end) {
        if (*low <= *high) {
            std::iter_swap (low, buf);
            low++;
        }
        else {
            std::iter_swap (high, buf);
            high++;
        }
        buf++;
    }
    std::move(low, mid, buf);
    std::move(high, end, buf);

    std::size_t size = std::distance(begin, end);
    std::move(begin_buffer, std::next(begin_buffer, size), begin);
}

template <typename T, typename U>
void buffer_merge_sort (T begin, T end, U begin_buffer)
{
    std::size_t size = std::distance (begin, end);
    if (size == 1) {
        return;
    }

    std::size_t split      = size / 2;
    T           mid        = std::next (begin, split);
    U           mid_buffer = std::next (begin_buffer, split);

    buffer_merge_sort (begin, mid, begin_buffer);
    buffer_merge_sort (mid,   end, mid_buffer);

    merge (begin, mid, end, begin_buffer);
}

template <typename T>
void merge_sort (T begin, T end)
{
    using       ValueType  = typename std::iterator_traits<T>::value_type;
    std::size_t size       = std::distance (begin, end);
    std::vector <ValueType> buffer (size);

    buffer_merge_sort (begin, end, std::begin(buffer));
}

int main()
{
    std::vector <int> a = {3, 0, 7, 5, 7, 8, 3, 1};
    merge_sort (std::begin(a), std::end(a));
    for (auto i: a){
            std::cout << i << std::endl;
    }
}
