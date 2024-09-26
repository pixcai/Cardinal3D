#pragma once

#include <utility>

namespace cardinal {
namespace functional {

template <typename... Ts> struct Overload final : Ts... {
    using Ts::operator()...;

    constexpr explicit Overload(Ts... ts) : Ts(std::move(ts))... {}
};

} // namespace functional
} // namespace cardinal