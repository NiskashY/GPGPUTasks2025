#pragma once

#include <cstddef>
#include <tuple>

#include <utils/iterator_range.hpp>

namespace utils { 

template <typename It>
class EnumeratorIterator { 
private:
    It it_;
    std::size_t pos_;

public:
    EnumeratorIterator(It it) : it_(it), pos_(0) { }

    auto operator*() const { 
        return std::forward_as_tuple(pos_, *it_);
    }

    EnumeratorIterator& operator++() { 
        ++it_;
        ++pos_;
        return *this;
    }

    bool operator==(const EnumeratorIterator& rhs) const { 
        return it_ == rhs.it_;
    }
    bool operator!=(const EnumeratorIterator& rhs) const { 
        return !(*this == rhs);
    }
};

template <typename Container>
auto Enumerate(Container& container) { 
    return IteratorRange{
        EnumeratorIterator{container.begin()},
        EnumeratorIterator{container.end()}
    };
}

} // 