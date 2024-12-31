#pragma once

#include <iterator>

namespace ave {

// Not a real meerkat; CC BY-SA 4.0
// from <https://stackoverflow.com/a/59690179>

template <typename Container>
class unordered_inserter {
public:
    using iterator_category = std::output_iterator_tag;
    using value_type        = void;
    using reference_type    = void;
    using difference_type   = void;
    using pointer           = void;
    using reference         = void;
    using container_type    = Container;

    unordered_inserter& operator++() {
        return *this;
    } // no-op
    unordered_inserter& operator++(int) {
        return *this;
    } // no-op
    unordered_inserter& operator*() {
        return *this;
    } // no-op
    constexpr unordered_inserter& operator=(const typename Container::value_type& value) {
        container->insert(value);
        return *this;
    }
    constexpr unordered_inserter& operator=(typename Container::value_type&& value) {
        container->insert(std::move(value));
        return *this;
    }
    unordered_inserter(Container* container) : container(container) {}

protected:
    Container* container;
};

} // namespace ave
