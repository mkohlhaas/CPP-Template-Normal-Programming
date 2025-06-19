### Links

- [CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 1 of 2)](https://www.youtube.com/watch?v=vwrXHznaYLA&pp=ygUidGVtcGxhdGUgbm9ybWFsIHByb2dyYW1taW5nIGFydGh1cg%3D%3D)
- [CppCon 2016: Arthur O'Dwyer “Template Normal Programming (part 2 of 2)](https://www.youtube.com/watch?v=VIz6xBvwYd8&pp=ygUidGVtcGxhdGUgbm9ybWFsIHByb2dyYW1taW5nIGFydGh1cg%3D%3D)

### Notes for Part 2

- Explicit instantiation looks like explicit/full specialization without the `<>`.

```cpp
// explicit/full specializaion
template<>
int abs(int);

// explicit instantiation
template
int abs(int);

// extern instantiation
// Tell compiler you already instantiated it in another translation unit.
extern template
int abs(int);
```

- `typename`

C++-grammar is not context-free.

```cpp
template<typename T>
void foo(int x)
{
  T::A(x); // T::A could be a function (-> function call) or a type (-> variable declaration)
}

// By default C++ assumes `T::A` is NOT a type!
// Solution: If `T::A` is a type use `typename`.
template<typename T>
void foo(int x)
{
  typename T::A(x);
}
```
