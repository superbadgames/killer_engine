#ifndef VECTOR3_H
#define VECTOR3_H

#include <Atom.h>
#include <type_traits>

template<typename T>
class Vector3 {
	T _vector[3];
public:
	Vector3(){}
	Vector3(T x, T y, T z): _vector[0](x),
							_vector[1](y),
							_vector[2](z) 
	{
		x = _vector[0];
		y = _vector[1];
		z = _vector[2];
	}

	T* x;
	T* y;
	T* z;
};

#endif