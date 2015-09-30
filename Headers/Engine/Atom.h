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
//=====Killer1 Engine Includes=====
#include <Engine/Color.hpp>

//=====KillerMath Includes=====
#include <KillerMath/Vector.hpp>
#include <KillerMath/Matrix.hpp>
#include <KillerMath/Point.hpp>

//=====OGL Includes=====
#include <GL/gl3w.h>

//=====Windows Includes=====
#include <windows.h>

//=====STD Includes=====
#include <string>
#include <memory>

//=====Global usings=====
//template<typename T>
//using shared_prt = std::shared_prt<T>;

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

//Color typedef
typedef KillerEngine::Color<F32> color;

//Matrix type
typedef KillerMath::Matrix4<F32> matrix;

//Vector type
typedef KillerMath::Vector2<F32> vec;

//Point typedef
typedef KillerMath::Point<F32> point;



#endif