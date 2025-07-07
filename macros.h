#ifndef MACROS_H
#define MACROS_H

#ifndef ENABLE_FINAL
#define ENABLE_FINAL 1
#endif

#if ENABLE_FINAL
#define FINAL final
#else
#define FINAL
#endif

#define PI 3.14159

#endif