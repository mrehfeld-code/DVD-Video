#ifndef DEFINES_H
#define DEFINES_H

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800


#ifndef _CSTDINT_
#include <cstdint>
#endif // _CSTDINT_

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float  float32;
typedef double float64;


// PRINTE Stuff
#define PRINTE_ERROR_SDL2 "SDL2 ERROR"
#define PRINTE_ERROR_OPENGL "OpenGL ERROR"
#define PRINTE_ERROR_MAIN "FATAL ERROR"
#define PRINTE_WARNING_SDL2 "SDL2 Warning"
#define PRINTE_WARNING_OPENGL "OpenGL Warning"

#endif // DEFINES_H

