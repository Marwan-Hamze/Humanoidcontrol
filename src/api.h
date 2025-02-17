#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define Humanoidcontroller_DLLIMPORT __declspec(dllimport)
#  define Humanoidcontroller_DLLEXPORT __declspec(dllexport)
#  define Humanoidcontroller_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define Humanoidcontroller_DLLIMPORT __attribute__((visibility("default")))
#    define Humanoidcontroller_DLLEXPORT __attribute__((visibility("default")))
#    define Humanoidcontroller_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define Humanoidcontroller_DLLIMPORT
#    define Humanoidcontroller_DLLEXPORT
#    define Humanoidcontroller_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef Humanoidcontroller_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define Humanoidcontroller_DLLAPI
#  define Humanoidcontroller_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef Humanoidcontroller_EXPORTS
#    define Humanoidcontroller_DLLAPI Humanoidcontroller_DLLEXPORT
#  else
#    define Humanoidcontroller_DLLAPI Humanoidcontroller_DLLIMPORT
#  endif // Humanoidcontroller_EXPORTS
#  define Humanoidcontroller_LOCAL Humanoidcontroller_DLLLOCAL
#endif // Humanoidcontroller_STATIC