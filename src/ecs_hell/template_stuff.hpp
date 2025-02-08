#include <array>
#include <string_view>
// template<std::size_t D, typename T>
// auto make_uniform_array(T const& t) {
//     return std::apply([&](auto... e) { return std::array{(e, t)...}; },
//                       std::array<int, D>{});
// }
namespace detail {
template<typename T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)> create_array(T value, std::index_sequence<Is...>) {
    // cast Is to void to remove the warning: unused value
    return {{(static_cast<void>(Is), value)...}};
}
} // namespace detail

template<std::size_t N, typename T>
constexpr std::array<T, N> create_array(const T& value) {
    return detail::create_array(value, std::make_index_sequence<N>());
}
// namespace PROP_DETAIL { //separate namespace because all types in this namespace don't display the namespace.
//     //For example PROP_DETAIL::foo would display as only foo. We don't want that for prop::.
//     template <typename T>
//     consteval auto type_name() {
//         std::string_view name, prefix, suffix;
// #ifdef __clang__
//         name = __PRETTY_FUNCTION__;
//         prefix = "auto PROP_DETAIL::type_name() [T = ";
//         suffix = "]";
// #elif defined(__GNUC__)
//         name = __PRETTY_FUNCTION__;
//         prefix = "consteval auto PROP_DETAIL::type_name() [with T = ";
//         suffix = "]";
// #elif defined(_MSC_VER)
//         name = __FUNCSIG__;
//         prefix = "auto __cdecl PROP_DETAIL::type_name<";
//         suffix = ">(void)";
// #endif
//         name.remove_prefix(prefix.size());
//         name.remove_suffix(suffix.size());
//         if (name == "std::basic_string<char>") {
//             return std::string_view{"std::string"};
//         } else if (name == "std::__cxx11::basic_string<char>") {
//             return std::string_view{"std::string"};
//         }
//         return name;
//     }
// } // namespace PROP_DETAIL
