// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include <utility>

namespace cardinal {
namespace utility {

template <typename... Ts>
struct Overload final : Ts... {
    using Ts::operator()...;

    constexpr explicit Overload(Ts... ts) : Ts(std::move(ts))... {}
};

} // namespace utility
} // namespace cardinal
