#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <type_traits>
#include <vector>

namespace function_overloading
{
    int
    f1(int a)
    {
        std::cout << a << std::endl;
        return 4;
    }

    int
    f1(double a)
    {
        std::cout << a << std::endl;
        return 4;
    }

    // Error: clang: Functions that differ only in their return type cannot be overloaded.
    // double
    // f1(int a)
    // {
    //     std::cout << a << std::endl;
    //     return 4.0;
    // }

} // namespace function_overloading

namespace motivation
{
    double
    abs(double x)
    {
        return (x >= 0) ? x : -x;
    }

    float
    abs(float x)
    {
        return (x >= 0) ? x : -x;
    }

    int
    abs(int x)
    {
        return (x >= 0) ? x : -x;
    }

} // namespace motivation

namespace function_templates
{
    template <typename T>
    T
    myabs(T x)
    {
        return (x >= 0) ? x : -x;
    }

} // namespace function_templates

namespace class_templates
{
    template <typename T>
    struct mylist
    {
        T          data;
        mylist<T> *next;
    };

} // namespace class_templates

namespace classes_are_still_classes
{
    // normal struct
    struct S
    {
        static int sdm;
    };

    int S::sdm = 42;

    // templated struct
    template <class T>
    struct ST
    {
        static int sdm;
    };

    template <class T>
    int ST<T>::sdm = 42;

} // namespace classes_are_still_classes

namespace variable_templates
{
    template <typename T>
    struct is_void
    {
        static const bool value = false;
    };

    template <typename T>
    const bool is_void_v = false;

} // namespace variable_templates

namespace best_of_both_worlds
{
    template <typename T>
    struct is_void
    {
        static constexpr bool value = false;
    };

    template <typename T>
    constexpr bool is_void_v = is_void<T>::value;

} // namespace best_of_both_worlds

namespace alias_templates
{
    using myvec_double = std::vector<double>;

    template <typename T>
    using myvec = std::vector<T>;

} // namespace alias_templates

namespace literally_the_same_type
{
    using myint = int;

    template <typename T>
    using myvec = std::vector<T>;

    void
    f(const myint &m)
    {
        (void)m;
    };

    void
    g(const myvec<int> &m)
    {
        (void)m;
    };

} // namespace literally_the_same_type

namespace type_deduction
{
    template <typename T>
    T
    abs(T x)
    {
        return (x >= 0) ? x : -x;
    }

} // namespace type_deduction

namespace rules_of_template_type_deduction
{
    template <typename T>
    void
    foo(T)
    {
        puts(__PRETTY_FUNCTION__);
    }

    template <typename T, typename U>
    void
    f(T, U)
    {
        puts(__PRETTY_FUNCTION__);
    };

    template <typename T>
    void
    g(T, T)
    {
        puts(__PRETTY_FUNCTION__);
    };

} // namespace rules_of_template_type_deduction

namespace puzzle_1
{
    template <typename T, typename U>
    void
    foo(std::array<T, sizeof(U)>, //
        std::array<U, sizeof(T)>, //
        int)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace puzzle_1

namespace puzzle_2
{
    template <typename R, typename A>
    void
    foo(R (*)(A))
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace puzzle_2

namespace many_people_have_seen_this
{
    short
    f()
    {
        return 42;
    };

} // namespace many_people_have_seen_this

namespace call_a_specialization_explicitly
{
    template <typename T>
    T
    abs(T x)
    {
        puts(__PRETTY_FUNCTION__);
        return (x >= 0) ? x : -x;
    }

    template <typename T, typename U>
    void
    add(T, U)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace call_a_specialization_explicitly

namespace default_template_parameters
{
    template <typename T = char *>
    void
    add()
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace default_template_parameters

namespace template_type_deduction_real_deal_1
{
    template <typename T>
    void
    f(T)
    {
        puts(__PRETTY_FUNCTION__);
    }

