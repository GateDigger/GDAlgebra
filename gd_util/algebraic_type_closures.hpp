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
	using mod_type = T;
};

template<typename T>
struct CL_1
{
	using neg_type = CL_2<T, T>::sub_type;
};