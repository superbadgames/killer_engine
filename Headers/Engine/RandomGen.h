//========================================================================
//// CMath.h -  useful and fast math functions and approximations
////
////
//// Part of the GameCode4 Application
////
//// GameCode4 is the sample application that encapsulates much of the source code
//// discussed in "Game Coding Complete - 4th Edition" by Mike McShaffry and David
//// "Rez" Graham, published by Charles River Media.
//// ISBN-10: 1133776574 | ISBN-13: 978-1133776574
////
//// If this source code has found it's way to you, and you think it has helped you
//// in any way, do the authors a favor and buy a new copy of the book - there are
//// detailed explanations in it that compliment this code well. Buy a copy at Amazon.com
//// by clicking here:
////    http://www.amazon.com/gp/product/1133776574/ref=olp_product_details?ie=UTF8&me=&seller=
////
//// There's a companion web site at http://www.mcshaffry.com/GameCode/
////
//// The source code is managed and maintained through Google Code:
////    http://code.google.com/p/gamecode4/
////
//// (c) Copyright 2012 Michael L. McShaffry and David Graham
////
//// This program is free software; you can redistribute it and/or
//// modify it under the terms of the GNU Lesser GPL v3
//// as published by the Free Software Foundation.
////
//// This program is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
//// http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
////
//// You should have received a copy of the GNU Lesser GPL v3
//// along with this program; if not, write to the Free Software
//// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
////
////========================================================================
//
//
////========================================================================
////
////  Original Code written at Compulsive Development
////
////========================================================================
/*
	Adopted and used by Killer Wave Entertainment
	Maxwell Miller
*/

#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

//Includes
#include <Engine/Atom.h>
#include <functional>
#include <vector>
#include <time.h>
#include <limits>

namespace KillerMath
{

	//Period parameters
	#define CMATH_N 624
	#define CMATH_M 397
	#define CMATH_MATRIX_A 0x9908b0df //const vector a
	#define CMATH_UPPER_MASK 0x80000000 //most significant w-r bits
	#define CMATH_LOWER_MASK 0x7fffffff //least signficant r bits

	//Tempering parameters
	#define CMATH_TEMPERING_MASK_B 0x9d2c5680
	#define CMATH_TEMPERING_MASK_C 0xefc60000
	#define CMATH_TEMPERING_SHIFT_U(y) (y >> 11)
	#define CMATH_TEMPERING_SHIFT_S(y) (y << 7)
	#define CMATH_TEMPERING_SHIFT_T(y) (y << 15)
	#define CMATH_TEMPERING_SHIFT_L(y) (y >> 18)

	class RandomGen 
	{
		U32 rseed;
		U32	rseed_sp;
		U64 mt[CMATH_N]; //the array for the state vector
		S32 mti; //mti == N+1 means mt[N] is not initialized

		static RandomGen* _instance;

	public:
		static RandomGen* Instance(void);
		
		U32	Random(U32 n);
		
		F32	Random(void);
		
		void SetRandomSeed(U32 n);
		
		U32	 GetRandomSeed(void);
		
		void Randomize(void);

	private:
		RandomGen(void);
	};

}//end namespace

#endif