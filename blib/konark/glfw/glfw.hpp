#ifndef __BLIB_GLFW_INCLUDED__
#define __BLIB_GLFW_INCLUDED__

#ifndef __BLIB_USE_EXTERNAL_GLFW__

#ifndef __BLIB_PLATFORM_CONFIG_INCLUDED__
#include <blib/config/platform_config.hpp>
#endif


/* Include standard OpenGL headers: GLFW uses GL_FALSE/GL_TRUE, and it is
* convenient for the user to only have to include <GL/glfw.h>. This also
* solves the problem with Windows <GL/gl.h> and <GL/glu.h> needing some
* special defines which normally requires the user to include <windows.h>
* (which is not a nice solution for portable programs).
*/

#ifndef __BLIB_GL_INCLUDED__
#define __BLIB_GL_INCLUDED__
#include <GL/gl.h>
#endif

#ifndef GLFW_NO_GLU

#ifndef __BLIB_GLU_INCLUDED__
#define __BLIB_GLU_INCLUDED__
#include <GL/glu.h>
#endif

#endif //GLFW_NO_GLU

/*************************************************************************
* GLFW version
*************************************************************************/
#ifndef __BLIB_GLFW_VERSION_DEFINED__
#define __BLIB_GLFW_VERSION_DEFINED__
#define GLFW_VERSION_MAJOR    2
#define GLFW_VERSION_MINOR    7
#define GLFW_VERSION_REVISION 8
#endif // __BLIB_GLFW_VERSION_DEFINED__


/*************************************************************************
* Input handling definitions
*************************************************************************/
#ifndef __BLIB_GLFW_INPUT_DEFINED__
#define __BLIB_GLFW_INPUT_DEFINED__
/* Key and button state/action definitions */
#define GLFW_RELEASE            0
#define GLFW_PRESS              1