    template <typename T>
    void
    f(T *)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace template_type_deduction_real_deal_1

namespace template_type_deduction_real_deal_2
{
    template <typename T>
    void
    f(T &)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace template_type_deduction_real_deal_2

namespace template_type_deduction_real_deal_3
{
    template <typename T>
    void
    f(T &&)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace template_type_deduction_real_deal_3

namespace case_in_which_refref_is_deduced
{
    template <typename T>
    void
    f(void (*)(T))
    {
        puts(__PRETTY_FUNCTION__);
    }

    void
    g(int &&)
    {
    }

} // namespace case_in_which_refref_is_deduced

namespace reference_and_cv_collapsing
{
    template <typename T>
    void
    f(T &&)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace reference_and_cv_collapsing

namespace deducing_Tref_not_Trefref
{
    template <typename T>
    void
    f(T &)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace deducing_Tref_not_Trefref

namespace rvalues_are_kinda_like_const_lvalues
{
    template <typename T>
    void
    f(T &)
    {
        puts(__PRETTY_FUNCTION__);
    }

} // namespace rvalues_are_kinda_like_const_lvalues

namespace defining_a_template_specialization_1
{
    // primary
    template <typename T>
    struct is_void
    {
        static constexpr bool value = false;
    };

    // explicit/fill specialization
    template <>
    struct is_void<void>
    {
        static constexpr bool value = true;
    };

} // namespace defining_a_template_specialization_1

namespace defining_a_template_specialization_2
{
    template <typename T>
    T
    abs(T x)
    {
        return (x >= 0) ? x : -x;
    }

    template <>
    int
    // abs<int>(int x)
    // abs<>(int x)
    abs(int x) // syntactic sugar
    {
        if (x == INT_MIN)
        {
            throw std::domain_error("oops");
        }
        return (x >= 0) ? x : -x;
    }

} // namespace defining_a_template_specialization_2

namespace partial_specialization_1
{
    template <typename T>
    constexpr bool is_array = false;

    template <typename Tp>
    constexpr bool is_array<Tp[]> = true;

} // namespace partial_specialization_1

namespace partial_specialization_2
{
    // primary template
    template <typename T>
    constexpr bool is_array = false;

    // partial specializations
    template <typename Tp>
    constexpr bool is_array<Tp[]> = true;

    // partial specializations
    template <typename Tp, int N>
    constexpr bool is_array<Tp[N]> = true;

    // full specialization
    template <>
    constexpr bool is_array<void> = true;

} // namespace partial_specialization_2

namespace which_specialization_is_called
{
    template <typename T>
    class A
    {
    };

    template <>
    class A<void>
    {
    };

    template <typename Tp>
    class A<Tp *>
    {
    };

    template <typename Tp>
    class A<Tp **>
    {
    };

} // namespace which_specialization_is_called

namespace function_templates_cannot_be_partially_specialized_1
{
    // Function templates cannot be partially specialized !

    template <typename T>
    bool
    is_pointer(T)
    {
        return false;
    }

    // this is NOT a partial specialization
    template <typename T>
    bool
    is_pointer(T *)
    {
        return true;
    }

    // Now we have two primary function templates in the same overload set. Dangerous!

} // namespace function_templates_cannot_be_partially_specialized_1

namespace function_templates_cannot_be_partially_specialized_2
{
    // Depending where you put the full specialization (after first or second primary function template) you get
    // possibly different behavior. Dangerous! If you put the full specialization after first primary function template
    // it will be a specialization for the first primary template. If you put the full specialization after second
    // primary function template it will be a specialization for the second primary template.

    // 1st primary function template
    template <typename T>
    bool
    is_pointer(T)
    {
        return false;
    }

    // full specialization
    template <>
    bool
    is_pointer(void *)
    {
        puts(__PRETTY_FUNCTION__);
        return true;
    }

    // 2nd primary function template
    template <typename T>
    bool
    is_pointer(T *)
    {
        return true;
    }

} // namespace function_templates_cannot_be_partially_specialized_2

namespace how_to_partially_specialize_a_function
{
    // How to partially specialize a function

    // primary template
    template <typename T>
    struct is_pointer_impl
    {
        static bool
        _()
        {
            return false;
        }
    };

    // partial specialization (classes can be partially specialized!)
    template <typename T>
    struct is_pointer_impl<T *>
    {
        static bool
        _()
        {
            return true;
        }
    };

