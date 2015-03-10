/*--------------------------------------------------------------------
A structure to hold basic colors for all Cells to sent to OGL in order
to render things

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
---------------------------------------------------------------------*/

#ifndef COLOR_HPP
#define COLOR_HPP

//User Defined includes
#include <Atom.h>

template <typename T>
struct Color {
	T r;
	T b;
	T g;

	Color(void) : r(0), b(0), g(0) {}
	Color(T red, T blue, T green) : r(red), b(blue), g(green) {}
};

#endif