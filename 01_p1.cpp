#include "unordered_inserter.hh"
#include "util.hh"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <fstream>
#include <numeric>
#include <ranges>
#include <set>
#include <unordered_set>
#include <vector>

void populate_multisets_from(std::ifstream& input, std::multiset<int>& a_set, std::multiset<int>& b_set) {
    int a{};
    int b{};
    while (input >> a >> b) {
        a_set.insert(a);
        b_set.insert(b);
    }
    assert(a_set.size() == b_set.size());
    // fmt::println("Size: {}, set: {}", a_set.size(), a_set);
}

#if defined(AOC_USE_RANGES)

int total_difference(std::multiset<int> const& a_set, std::multiset<int> const& b_set) {
#if 1
    // This took me embarrassingly long, but I'm just starting with ranges...
    // https://devblogs.microsoft.com/cppblog/cpp23s-new-fold-algorithms/
    return std::ranges::fold_left(std::views::zip(a_set, b_set), 0,
        [](int total, const auto& pair) { return total + std::abs(std::get<0>(pair) - std::get<1>(pair)); });
#else
    // alternatively, via std::accumulate (without common_view iterator types are different) and using pipe operator:
    auto it = std::ranges::common_view{std::views::zip(a_set, b_set) | std::views::transform([](auto const& pair) {
        return std::abs(pair.first - pair.second);
    })};
    return std::accumulate(it.begin(), it.end(), 0);
#endif
}

#else

int total_difference(std::multiset<int> const& a_set, std::multiset<int> const& b_set) {
    std::unordered_multiset<int> differences;
    std::transform(std::cbegin(a_set), std::cend(a_set), std::cbegin(b_set), ave::unordered_inserter{&differences},
        [](int const a, int const b) { return std::abs(a - b); });
    return std::accumulate(std::begin(differences), std::end(differences), 0);
}

#endif

int main() {
    std::ifstream input;
    try {
        input = util::try_open("01_p1.in");
    } catch (std::system_error const& e) {
        fmt::println("{} ({})", e.what(), e.code());
        std::exit(EXIT_FAILURE);
    }

    std::multiset<int> a_set;
    std::multiset<int> b_set;
    populate_multisets_from(input, a_set, b_set);

    auto answer = total_difference(a_set, b_set);
    fmt::println("Answer: {}", answer);
    // TODO ranges zip solution, add cmake choice and support macro?
}