    template <typename T>
    bool
    is_this_really_a_pointer(T)
    {
        return is_pointer_impl<T>::_();
    }

} // namespace how_to_partially_specialize_a_function

// Kind of Template | Type deduction | Full specialization allowed ? | Partial specialization allowed ? |
// -----------------+----------------+-------------------------------+-----------------------------------
//     Function     |     Yes        |            Yes                |             No                   |
//     Class        |     No         |            Yes                |             Yes                  |
//     Variable     |     No         |            Yes                |             Yes                  |
//     Alias        |     No         |            No                 |             No                   |
// -----------------+----------------+-------------------------------+-----------------------------------

namespace bad_tag_dispatch
{
    template <typename Element>
    struct tree_iterator
    {
        tree_iterator &operator++(); // NOTE: inside definition of class template the <> are not needed.
                                     // Otherwise we had to write `tree_iterator<Element>)`
    };

    template <typename Element>
    struct vector_iterator
    {
        vector_iterator &operator++();
        vector_iterator  operator+();
    };

    template <typename Element>
    struct vector
    {
        using iterator = vector_iterator<Element>;
    };

    template <typename Element>
    struct tree
    {
        using iterator = tree_iterator<Element>;
    };

    template <typename Iter>
    Iter
    advance(Iter begin, int n)
    {
        for (int i = 0; i < n; i++)
        {
            ++begin;
        }
        return begin;
    }

    // advance specialized for vectors
    // WRONG: function templates cannot be partially specialized -> Don't do it!
    template <typename Element>
    vector_iterator<Element>
    advance(vector_iterator<Element> begin, int n)
    {
        return begin + n;
    }

} // namespace bad_tag_dispatch

namespace good_tag_dispatch
{
    template <typename Element>
    struct tree_iterator
    {
        tree_iterator &operator++();
        using supports_plus = std::false_type;
    };

    template <typename Element>
    struct vector_iterator
    {
        vector_iterator &operator++();
        vector_iterator  operator+();
        using supports_plus = std::true_type;
    };

    template <typename Element>
    struct vector
    {
        using iterator = vector_iterator<Element>;
    };

    template <typename Element>
    struct tree
    {
        using iterator = tree_iterator<Element>;
    };

    template <typename Iter>
    Iter
    advance_impl(Iter begin, int n, std::false_type)
    {
        for (int i = 0; i < n; i++)
        {
            ++begin;
        }
        return begin;
    }

    template <typename Iter>
    Iter
    advance_impl(Iter begin, int n, std::true_type)
    {
        return begin + n;
    }

    template <typename Iter>
    auto
    advance(Iter begin, int n)
    {
        // NOTE: `typename` is not strictly necessary in C++20.
        // NOTE: We instantiate a value of type Iter::supports_plus (you can use `()` or `{}`). See below.
        return advance_impl(begin, n, typename Iter::supports_plus());
    }

} // namespace good_tag_dispatch

namespace dependent_names
{
    // Actually compiler can distinguish what is a declaration and a function call.

    template <typename T>
    void
    foo3(int x)
    {
        // If T::A is a function, this is a function call, i.e. A(x).
        T::A(x);
    }

    template <typename T>
    void
    foo4(int x)
    {
        // If T::A is a type, this is a declaration, i.e. `int(y)`, same as `int y`.
        typename T::A(y);

        (void)x;
        (void)y;
    }

    struct S1
    {
        static void A(int) {};
    };

    struct S2
    {
        using A = int;
    };

} // namespace dependent_names

namespace refer_to_template
{
    template <typename T>
    void
    foo(int x)
    {
        T::template A<0>(x);
    }

