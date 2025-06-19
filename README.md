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
// Tell compiler instantiation already happened in another translation unit.
extern template
int abs(int);
```