/* Keyboard key definitions: 8-bit ISO-8859-1 (Latin 1) encoding is used
* for printable keys (such as A-Z, 0-9 etc), and values above 256
* represent special (non-printable) keys (e.g. F1, Page Up etc).
*/
#define GLFW_KEY_UNKNOWN      -1
#define GLFW_KEY_SPACE        32
#define GLFW_KEY_SPECIAL      256
#define GLFW_KEY_ESC          (GLFW_KEY_SPECIAL+1)
#define GLFW_KEY_F1           (GLFW_KEY_SPECIAL+2)
#define GLFW_KEY_F2           (GLFW_KEY_SPECIAL+3)
#define GLFW_KEY_F3           (GLFW_KEY_SPECIAL+4)
#define GLFW_KEY_F4           (GLFW_KEY_SPECIAL+5)
#define GLFW_KEY_F5           (GLFW_KEY_SPECIAL+6)
#define GLFW_KEY_F6           (GLFW_KEY_SPECIAL+7)
#define GLFW_KEY_F7           (GLFW_KEY_SPECIAL+8)
#define GLFW_KEY_F8           (GLFW_KEY_SPECIAL+9)
#define GLFW_KEY_F9           (GLFW_KEY_SPECIAL+10)
#define GLFW_KEY_F10          (GLFW_KEY_SPECIAL+11)
#define GLFW_KEY_F11          (GLFW_KEY_SPECIAL+12)
#define GLFW_KEY_F12          (GLFW_KEY_SPECIAL+13)
#define GLFW_KEY_F13          (GLFW_KEY_SPECIAL+14)
#define GLFW_KEY_F14          (GLFW_KEY_SPECIAL+15)
#define GLFW_KEY_F15          (GLFW_KEY_SPECIAL+16)
#define GLFW_KEY_F16          (GLFW_KEY_SPECIAL+17)
#define GLFW_KEY_F17          (GLFW_KEY_SPECIAL+18)
#define GLFW_KEY_F18          (GLFW_KEY_SPECIAL+19)
#define GLFW_KEY_F19          (GLFW_KEY_SPECIAL+20)
#define GLFW_KEY_F20          (GLFW_KEY_SPECIAL+21)
#define GLFW_KEY_F21          (GLFW_KEY_SPECIAL+22)
#define GLFW_KEY_F22          (GLFW_KEY_SPECIAL+23)
#define GLFW_KEY_F23          (GLFW_KEY_SPECIAL+24)
#define GLFW_KEY_F24          (GLFW_KEY_SPECIAL+25)
#define GLFW_KEY_F25          (GLFW_KEY_SPECIAL+26)
#define GLFW_KEY_UP           (GLFW_KEY_SPECIAL+27)
#define GLFW_KEY_DOWN         (GLFW_KEY_SPECIAL+28)
#define GLFW_KEY_LEFT         (GLFW_KEY_SPECIAL+29)
#define GLFW_KEY_RIGHT        (GLFW_KEY_SPECIAL+30)
#define GLFW_KEY_LSHIFT       (GLFW_KEY_SPECIAL+31)
#define GLFW_KEY_RSHIFT       (GLFW_KEY_SPECIAL+32)
#define GLFW_KEY_LCTRL        (GLFW_KEY_SPECIAL+33)
#define GLFW_KEY_RCTRL        (GLFW_KEY_SPECIAL+34)
#define GLFW_KEY_LALT         (GLFW_KEY_SPECIAL+35)
#define GLFW_KEY_RALT         (GLFW_KEY_SPECIAL+36)
#define GLFW_KEY_TAB          (GLFW_KEY_SPECIAL+37)
#define GLFW_KEY_ENTER        (GLFW_KEY_SPECIAL+38)
#define GLFW_KEY_BACKSPACE    (GLFW_KEY_SPECIAL+39)
#define GLFW_KEY_INSERT       (GLFW_KEY_SPECIAL+40)
#define GLFW_KEY_DEL          (GLFW_KEY_SPECIAL+41)
#define GLFW_KEY_PAGEUP       (GLFW_KEY_SPECIAL+42)
#define GLFW_KEY_PAGEDOWN     (GLFW_KEY_SPECIAL+43)
#define GLFW_KEY_HOME         (GLFW_KEY_SPECIAL+44)
#define GLFW_KEY_END          (GLFW_KEY_SPECIAL+45)
#define GLFW_KEY_KP_0         (GLFW_KEY_SPECIAL+46)
#define GLFW_KEY_KP_1         (GLFW_KEY_SPECIAL+47)
#define GLFW_KEY_KP_2         (GLFW_KEY_SPECIAL+48)
#define GLFW_KEY_KP_3         (GLFW_KEY_SPECIAL+49)
#define GLFW_KEY_KP_4         (GLFW_KEY_SPECIAL+50)
#define GLFW_KEY_KP_5         (GLFW_KEY_SPECIAL+51)
#define GLFW_KEY_KP_6         (GLFW_KEY_SPECIAL+52)
#define GLFW_KEY_KP_7         (GLFW_KEY_SPECIAL+53)
#define GLFW_KEY_KP_8         (GLFW_KEY_SPECIAL+54)
#define GLFW_KEY_KP_9         (GLFW_KEY_SPECIAL+55)
#define GLFW_KEY_KP_DIVIDE    (GLFW_KEY_SPECIAL+56)
#define GLFW_KEY_KP_MULTIPLY  (GLFW_KEY_SPECIAL+57)
#define GLFW_KEY_KP_SUBTRACT  (GLFW_KEY_SPECIAL+58)
#define GLFW_KEY_KP_ADD       (GLFW_KEY_SPECIAL+59)
#define GLFW_KEY_KP_DECIMAL   (GLFW_KEY_SPECIAL+60)
#define GLFW_KEY_KP_EQUAL     (GLFW_KEY_SPECIAL+61)
#define GLFW_KEY_KP_ENTER     (GLFW_KEY_SPECIAL+62)
#define GLFW_KEY_KP_NUM_LOCK  (GLFW_KEY_SPECIAL+63)
#define GLFW_KEY_CAPS_LOCK    (GLFW_KEY_SPECIAL+64)
#define GLFW_KEY_SCROLL_LOCK  (GLFW_KEY_SPECIAL+65)
#define GLFW_KEY_PAUSE        (GLFW_KEY_SPECIAL+66)
#define GLFW_KEY_LSUPER       (GLFW_KEY_SPECIAL+67)
#define GLFW_KEY_RSUPER       (GLFW_KEY_SPECIAL+68)
#define GLFW_KEY_MENU         (GLFW_KEY_SPECIAL+69)
#define GLFW_KEY_LAST         GLFW_KEY_MENU