    struct S2
    {
        template <int N>
        static void
        A(int)
        {
        }
    };

} // namespace refer_to_template

int
main()
{
    {
        // function overloading (params are significant)
        // Functions that differ only in their return type cannot be overloaded.

        using namespace function_overloading;

        std::cout << "=== Function Overloading\n" << std::endl;

        f1(42);   // 42
        f1(42.0); // 42
    }

    {
        // Without templates we need a bunch of overloaded functions
        // and implicit conversions can also be a pain in the ass.

        using namespace motivation;

        std::cout << "\n=== Motivation\n" << std::endl;

        std::cout << abs(-42.0) << std::endl; // 42
        std::cout << abs(-42.f) << std::endl; // 42

        // std::cout << abs(-42) << std::endl; // error: Call to 'abs' is ambiguous
    }

    {
        using namespace function_templates;

        std::cout << "\n=== Function Templates\n" << std::endl;

        std::cout << myabs(-42.0) << std::endl;    // 42
        std::cout << myabs<int>(-42) << std::endl; // 42
        std::cout << myabs(-42) << std::endl;      // 42

        double (*foo)(double) = myabs<double>;
        std::cout << foo(-42.0) << std::endl;      // 42
    }

    {
        using namespace class_templates;

        std::cout << "\n=== Class Templates\n" << std::endl;

        mylist<int>    *intlist [[maybe_unused]]{};
        mylist<double> *doublelist [[maybe_unused]]{};
    }

    {
        using namespace classes_are_still_classes;

        std::cout << "\n=== Class are still Classes\n" << std::endl;

        std::cout << S::sdm << std::endl;        // 42
        std::cout << ST<char>::sdm << std::endl; // 42
    }

    {
        // Variable templates are syntactic sugar.
        // A variable template is exactly 100% equivalent to a static data member of a class template.

        using namespace variable_templates;

        std::cout << "\n=== Variable Templates\n" << std::endl;

        std::cout << std::boolalpha;
        std::cout << is_void<int>::value << std::endl; // false
        std::cout << is_void_v<int> << std::endl;      // false
    }

    {
        using namespace best_of_both_worlds;

        std::cout << "\n=== Best of both worlds in the STL\n" << std::endl;

        std::cout << std::boolalpha;
        std::cout << is_void<int>::value << std::endl; // false
        std::cout << is_void_v<int> << std::endl;      // false
    }

    {
        using namespace alias_templates;

        std::cout << "\n=== Alias Templates\n" << std::endl;

        static_assert(std::is_same_v<myvec_double, std::vector<double>>);
        static_assert(std::is_same_v<myvec<double>, std::vector<double>>);
    }

    {
        using namespace literally_the_same_type;

        std::cout << "\n=== Literally the same type\n" << std::endl;

        int i{};
        f(i); // OK because myint is int

        std::vector<int> v = {1, 2, 3, 4};
        g(v); // OK because myvec<int> is std::vector<int>
    }

    {
        using namespace type_deduction;

        std::cout << "\n=== Type Deduction\n" << std::endl;

        double (*f)(double) = abs<double>;

        std::cout << f(-42.0) << std::endl;      // 42
        std::cout << abs<int>(-42) << std::endl; // 42
    }

    {
        using namespace rules_of_template_type_deduction;

        std::cout << "\n=== Rules of Template Type Deduction\n" << std::endl;

        foo(4);       // [T = int]
        foo(4.2);     // [T = double]
        foo("hello"); // [T = const char *]

        f(1, 2);      // [T = int, U = int]
        g(1, 2);      // [T = int]
        // g(1, 2u);  // error: no matching function for call to g(int, unsigned int)
    }

    {
        using namespace puzzle_1;

        std::cout << "\n=== Puzzle #1\n" << std::endl;

        foo(std::array<int, 8>{},    // [T = int; U = double]
            std::array<double, 4>{}, //
            0.0);

        // foo(std::array<int, 9>{}, std::array<double, 4>{}, 0.0); // error: No matching function for call to 'foo'
    }

    {
        using namespace puzzle_2;

        std::cout << "\n=== Puzzle #2\n" << std::endl;

        foo(+[](double x) { return int(x); }); // [with R = int; A = double]

        // foo([](double x) { return int(x); }); // error
    }

    {
        using namespace many_people_have_seen_this;

        std::cout << "\n=== Many People have seen this\n" << std::endl;

        // std::max(f(), 42);                    // error: No matching function for call to 'max'

        // cast (too verbose)
        std::cout << std::max(static_cast<int>(f()), 24) << std::endl; // 42
        // make template paarameters explicit
        std::cout << std::max<int>(f(), 24) << std::endl; // 42
    }

    {
        using namespace call_a_specialization_explicitly;

        std::cout << "\n=== Call a Specialization explicitly\n" << std::endl;

        std::cout << abs<int>('x') << std::endl;  // [T = int]    | 120
        std::cout << abs<double>(3) << std::endl; // [T = double] | 3

        add<int, int>('x', 3.1);                  // [T = int, U = int]
        add<int>('x', 3.1);                       // [T = int, U = double]
        add<>('x', 3.1);                          // [T = char, U = double]
        add('x', 3.1);                            // [T = char, U = double]
    }

    {
        using namespace default_template_parameters;

        std::cout << "\n=== Default Template Parameters\n" << std::endl;

        add<int>(); // [T = int]
        add<>();    // [T = char *]
        add();      // [T = char *]
    }

    {
        using namespace template_type_deduction_real_deal_1;

        std::cout << "\n=== Template Type Deduction #1\n" << std::endl;

        int i{};
        f(i);  // [T = int]
        f(&i); // [T = int]
    }

    {
        using namespace template_type_deduction_real_deal_2;

        std::cout << "\n=== Template Type Deduction #2\n" << std::endl;

        int i{};
        f(i); // [T = int]
    }

    {
        using namespace template_type_deduction_real_deal_3;

        std::cout << "\n=== Template Type Deduction #3\n" << std::endl;

        // Combining two reference types mins the number of ampersands (reference collapsing):
        // &  +  & =  &
        // &  + && =  &
        // && +  & =  &
        // && + && = &&

        int i{};
        f(42);           // [T = int]
        f(std::move(i)); // [T = int]
        f(i);            // [T = int&]
    }

    {
        using namespace case_in_which_refref_is_deduced;

        std::cout << "\n=== Case in which && is deduced\n" << std::endl;

        f(g); // [T=int&&]
    }

    {
        using namespace reference_and_cv_collapsing;

        std::cout << "\n=== Reference and CV-Collapsing\n" << std::endl;

        const int i = 42;
        f(i);            // [T=const int&]
        f(std::move(i)); // [T=const int]
    }

    {
        using namespace deducing_Tref_not_Trefref;

        std::cout << "\n=== Deducing T&, not T&&\n" << std::endl;

        int i = 42;
        f(static_cast<int &>(i));          // [T=int]
        f(static_cast<volatile int &>(i)); // [T=volatile int]

        f(static_cast<const int &>(i));    // [T=const int]
        f(static_cast<const int &&>(i));   // [T=const int] (!)

        // f(static_cast<int &&>(i));          // ERROR
        // f(static_cast<volatile int &&>(i)); // ERROR
    }

    {
        using namespace rvalues_are_kinda_like_const_lvalues;

        std::cout << "\n=== r-Values are kinda like const lvalues\n" << std::endl;

        int i = 42;
        f(static_cast<int &>(i));        // [T = int]
        f(static_cast<const int &>(i));  // [T = const int]
        f(static_cast<const int &&>(i)); // [T = const int]
        // f(static_cast<int &&>(i));    // error
    }

    {
        using namespace defining_a_template_specialization_1;

        std::cout << "\n=== Defining a Template Specialization #1\n" << std::endl;

        std::cout << is_void<int>::value << std::endl;  // false
        std::cout << is_void<void>::value << std::endl; // true
    }

    {
        using namespace partial_specialization_1;

        std::cout << "\n=== Partial Specialization #1\n" << std::endl;

        std::cout << is_array<int> << std::endl;   // false
        std::cout << is_array<int[]> << std::endl; // true
    }

    {
        using namespace partial_specialization_2;

        std::cout << "\n=== Partial Specialization #2\n" << std::endl;

        std::cout << is_array<int> << std::endl;    // false
        std::cout << is_array<int[]> << std::endl;  // true
        std::cout << is_array<int[8]> << std::endl; // true
    }

    {
        using namespace which_specialization_is_called;

        std::cout << "\n=== Which Specialization is being called ?\n" << std::endl;

        A<int>     a1 [[maybe_unused]]; // uses primary
        A<int *>   a2 [[maybe_unused]]; // uses 1st partial specialization
        A<int ***> a3 [[maybe_unused]]; // uses 2nd partial specialization
        A<void>    a4 [[maybe_unused]]; // uses full specialization
    }

    // {
    //     // Deduce T such that T&& is the target category (r-value/l-value).
    //     // Another way to put it: What is T such that T&& leads to target type?
    //     f6(42);           // r-value ref (42 = int&& = target category) -> T = int (T&& would also work)
    //                       // What is T such that T&& = int &&? -> T = int
    //     f6(std::move(i)); // same as previous
    //     f6(i);            // l-value ref (i = int& = target category) -> T = int&
    //                       // What is T such that T&& = int&? -> T = int&
    //
    //                       // Combining two reference types mins the number of ampersands (reference collapsing):
    //     // &  +  & =  &
    //     // &  + && =  &
    //     // && +  & =  &
    //     // && + && = &&
    //
    //     f7(g); // T = int&& is the only solution
    //
    //     // l-value references
    //     f8(static_cast<int &>(i)); // ok
    //     // f8(static_cast<int &&>(i));    // error
    //     f8(static_cast<const int &&>(i)); // ok (!)
    //
    //     // l-value references with volatile
    //     f8(static_cast<int &>(i));          // ok
    //     f8(static_cast<volatile int &>(i)); // ok
    //     // f8(static_cast<int &&>(i));          // error
    //     // f8(static_cast<volatile int &&>(i)); // error
    //
    //     // l-value references with const
    //     f8(static_cast<int &>(i));       // ok
    //     f8(static_cast<const int &>(i)); // ok
    //     // f8(static_cast<int &&>(i));    // error
    //     f8(static_cast<const int &&>(i)); // ok (!)
    //
    //     // You can pass an r-value ref to a function expecting a const l-value ref.
    //     // r-values are kind of like const l-values.
    //
    //     // Passing an r-value ref to a function expecting an l-value ref is not allowed
    //     f9(i);
    //     // f9(42);           // error
    //     // f9(std::move(i)); // error
    //
    //     // Passing an r-value ref to a function expecting a const l-value ref is allowed !!!
    //     f10(i);
    //     f10(42);
    //     f10(std::move(i));
    //
    //     std::cout << std::boolalpha;
    //     std::cout << is_void<int>::value << std::endl;  // false
    //     std::cout << is_void<void>::value << std::endl; // true
    //
    //     std::cout << is_array<int> << std::endl;        // false
    //     std::cout << is_array<int[]> << std::endl;      // true
    //
    //     A<int *>   a1 [[maybe_unused]];                 // uses 1st partial specialization
    //     A<int ***> a2 [[maybe_unused]];                 // uses 2nd partial specialization
    //     A<void>    a3 [[maybe_unused]];                 // uses full specialization
    //
    //     // Kind of Template | Type deduction happens ? | Full specialization allowed ? | Partial specialization
    //     allowed
    //     // ? |
    //     //
    //     -----------------+--------------------------+-------------------------------+-----------------------------------
    //     // Function         |         Yes              |            Yes                |             No | Class | No
    //     |
    //     // Yes                |             Yes                  | Variable         |         No               | Yes
    //     |
    //     // Yes                  | Alias            |         No               |            No                 | No |
    //     //
    //     -----------------+--------------------------+-------------------------------+-----------------------------------
    //
    //     // Variable templates are actually special kind of class templates. (Class templates with static member
    //     // variable.)
    //
    //     std::cout << is_this_really_a_pointer(i) << std::endl;  // false
    //     std::cout << is_this_really_a_pointer(&i) << std::endl; // true
    //
    //     {
    //         // Dependent names
    //
    //         // C++'s grammar is not context-free.
    //
    //         using namespace dependent_names;
    //
    //         foo3<S1>(0);
    //         foo4<S2>(0);
    //     }
    //
    //     {
    //         // Similarly to refer to a template
    //
    //         using namespace refer_to_template;
    //
    //         foo<S2>(42);
    //     }
    // }
}
