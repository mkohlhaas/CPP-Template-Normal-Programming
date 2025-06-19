#include <algorithm>
#include <array>
#include <iostream>

#define PROJECT_NAME "f"

// function overloading (params are significant)
int
f1(int a)
{
    std::cout << a << std::endl;
    return 4;
}

double
f1(float a)
{
    std::cout << a << std::endl;
    return 4.0;
}

template <typename T, typename U>
void
foo1(std::array<T, sizeof(U)>, //
     std::array<U, sizeof(T)>, //
     int)
{
    puts(__PRETTY_FUNCTION__);
}

template <typename R, typename A>
void
foo2(R (*)(A))
{
    puts(__PRETTY_FUNCTION__);
}

short
f2()
{
    return 99;
};

template <typename T, typename U>
void
add1(T, U)
{
    puts(__PRETTY_FUNCTION__);
}

template <typename T>
void
add2()
{
    puts(__PRETTY_FUNCTION__);
}

template <typename T = char *>
void
add3()
{
    puts(__PRETTY_FUNCTION__);
}

template <typename T>
void
f3(T)
{
    puts(__PRETTY_FUNCTION__);
}

template <typename T>
void
f4(T *)
{
    puts(__PRETTY_FUNCTION__);
}

template <typename T>
void
f5(T &) // l-value ref
{
    puts(__PRETTY_FUNCTION__);
}

template <typename T>
void
f6(T &&) // universal/forwarding reference
{
    puts(__PRETTY_FUNCTION__);
}

template <typename T>
void
f7(void (*)(T))
{
    puts(__PRETTY_FUNCTION__);
}

void
g(int &&) // r-value ref (NOT universal/forwarding ref!)
{
}

int
main()
{
    foo1(std::array<int, 8>{}, std::array<double, 4>{}, 0.0);
    // foo(std::array<int, 9>{}, std::array<double, 4>{}, 0.0); // error

    // foo2([](double x) { return int(x); }); // error
    foo2(+[](double x) { return int(x); });

    // return std::max(f(), 42); // error

    // workarounds:
    std::cout << std::max(static_cast<int>(f2()), 42) << std::endl; // cast (too verbose)
    std::cout << std::max<int>(f2(), 42) << std::endl;              // make template paarameters explicit

    add1<int, int>('x', 3.1);
    add1<int>('x', 3.1);
    add1<>('x', 3.1);
    add1('x', 3.1);

    add2<int>();
    // add2<>();  // error
    // add2();    // error

    // with default type parameter
    add3<int>();
    add3<>();
    add3();

    int i{};
    f3(i);

    f4(&i);

    f5(i);

    // deduce T such that T&& is the target category (r-value/l-value)
    // Another way to put it: What is T such that T&& leads to target type?
    f6(42);           // r-value ref (42 = int&& = target category) -> T = int (T&& would also work)
                      // What is T such that T&& = int &&? -> T = int
    f6(std::move(i)); // same as previous
    f6(i);            // l-value ref (i = int& = target category) -> T = int&
                      // What is T such that T&& = int&? -> T = int&

                      // Combining two reference types mins the number of ampersands (reference collapsing):
    // &  +  & =  &
    // &  + && =  &
    // && +  & =  &
    // && + && = &&

    f7(g); // T = int&& is the only solution
}
