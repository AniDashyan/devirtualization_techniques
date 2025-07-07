# Devirtualizing Techniques

## Overview
This project demonstrates techniques to optimize virtual function call performance in C++. It compares virtual calls, direct calls, devirtualized calls, and template-based calls using a `Shape`/`Circle` class hierarchy.

## Build & Run
```bash
# Clone the repository
git clone https://github.com/AniDashyan/devirtualized_tecniques.git
cd devirtualized_tecniques

# Configure the project with CMake
cmake -S . -B build

# Build and run the benchmark
cmake --build build --target benchmark
```


## Example Output
```bash
"=== Comprehensive Performance Comparison ==="
"1. Devirtualization ENABLED + final ENABLED:"
=== Devirtualization Techniques Demo ===

Testing with 10000 objects, 10000 iters each


=== Performance Results ===
Virtual calls:      274445 us
Direct calls:       237926 us
Devirtualized:      221848 us
Template calls:     216889 us

Speedup ratios (compared to virtual calls):
Direct calls:       1.15349x
Devirtualized:      1.23709x
Template calls:     1.26537x
ECHO is off.
"2. Devirtualization ENABLED + final DISABLED:"
=== Devirtualization Techniques Demo ===

Testing with 10000 objects, 10000 iters each


=== Performance Results ===
Virtual calls:      231335 us
Direct calls:       222598 us
Devirtualized:      217402 us
Template calls:     220979 us

Speedup ratios (compared to virtual calls):
Direct calls:       1.03925x
Devirtualized:      1.06409x
Template calls:     1.04686x
ECHO is off.
"3. Devirtualization DISABLED + final ENABLED:"
=== Devirtualization Techniques Demo ===

Testing with 10000 objects, 10000 iters each


=== Performance Results ===
Virtual calls:      244642 us
Direct calls:       232145 us
Devirtualized:      232021 us
Template calls:     234493 us

Speedup ratios (compared to virtual calls):
Direct calls:       1.05383x
Devirtualized:      1.0544x
Template calls:     1.04328x
ECHO is off.
"4. Devirtualization DISABLED + final DISABLED:"
=== Devirtualization Techniques Demo ===

Testing with 10000 objects, 10000 iters each


=== Performance Results ===
Virtual calls:      233680 us
Direct calls:       226456 us
Devirtualized:      249645 us
Template calls:     260342 us

Speedup ratios (compared to virtual calls):
Direct calls:       1.0319x
Devirtualized:      0.936049x
Template calls:     0.897589x
```

## How it Works?
This project shows ways to optimize virtual function calls in C++ by reducing or eliminating runtime overhead. The key techniques are:

* **Final Keyword:** The final specifier on the `Circle` class prevents further inheritance, allowing the compiler to devirtualize calls to `area()` when the type is known, avoiding the virtual table lookup.

* **Devirtualization Flags:** Compilers like GCC and Clang can optimize calls when the type is known at compile-time, especially with flags like `-O2` or `-fdevirtualize`. The project uses a vector of `Circle` objects to show this, as the compiler can inline the `area()` function.

* **Direct Calls:** Non-virtual functions (`direct_area()`) skip the virtual table, providing the best performance.

* **Template-Based Calls:** Using templates (`calc_area_template()`) resolves calls at compile-time, improving performance by avoiding runtime overhead.

The benchmark measures the time for virtual, direct, devirtualized, and template-based calls, showing speed improvements with devirtualization techniques.
