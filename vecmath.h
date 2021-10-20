#ifndef VECMATH_H
#define VECMATH_H

/*
 *	This is a GLSL-style linear math library. Made mainly for versatility, but also with thought about performance.
 *	
 * */

#include <iostream>
#include <utility>
#include <cstring>
#include <math.h>

namespace vecmath {
	template<int dim, class T> requires (dim >= 2)
		class vec {
			private: 
				T v[dim];
			public:
				vec();

				template<class ... Args>
					vec(const Args & ... vals) requires (sizeof...(vals) == dim && (std::is_convertible_v<Args, T> && ...));
				

				vec(const T &val);

				vec(const vec<dim, T> &other) {
					*this = other;
				}

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

template<int dim, class T>
vecmath::vec<dim, T>::vec(const T &val) {
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((v[p] = val), ...);
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

/*
 *	##############################################################
 *	other utility vector functions
 * */
template<int dim, class T>
T dot(vecmath::vec<dim, T> &a, vecmath::vec<dim, T> &b) {
	return [&]<std::size_t...p>(std::index_sequence<p...>) -> T{
		((a[p] * b[p]) + ...);
	}
	(std::make_index_sequence<dim>{});
}

template<class T>
vecmath::vec<3, T> cross(vecmath::vec<3, T> &a, vecmath::vec<3, T> &b) {
	return vecmath::vec<3, T>(
		a[1]*b[2] - a[2]*b[1],
		a[2]*b[0] - a[0]*b[2],
		a[0]*b[1] - a[1]*b[0]
		);
}

template<int dim, class T>
T length(vecmath::vec<dim, T> &a) {
	return sqrt(dot(a, a));
}

template<int dim, class T>
T lengthSquared(vecmath::vec<dim, T> &a) {
	return dot(a, a);
}

template<int dim, class T>
vecmath::vec<dim, T> normalize(vecmath::vec<dim, T> &a) {
	return a / length(a);
}

/*
 *	##############################################################
 *	basic math functions applied on vectors
 * */

template<int dim, class T>
vecmath::vec<dim, T> apply(vecmath::vec<dim, T> &v, T (*f)(T)) {
	vecmath::vec<dim, T> n;
	[&]<std::size_t...p>(std::index_sequence<p...>) {
		((n[p] = f(v[p])), ...);
	}
	(std::make_index_sequence<dim>{});
	return n;
}

template<int dim, class T>
vecmath::vec<dim, T> sin(vecmath::vec<dim, T> &v) { return apply(v, std::sin); }

template<int dim, class T>
vecmath::vec<dim, T> cos(vecmath::vec<dim, T> &v) { return apply(v, std::cos); }

template<int dim, class T>
vecmath::vec<dim, T> tan(vecmath::vec<dim, T> &v) { return apply(v, std::tan); }

template<int dim, class T>
vecmath::vec<dim, T> asin(vecmath::vec<dim, T> &v) { return apply(v, std::asin); }

template<int dim, class T>
vecmath::vec<dim, T> acos(vecmath::vec<dim, T> &v) { return apply(v, std::acos); }

template<int dim, class T>
vecmath::vec<dim, T> atan(vecmath::vec<dim, T> &v) { return apply(v, std::atan); }

template<int dim, class T>
vecmath::vec<dim, T> exp(vecmath::vec<dim, T> &v) { return apply(v, std::exp); }

template<int dim, class T>
vecmath::vec<dim, T> log(vecmath::vec<dim, T> &v) { return apply(v, std::log); }

template<int dim, class T>
vecmath::vec<dim, T> exp2(vecmath::vec<dim, T> &v) { return apply(v, std::exp2); }

template<int dim, class T>
vecmath::vec<dim, T> log2(vecmath::vec<dim, T> &v) { return apply(v, std::log2); }

template<int dim, class T>
vecmath::vec<dim, T> sqrt(vecmath::vec<dim, T> &v) { return apply(v, std::sqrt); }

template<int dim, class T>
vecmath::vec<dim, T> abs(vecmath::vec<dim, T> &v) { return apply(v, std::abs); }

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template<int dim, class T>
vecmath::vec<dim, T> sign(vecmath::vec<dim, T> &v) { return apply(v, sign); }

template<int dim, class T>
vecmath::vec<dim, T> floor(vecmath::vec<dim, T> &v) { return apply(v, std::floor); }

template<int dim, class T>
vecmath::vec<dim, T> ceil(vecmath::vec<dim, T> &v) { return apply(v, std::ceil); }





#endif
