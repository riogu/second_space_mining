//
// #include <type_traits>
// class Base {
//   public:
//     int x = 1321;
// };
// class Derived : public Base {};
//
// template<int i>
// struct map {
//     template<typename t>
//     map() {
//         // using type = t;
//     }
// };
//
// struct another_map {
//     template<class T>
//     another_map(std::type_identity_t<T>) {
//     }
// };
// struct storage {
//     template<class T>
//     storage() {
//         using type = T;
//     }
// };
//
// int main() {
//     int x = 3123;
//
//     map<0> var(Base);
//
//     another_map(std::type_identity_t<Base>());
//
//     return 0;
// }
