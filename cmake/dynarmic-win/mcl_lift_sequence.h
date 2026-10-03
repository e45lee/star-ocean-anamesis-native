// For dynarmic's bundled mcl on Windows with llvm-mingw's clang 23 (cmake/deps.cmake, force-included
// into dynarmic's sources there): mcl's lift_sequence matches a value list through a template
// template parameter `template<class, T...> class`, which this clang no longer deduces for
// std::integer_sequence ("implicit instantiation of undefined template lift_sequence_impl<...>").
// The same specialization, spelled for std::integer_sequence directly.
#pragma once
#include <utility>

#include "mcl/mp/typelist/lift_sequence.hpp"

namespace mcl::mp::detail {
template<class T, T... values>
struct lift_sequence_impl<std::integer_sequence<T, values...>> {
    using type = list<std::integral_constant<T, values>...>;
};
}  // namespace mcl::mp::detail
