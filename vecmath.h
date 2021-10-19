#ifndef VECMATH_H
#define VECMATH_H

/*
 *	This is a GLSL-style linear math library. Made mainly for versatility, but also with thought about performance.
 *	
 * */


#include <iostream>
#include <math.h>
#include <utility>
#include <cstring>

namespace vecmath {
	template<int dim, class T> requires (dim >= 2)
		class vec {
			private: 
				T v[dim];
			public:
				vec();

				template<class ... Args>
					vec(const Args & ... vals) requires (sizeof...(vals) == dim && (std::is_convertible_v<Args, T> && ...));


				friend std::ostream & operator << <>(std::ostream &out, const vec &v);
				friend std::istream & operator >> <>(std::istream &in, vec &v);

			

				vec<dim, T> &operator = (const vec<dim, T> &other) {
					std::copy(other.v, other.v + dim, v);
					return *this;
				}

				T &operator [] (const int &index) {
					return v[index];
				}

				const T &operator [] (const int &index) const {
					return v[index];
				}
		};
}


/*
 *	###############################################################
 *	default constructor
 * */
template<int dim, class T>
vecmath::vec<dim, T>::vec() {
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = T()) , ... );
	}
	(std::make_index_sequence<dim>{});
}

/*
 *	###############################################################
 *	constructor from all values
 * */
template<int dim, class T>
template<class ... Args>
vecmath::vec<dim, T>::vec(const Args & ... vals) requires (sizeof...(vals) == dim && (std::is_convertible_v<Args, T> && ...)){
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = vals), ...);
	}
	(std::make_index_sequence<dim>{});
}

/*
 *	##############################################################
 *	+ - * / operators with another vec
 * */
template<int dim, class T>
vecmath::vec<dim, T> operator + (const vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] + other[p]) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

template<int dim, class T>
vecmath::vec<dim, T> operator - (const vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] - other[p]) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

template<int dim, class T>
vecmath::vec<dim, T> operator * (const vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] * other[p]) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

template<int dim, class T>
vecmath::vec<dim, T> operator / (const vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] / other[p]) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

/*
 *	##############################################################
 *	+ - * / operators with a scalar
 * */
template<int dim, class T, class Arg>
vecmath::vec<dim, T> operator + (const vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] + other) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

template<int dim, class T, class Arg>
vecmath::vec<dim, T> operator - (const vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] - other) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

template<int dim, class T, class Arg>
vecmath::vec<dim, T> operator * (const vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] * other) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

template<int dim, class T, class Arg>
vecmath::vec<dim, T> operator / (const vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	vecmath::vec<dim, T> v;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = one[p] / other) , ...);
	}
	(std::make_index_sequence<dim>{});
	return v;
}

/*
 *	##############################################################
 *	+=, -=, *=, /= operators with another vector
 * */
template<int dim, class T>
vecmath::vec<dim, T> operator += (vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	one = one + other;
	return one;
}

template<int dim, class T>
vecmath::vec<dim, T> operator -= (vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	one = one - other;
	return one;
}

template<int dim, class T>
vecmath::vec<dim, T> operator *= (vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	one = one * other;
	return one;
}

template<int dim, class T>
vecmath::vec<dim, T> operator /= (vecmath::vec<dim, T> &one, const vecmath::vec<dim, T> &other) {
	one = one / other;
	return one;
}

/*
 *	##############################################################
 *	+=, -=, *=, /= operators with a scalar
 * */
template<int dim, class T, class Arg>
vecmath::vec<dim, T> &operator += (vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	one = one + other;
	return one;
}

template<int dim, class T, class Arg>
vecmath::vec<dim, T> &operator -= (vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	one = one - other;
	return one;
}

template<int dim, class T, class Arg>
vecmath::vec<dim, T> &operator *= (vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	one = one * other;
	return one;
}

template<int dim, class T, class Arg>
vecmath::vec<dim, T> &operator /= (vecmath::vec<dim, T> &one, const Arg &other) requires (std::is_convertible_v<Arg, T>) {
	one = one / other;
	return one;
}

/*
 *	##############################################################
 *	comparison
 * */
template<int dim, class T>
bool operator < (const vecmath::vec<dim, T> &a, const vecmath::vec<dim, T> &b) {
	for(int i = 0; i < dim; i ++) {
		if(a[i] != b[i]) return a[i] < b[i];
	}
	return false;
}

template<int dim, class T>
bool operator > (const vecmath::vec<dim, T> &a, const vecmath::vec<dim, T> &b) {
	for(int i = 0; i < dim; i ++) {
		if(a[i] != b[i]) return a[i] > b[i];
	}
	return false;
}

template<int dim, class T>
bool operator == (const vecmath::vec<dim, T> &a, const vecmath::vec<dim, T> &b) {
	return [&]<std::size_t...p>(std::index_sequence<p...>) -> bool {
		return ((a[p] == b[p]) && ...);
	}
	(std::make_index_sequence<dim>{});
}

template<int dim, class T>
bool operator != (const vecmath::vec<dim, T> &a, const vecmath::vec<dim, T> &b) {
	return !(a == b);
}

template<int dim, class T>
bool operator <= (const vecmath::vec<dim, T> &a, const vecmath::vec<dim, T> &b) {
	return a[0] <= b[0];
}

template<int dim, class T>
bool operator >= (const vecmath::vec<dim, T> &a, const vecmath::vec<dim, T> &b) {
	return a[0] >= b[0];
}

/*
 *	##############################################################
 *	in and out operators
 * */
template<int dim, class T>	
std::ostream &operator << (std::ostream &out, const vecmath::vec<dim, T> &v) {
	out << "vec<dim = " << dim << ", T = " << typeid(T).name() << "> ( ";
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((out << v.v[p] << " ") , ... );
	}
	(std::make_index_sequence<dim>{});
	out << ")";
	return out;
}

template<int dim, class T>	
std::istream &operator >> (std::istream &in, vecmath::vec<dim, T> &v) {
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((in >> v[p]) , ... );
	}
	(std::make_index_sequence<dim>{});
	return in;
}

/*
 *	##############################################################
 *	increment and decrement operators
 * */

template<int dim, class T>
vecmath::vec<dim, T> & operator ++ (vecmath::vec<dim, T> &a) requires (std::is_convertible_v<int, T>){
	a += 1;
	return a;
}

template<int dim, class T>
vecmath::vec<dim, T> operator ++ (vecmath::vec<dim, T> &a, int) requires (std::is_convertible_v<int, T>){
	vecmath::vec<dim, T> b = a;
	a += 1;
	return b;
}

template<int dim, class T>
vecmath::vec<dim, T> & operator -- (vecmath::vec<dim, T> &a) requires (std::is_convertible_v<int, T>){
	a -= 1;
	return a;
}
template<int dim, class T>
vecmath::vec<dim, T> operator -- (vecmath::vec<dim, T> &a, int) requires (std::is_convertible_v<int, T>){
	vecmath::vec<dim, T> b = a;
	a -= 1;
	return b;
}

#endif
