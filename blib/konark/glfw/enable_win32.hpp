#ifndef __BLIB_GLFW_ENABLE_WIN32_INCLUDED__
#define __BLIB_GLFW_ENABLE_WIN32_INCLUDED__

#ifndef __BLIB_WINDOWS_INCLUDED__
#define __BLIB_WINDOWS_INCLUDED__
#include <windows.h>
#endif

//************************************************************************
//****                  GLFW internal functions                       ****
//************************************************************************

//========================================================================
// Low level keyboard hook (system callback) function
// Used to disable system keys under Windows NT
//========================================================================
namespace blib{namespace glfw{

   static LRESULT keyboardHook( int nCode, WPARAM wParam, LPARAM lParam )
   {
      BOOL syskeys = FALSE;
      PKBDLLHOOKSTRUCT p;

      // We are only looking for keyboard events - interpret lParam as a
      // pointer to a KBDLLHOOKSTRUCT
      p = (PKBDLLHOOKSTRUCT) lParam;

      if( nCode == HC_ACTION )
      {
         // We have a keyboard event

         switch( wParam )
         {
         case WM_KEYDOWN:
         case WM_SYSKEYDOWN:
         case WM_KEYUP:
         case WM_SYSKEYUP:
            // Detect: ALT+TAB, ALT+ESC, ALT+F4, CTRL+ESC,
            // LWIN, RWIN, APPS (mysterious menu key)
            syskeys = ( p->vkCode == VK_TAB &&
               p->flags & LLKHF_ALTDOWN ) ||
               ( p->vkCode == VK_ESCAPE &&
               p->flags & LLKHF_ALTDOWN ) ||
               ( p->vkCode == VK_F4 &&
               p->flags & LLKHF_ALTDOWN ) ||
               ( p->vkCode == VK_ESCAPE &&
               (GetKeyState(VK_CONTROL) & 0x8000)) ||
               p->vkCode == VK_LWIN ||
               p->vkCode == VK_RWIN ||
               p->vkCode == VK_APPS;
            break;

         default:
            break;
         }
      }

      // Was it a system key combination (e.g. ALT+TAB)?
      if( syskeys )
      {
         // Pass the key event to our window message loop
         if( _glfwWin.opened )
         {
            PostMessage( _glfwWin.window, (UINT) wParam, p->vkCode, 0 );
         }

         // We've taken care of it - don't let the system know about this
         // key event
         return 1;
      }
      else
      {
         // It's a harmless key press, let the system deal with it
         return CallNextHookEx( _glfwWin.keyboardHook, nCode, wParam, lParam );
      }
   }



   //************************************************************************
   //****               Platform implementation functions                ****
   //************************************************************************

   //========================================================================
   // Enable system keys
   //========================================================================

   void _glfwPlatformEnableSystemKeys( void )
   {
      BOOL dummy;

      // Use different methods depending on operating system version
      if( _glfwLibrary.Sys.winVer >= _GLFW_WIN_NT4 )
      {
         if( _glfwWin.keyboardHook != NULL )
         {
            UnhookWindowsHookEx( _glfwWin.keyboardHook );
            _glfwWin.keyboardHook = NULL;
         }
      }
      else
      {
         (void) SystemParametersInfo( SPI_SETSCREENSAVERRUNNING, FALSE, &dummy, 0 );
      }
   }

   //========================================================================
   // Disable system keys
   //========================================================================

   void _glfwPlatformDisableSystemKeys( void )
   {
      BOOL dummy;

      // Use different methods depending on operating system version
      if( _glfwLibrary.Sys.winVer >= _GLFW_WIN_NT4 )
      {
         // Under Windows NT, install a low level keyboard hook
         _glfwWin.keyboardHook = SetWindowsHookEx( WH_KEYBOARD_LL,
            keyboardHook,
            _glfwLibrary.instance,
            0 );
      }
      else
      {
         // Under Windows 95/98/ME, fool Windows that a screensaver
         // is running => prevents ALT+TAB, CTRL+ESC and CTRL+ALT+DEL
         (void) SystemParametersInfo( SPI_SETSCREENSAVERRUNNING, TRUE, &dummy, 0 );
      }
   }

}
}

#endif // __BLIB_GLFW_ENABLE_WIN32_INCLUDED__
