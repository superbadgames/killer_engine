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

template <typename T=F32>
struct Color {
	T Red;
	T Green;
	T Blue;

	Color(void): Red(0.0f), Blue(0.0f), Green(0.0f) {}
	Color(T red, T green, T blue) : Red(red), Green(green), Blue(blue) {}
	void operator =(const Color& c) {
		Red    = c.Red;
		Green  = c.Green;
		Blue   = c.Blue;
	}

	void operator =(const Color* c) {
		Red   = c->Red;
		Green = c->Green;
		Blue  = c->Blue;
	}
};

#endif