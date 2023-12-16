#pragma once


template<typename L, typename R>
struct CL_2
{
};

template<typename T>
struct CL_2<T, T>
{
	using add_type = T;
	using sub_type = T;
	using mul_type = T;
	using div_type = T;

	using karatsuba_mul_type = T;
};

template<typename T>
struct CL_1
{
	using shift_type = T;

	using neg_type = T;
};