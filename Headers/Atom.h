/*========================================================================
Call Atom because it is the most basic include file. This is the file
to be included with all other files that are made. This contains the 
type definitions that will be the atomic variable types for the Killer1
Engine (as suggested by Jason Gregory in Game Engine Architecture 2nd 
Edition). It will also contain the basic header files that every other 
class or file will need. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef ATOM_H
#define ATOM_H

//Includes. These will be the files that everything will need to have access to
//User defined Includes
#include <KillerMath.h>
#include <Point.hpp>
#include <Color.hpp>
//Sytem and library includes
#include <GL/gl3w.h>
#include <windows.h>
#include <string>

//Signed Typedefs
typedef signed __int8   S8;
typedef signed __int16  S16;
typedef signed __int32  S32;
typedef signed __int64  S64;

//Unsigned Typedefs
typedef unsigned __int8  U8;
typedef unsigned __int16 U16;
typedef unsigned __int32 U32;
typedef unsigned __int64 U64;

//Floating types
typedef float  F32;
typedef double F64;

//text type 
typedef std::string text;

//Matrix type
typedef Matrix4<F32> matrix;

//Vector type
typedef Vector<F32> vec;

//Point typedef
typedef Point<F32> point;

//Color typedef
typedef Color<F32> color;

#endif