/* Mouse button definitions */
#define GLFW_MOUSE_BUTTON_1      0
#define GLFW_MOUSE_BUTTON_2      1
#define GLFW_MOUSE_BUTTON_3      2
#define GLFW_MOUSE_BUTTON_4      3
#define GLFW_MOUSE_BUTTON_5      4
#define GLFW_MOUSE_BUTTON_6      5
#define GLFW_MOUSE_BUTTON_7      6
#define GLFW_MOUSE_BUTTON_8      7
#define GLFW_MOUSE_BUTTON_LAST   GLFW_MOUSE_BUTTON_8

/* Mouse button aliases */
#define GLFW_MOUSE_BUTTON_LEFT   GLFW_MOUSE_BUTTON_1
#define GLFW_MOUSE_BUTTON_RIGHT  GLFW_MOUSE_BUTTON_2
#define GLFW_MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_3


/* Joystick identifiers */
#define GLFW_JOYSTICK_1          0
#define GLFW_JOYSTICK_2          1
#define GLFW_JOYSTICK_3          2
#define GLFW_JOYSTICK_4          3
#define GLFW_JOYSTICK_5          4
#define GLFW_JOYSTICK_6          5
#define GLFW_JOYSTICK_7          6
#define GLFW_JOYSTICK_8          7
#define GLFW_JOYSTICK_9          8
#define GLFW_JOYSTICK_10         9
#define GLFW_JOYSTICK_11         10
#define GLFW_JOYSTICK_12         11
#define GLFW_JOYSTICK_13         12
#define GLFW_JOYSTICK_14         13
#define GLFW_JOYSTICK_15         14
#define GLFW_JOYSTICK_16         15
#define GLFW_JOYSTICK_LAST       GLFW_JOYSTICK_16

#endif // __BLIB_GLFW_INPUT_DEFINED__

/*************************************************************************
* Other definitions
*************************************************************************/
#ifndef __BLIB_GLFW_OTHER_DEFINED__
#define __BLIB_GLFW_OTHER_DEFINED__
/* glfwOpenWindow modes */
#define GLFW_WINDOW               0x00010001
#define GLFW_FULLSCREEN           0x00010002

/* glfwGetWindowParam tokens */
#define GLFW_OPENED               0x00020001
#define GLFW_ACTIVE               0x00020002
#define GLFW_ICONIFIED            0x00020003
#define GLFW_ACCELERATED          0x00020004
#define GLFW_RED_BITS             0x00020005
#define GLFW_GREEN_BITS           0x00020006
#define GLFW_BLUE_BITS            0x00020007
#define GLFW_ALPHA_BITS           0x00020008
#define GLFW_DEPTH_BITS           0x00020009
#define GLFW_STENCIL_BITS         0x0002000A

/* The following constants are used for both glfwGetWindowParam
* and glfwOpenWindowHint
*/
#define GLFW_REFRESH_RATE         0x0002000B
#define GLFW_ACCUM_RED_BITS       0x0002000C
#define GLFW_ACCUM_GREEN_BITS     0x0002000D
#define GLFW_ACCUM_BLUE_BITS      0x0002000E
#define GLFW_ACCUM_ALPHA_BITS     0x0002000F
#define GLFW_AUX_BUFFERS          0x00020010
#define GLFW_STEREO               0x00020011
#define GLFW_WINDOW_NO_RESIZE     0x00020012
#define GLFW_FSAA_SAMPLES         0x00020013
#define GLFW_OPENGL_VERSION_MAJOR 0x00020014
#define GLFW_OPENGL_VERSION_MINOR 0x00020015
#define GLFW_OPENGL_FORWARD_COMPAT 0x00020016
#define GLFW_OPENGL_DEBUG_CONTEXT 0x00020017
#define GLFW_OPENGL_PROFILE       0x00020018

