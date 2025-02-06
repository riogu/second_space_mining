#include <iostream>

class Base {
  public:
    int x = 1321;
};
class Derived : public Base {};

template<int i>
struct my_map;

// specialize the map
template<>
struct my_map<0> {
    using type = Base;
};

template<>
struct my_map<1> {
    using type = Derived;
};

template<int i>
using my_map_t = typename my_map<i>::type;

int main() {
    my_map_t<0> something; // default creates a Base() object
    //^ same as the using this
    my_map<1>::type something_else;

    std::cout << something.x; // we can use this normally as an instance of Base
    std::cout << something_else.x;

    // we can also do this
    Base some_base = my_map_t<0>();
    std::cout << some_base.x;

    return 0;
}
