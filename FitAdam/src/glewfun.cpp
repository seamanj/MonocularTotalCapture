#include "glewfun.hpp"

// tj - : definition with initialization
PFNGLCREATESHADERPROC glCreateShader = (PFNGLCREATESHADERPROC)OSMesaGetProcAddress("glCreateShader");
PFNGLSHADERSOURCEPROC glShaderSource = (PFNGLSHADERSOURCEPROC)OSMesaGetProcAddress("glShaderSource");
PFNGLUSEPROGRAMPROC glUseProgram = (PFNGLUSEPROGRAMPROC)OSMesaGetProcAddress("glUseProgram");
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)OSMesaGetProcAddress("glEnableVertexAttribArray");
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC )OSMesaGetProcAddress("glVertexAttribPointer");
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)OSMesaGetProcAddress("glDisableVertexAttribArray");  ;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)OSMesaGetProcAddress("glGenVertexArrays");
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)OSMesaGetProcAddress("glBindVertexArray");
PFNGLGENBUFFERSPROC glGenBuffers = (PFNGLGENBUFFERSPROC)OSMesaGetProcAddress("glGenBuffers");;
PFNGLBINDBUFFERPROC glBindBuffer =(PFNGLBINDBUFFERPROC)OSMesaGetProcAddress("glBindBuffer");;
PFNGLBUFFERDATAPROC glBufferData = (PFNGLBUFFERDATAPROC)OSMesaGetProcAddress("glBufferData");;
PFNGLGETSHADERIVPROC glGetShaderiv = (PFNGLGETSHADERIVPROC)OSMesaGetProcAddress("glGetShaderiv");;
PFNGLCOMPILESHADERPROC glCompileShader = (PFNGLCOMPILESHADERPROC)OSMesaGetProcAddress("glCompileShader");;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)OSMesaGetProcAddress("glGetShaderInfoLog");;
PFNGLCREATEPROGRAMPROC glCreateProgram = (PFNGLCREATEPROGRAMPROC)OSMesaGetProcAddress("glCreateProgram");;
PFNGLATTACHSHADERPROC glAttachShader = (PFNGLATTACHSHADERPROC)OSMesaGetProcAddress("glAttachShader");;
PFNGLLINKPROGRAMPROC glLinkProgram = (PFNGLLINKPROGRAMPROC)OSMesaGetProcAddress("glLinkProgram");;
PFNGLGETPROGRAMIVPROC glGetProgramiv = (PFNGLGETPROGRAMIVPROC)OSMesaGetProcAddress("glGetProgramiv");;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)OSMesaGetProcAddress("glGetProgramInfoLog");;
PFNGLDETACHSHADERPROC glDetachShader = (PFNGLDETACHSHADERPROC)OSMesaGetProcAddress("glDetachShader");;
PFNGLDELETESHADERPROC glDeleteShader = (PFNGLDELETESHADERPROC)OSMesaGetProcAddress("glDeleteShader");;
PFNGLDRAWARRAYSEXTPROC glDrawArraysEXT = (PFNGLDRAWARRAYSEXTPROC)OSMesaGetProcAddress("glDrawArraysEXT");
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)OSMesaGetProcAddress("glGenFramebuffers");;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)OSMesaGetProcAddress("glBindFramebuffer");
PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC)OSMesaGetProcAddress("glFramebufferTexture");
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)OSMesaGetProcAddress("glGenRenderbuffers");;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer =  (PFNGLBINDRENDERBUFFERPROC)OSMesaGetProcAddress("glBindRenderbuffer");
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage =  (PFNGLRENDERBUFFERSTORAGEPROC)OSMesaGetProcAddress("glRenderbufferStorage");
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)OSMesaGetProcAddress("glFramebufferRenderbuffer");
PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)OSMesaGetProcAddress("glCheckFramebufferStatus");
PFNGLDRAWBUFFERSPROC glDrawBuffers = (PFNGLDRAWBUFFERSPROC)OSMesaGetProcAddress("glDrawBuffers");
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv =  (PFNGLUNIFORMMATRIX4FVPROC)OSMesaGetProcAddress("glUniformMatrix4fv");
PFNGLMAPBUFFERPROC glMapBuffer = (PFNGLMAPBUFFERPROC)OSMesaGetProcAddress("glMapBuffer");
PFNGLUNMAPBUFFERPROC glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)OSMesaGetProcAddress("glUnmapBuffer");
PFNGLCLEARBUFFERFVPROC glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)OSMesaGetProcAddress("glClearBufferfv");
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)OSMesaGetProcAddress("glGetUniformLocation");
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)OSMesaGetProcAddress("glGetAttribLocation");
