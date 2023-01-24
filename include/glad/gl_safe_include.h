#ifdef GLAD_WGL

#ifndef __gl_h_

#include "gl.h"

#endif

#ifndef GLAD_WGL_H_

#include "wgl.h"

#endif

#elif GLAD_GLX

#ifndef __gl_h_

#include "gl.h"

#endif

#ifndef GLAD_GLX_H_

#include "glx.h"

#endif

#elif GLAD_EGL

#ifndef __gl_h_

#include "gl.h"

#endif

#ifndef GLAD_EGL_H_

#include "egl.h"

#endif

#else

#endif