/* GLFW_OPENGL_PROFILE tokens */
#define GLFW_OPENGL_CORE_PROFILE  0x00050001
#define GLFW_OPENGL_COMPAT_PROFILE 0x00050002

/* glfwEnable/glfwDisable tokens */
#define GLFW_MOUSE_CURSOR         0x00030001
#define GLFW_STICKY_KEYS          0x00030002
#define GLFW_STICKY_MOUSE_BUTTONS 0x00030003
#define GLFW_SYSTEM_KEYS          0x00030004
#define GLFW_KEY_REPEAT           0x00030005
#define GLFW_AUTO_POLL_EVENTS     0x00030006

/* glfwWaitThread wait modes */
#define GLFW_WAIT                 0x00040001
#define GLFW_NOWAIT               0x00040002

/* glfwGetJoystickParam tokens */
#define GLFW_PRESENT              0x00050001
#define GLFW_AXES                 0x00050002
#define GLFW_BUTTONS              0x00050003

/* glfwReadImage/glfwLoadTexture2D flags */
#define GLFW_NO_RESCALE_BIT       0x00000001 /* Only for glfwReadImage */
#define GLFW_ORIGIN_UL_BIT        0x00000002
#define GLFW_BUILD_MIPMAPS_BIT    0x00000004 /* Only for glfwLoadTexture2D */
#define GLFW_ALPHA_MAP_BIT        0x00000008

/* Time spans longer than this (seconds) are considered to be infinity */
#define GLFW_INFINITY 100000.0

#endif // __BLIB_GLFW_OTHER_DEFINED__


/*************************************************************************
* Typedefs
*************************************************************************/
#ifndef __BLIB_GLFW_TYPES_DEFINED__
#define __BLIB_GLFW_TYPES_DEFINED__
namespace blib{namespace glfw{
   /* The video mode structure used by glfwGetVideoModes() */
   struct GLFWvidmode
   {
      int Width, Height;
      int RedBits, BlueBits, GreenBits;
   };

   /* Image/texture information */
   typedef struct GLFWimage
   {
      int Width, Height;
      int Format;
      int BytesPerPixel;
      unsigned char *Data;
   };
   //
   ///* Thread ID */
   //typedef int GLFWthread;
   //
   ///* Mutex object */
   //typedef void * GLFWmutex;
   //
   ///* Condition variable object */
   //typedef void * GLFWcond;

   /* Function pointer types */
   typedef void (*GLFWwindowsizefun)(int,int);
   typedef int  (*GLFWwindowclosefun)(void);
   typedef void (*GLFWwindowrefreshfun)(void);
   typedef void (*GLFWmousebuttonfun)(int,int);
   typedef void (*GLFWmouseposfun)(int,int);
   typedef void (*GLFWmousewheelfun)(int);
   typedef void (*GLFWkeyfun)(int,int);
   typedef void (*GLFWcharfun)(int,int);
   typedef void (*GLFWthreadfun)(void *);


   /*************************************************************************
   * Prototypes
   *************************************************************************/

   /* GLFW initialization, termination and version querying */
   int   glfwInit( void );
   void  glfwTerminate( void );
   void  glfwGetVersion( int *major, int *minor, int *rev );

