# math_tools-C-library

Lightweight C implementations of common trigonometric and root functions using series expansions and Newton-Raphson iteration. Designed for environments where you want predictable, dependency-free math routines that operate on `long double`.

## What’s included
- Trigonometric: `sin`, `cos`, `tan`, `cot`
- Inverse trig: `arcsin`, `arccos`, `arctan`, `arccot`
- Root: `sqrt`
- Period reduction to speed up series convergence and a configurable epsilon (`EPS`) to control stopping criteria.

## API at a glance
All functions take and return `long double`:

```
long double sin(long double arg);
long double cos(long double arg);
long double tan(long double arg);
long double cot(long double arg);

long double arcsin(long double arg); // domain: [-1, 1]
long double arccos(long double arg);
long double arctan(long double arg);
long double arccot(long double arg);

long double sqrt(long double n);     // n >= 0
```

## Using the library
1) Build the object file:
```
gcc -std=c11 -O2 -c math_tools.c -o math_tools.o
```
2) Link it into your project:
```
gcc your_program.c math_tools.o -o your_program
```
3) Include the header in your code:

```c
#include "math_tools.h"

int main(void) {
    long double angle = 1.0L; // radians
    long double s = sin(angle);
    long double r = sqrt(2.0L);
    // use s and r ...
    return 0;
}
```

## Implementation notes
- `sin`/`cos`: Taylor series with argument reduction to `[0, π/2]` for faster convergence.
- `tan`/`cot`: ratios of the above to avoid duplicating series logic.
- Inverse trig: Newton-Raphson iterations with `EPS` as the convergence threshold; inputs outside valid domains return `INT_MAX` for `arcsin`.
- `sqrt`: Newton-Raphson iteration; starts at `n/2` and stops when successive estimates differ by less than `EPS`.
- Constants: `PI`, `TWO_PI`, and `EPS` are defined in `math_tools.c`. Adjust `EPS` for tighter or looser precision.

## Caveats
- No input validation beyond basic domain checks; NaNs/inf are not handled specially.
- `tan` and `cot` will overflow near their poles when `cos(arg)` or `sin(arg)` approach zero.
- `EPS` is set to `1e-15`; adjust if you need different precision/performance trade-offs.

## Contributing
Feel free to open issues or pull requests for bug fixes, additional functions, or portability improvements.
