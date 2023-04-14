A C++ std::string wrapper that adds slices and some utility functions.

Example usage:

```C++
#include "cppstr.hpp"
#include <iostream>

int main()
{
    cppstr test = "Test123";

    /* Basic usage like a normal std::string, access to the underlying std::string via test.str() */
    std::cout << test.c_str() << "\n";
    for (auto const& c : test) {
        std::cout << c;
    }
    std::cout << "\n";

    std::cout << "test = \"" << test.c_str() << "\"\n";
    // Slices similar to python
    std::cout << "test[0:4]: " << (test[SLICE(0:4)]).c_str() << "\n";
    std::cout << "test[2:3]: " << (test[SLICE(2:3)]).c_str() << "\n";
    std::cout << "test[0]: " << test[0] << "\n";

    std::cout << "test[-3:]: " << (test[{-3, {}}]).c_str() << "\n";
    std::cout << "test[-3:-1]: " << (test[SLICE(-3:-1)]).c_str() << "\n";

    // Misc functions
    std::cout << "Starts with 'Test' " << test.startswith("Test") << "\n";
    std::cout << "Ends with '123' " << test.endswith("123") << "\n";


    return 0;
}
```
