/*========================================================================
A structure to hold basic colors for all Cells to sent to OGL in order
to render things

There will be 4 values per color so that it can be sent to a vec4 in OGL
before it is used to actually control the colors of anything in the shader.
This is stored in an array for convience of passing the whole array out 
when the time comes. 

This is not free to use;
and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
========================================================================*/

#ifndef COLOR_HPP
#define COLOR_HPP

//=====Killer1 includes=====
#include <Engine/Atom.h>

namespace KillerEngine{
	
	template <typename T>
	struct Color {
		T _values[4];

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Color(void) 
		{
			_values[0] = _values[1] = _values[2] = 0.0f;
			_values[3] = 1.0f;
		}
		
		Color(T red, T green, T blue) 
		{
			_values[0] = red;
			_values[1] = green;
			_values[2] = blue;
			_values[3] = 1.0f;
		}
		
		Color(T red, T green, T blue, T alpha) 
		{
			_values[0] = red;
			_values[1] = green;
			_values[2] = blue;
			_values[3] = alpha;
		}
		
		Color(const Color<T>& c) 
		{
			_values[0] = c.GetRed();
			_values[1] = c.GetGreen();
			_values[2] = c.GetBlue();
			_values[3] = c.GetAlpha();
		}


//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
		Color& operator=(const Color& c) 
		{
			_values[0] = c.GetRed();
			_values[1] = c.GetGreen();
			_values[2] = c.GetBlue();
			_values[3] = c.GetAlpha();

			return *this;
		}
		
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		const T* Get(void) 	 	const { return _values; }
		
		const T  GetRed(void)   const { return _values[0]; }
		
		const T  GetGreen(void) const { return _values[1]; }
		
		const T  GetBlue(void)  const { return _values[2]; }
		
		const T  GetAlpha(void) const { return _values[3]; }

		void SetRed(const T r)   { _values[0] = r; }
		
		void SetGree(const T g)  { _values[1] = g; }
		
		void SetBlue(const T b)  { _values[2] = b; }
		
		void SetAlpha(const T a) { _values[3] = a; }

	};
}//End namespace
#endif