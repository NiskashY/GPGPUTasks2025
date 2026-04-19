#pragma once 

namespace utils { 

template <typename It>
class IteratorRange {
private:
    It begin_;
    It end_;

public:
    IteratorRange(It begin, It end) : begin_(begin), end_(end) { }

    It begin() const {  return begin_; }
    It end() const { return end_; }
};

}