   /* Window handling */
   int   glfwOpenWindow( int width, int height, int redbits, int greenbits, int bluebits, int alphabits, int depthbits, int stencilbits, int mode );
   void  glfwOpenWindowHint( int target, int hint );
   void  glfwCloseWindow( void );
   void  glfwSetWindowTitle( const char *title );
   void  glfwGetWindowSize( int *width, int *height );
   void  glfwSetWindowSize( int width, int height );
   void  glfwSetWindowPos( int x, int y );
   void  glfwIconifyWindow( void );
   void  glfwRestoreWindow( void );
   void  glfwSwapBuffers( void );
   void  glfwSwapInterval( int interval );
   int   glfwGetWindowParam( int param );
   void  glfwSetWindowSizeCallback( GLFWwindowsizefun cbfun );
   void  glfwSetWindowCloseCallback( GLFWwindowclosefun cbfun );
   void  glfwSetWindowRefreshCallback( GLFWwindowrefreshfun cbfun );

   /* Video mode functions */
   int   glfwGetVideoModes( GLFWvidmode *list, int maxcount );
   void  glfwGetDesktopMode( GLFWvidmode *mode );

   /* Input handling */
   void  glfwPollEvents( void );
   void  glfwWaitEvents( void );
   int   glfwGetKey( int key );
   int   glfwGetMouseButton( int button );
   void  glfwGetMousePos( int *xpos, int *ypos );
   void  glfwSetMousePos( int xpos, int ypos );
   int   glfwGetMouseWheel( void );
   void  glfwSetMouseWheel( int pos );
   void  glfwSetKeyCallback( GLFWkeyfun cbfun );
   void  glfwSetCharCallback( GLFWcharfun cbfun );
   void  glfwSetMouseButtonCallback( GLFWmousebuttonfun cbfun );
   void  glfwSetMousePosCallback( GLFWmouseposfun cbfun );
   void  glfwSetMouseWheelCallback( GLFWmousewheelfun cbfun );

   /* Joystick input */
   int  glfwGetJoystickParam( int joy, int param );
   int  glfwGetJoystickPos( int joy, float *pos, int numaxes );
   int  glfwGetJoystickButtons( int joy, unsigned char *buttons, int numbuttons );

   /* Time */
   double  glfwGetTime( void );
   void    glfwSetTime( double time );
   void    glfwSleep( double time );

   /* Extension support */
   int    glfwExtensionSupported( const char *extension );
   void*  glfwGetProcAddress( const char *procname );
   void   glfwGetGLVersion( int *major, int *minor, int *rev );

   /* Threading support */
   GLFWthread  glfwCreateThread( GLFWthreadfun fun, void *arg );
   void  glfwDestroyThread( GLFWthread ID );
   int   glfwWaitThread( GLFWthread ID, int waitmode );
   GLFWthread  glfwGetThreadID( void );
   GLFWmutex  glfwCreateMutex( void );
   void  glfwDestroyMutex( GLFWmutex mutex );
   void  glfwLockMutex( GLFWmutex mutex );
   void  glfwUnlockMutex( GLFWmutex mutex );
   GLFWcond  glfwCreateCond( void );
   void  glfwDestroyCond( GLFWcond cond );
   void  glfwWaitCond( GLFWcond cond, GLFWmutex mutex, double timeout );
   void  glfwSignalCond( GLFWcond cond );
   void  glfwBroadcastCond( GLFWcond cond );
   int   glfwGetNumberOfProcessors( void );

   /* Enable/disable functions */
   void  glfwEnable( int token );
   void  glfwDisable( int token );

   /* Image/texture I/O support */
   int   glfwReadImage( const char *name, GLFWimage *img, int flags );
   int   glfwReadMemoryImage( const void *data, long size, GLFWimage *img, int flags );
   void  glfwFreeImage( GLFWimage *img );
   int   glfwLoadTexture2D( const char *name, int flags );
   int   glfwLoadMemoryTexture2D( const void *data, long size, int flags );
   int   glfwLoadTextureImage2D( GLFWimage *img, int flags );
} // namespace glfw
} // namespace blib

#endif // __BLIB_GLFW_TYPES_DEFINED__

#endif // __BLIB_USE_INTERNAL_GLFW__

#endif // __BLIB_GLFW_INCLUDED__