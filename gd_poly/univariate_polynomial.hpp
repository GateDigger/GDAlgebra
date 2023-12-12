#pragma once

#include <string>
#include <iostream>
#include <initializer_list>

#include "../gd_util/algebraic_type_closures.hpp"

//#define CONSOLE_LOG

#define _NEQ0_BY_PTR(LOW, HIGH) ((LOW) < (HIGH))
#define _EQ0_BY_PTR(LOW, HIGH) (!((LOW) < (HIGH)))

namespace gda
{
#pragma region INTERNAL_ROUTINES

	template<typename T>
	/*
		Extracts the most significant bit from an integer; surely there is not a single instruction for this...
	*/
	static T extract_msb_internal(T arg)
	{
		T result = static_cast<T>(1);
		for (;;)
		{
			arg >>= 1;

			if (!arg)
			{
				break;
			}

			result <<= 1;
		}
		return result;
	}

	template<typename T>
	/*
		Returns a pointer one past the actual leading coefficient, or nullptr if there is none
	*/
	static T* rewind_trailing_zeroes_internal(T* low, T* high)
	{
		if (_NEQ0_BY_PTR(low, high))
		{
			T* iter = high;
			for (--iter;; --iter)
			{
				if (*iter != static_cast<T>(0))
				{
					return iter + 1;
				}
				if (iter == low)
				{
					return nullptr;
				}
			}
		}
		return nullptr;
	}

	template<typename T, T VAL>
	static void init_internal(T* low, T* high)
	{
		for (T* iter = low; iter != high; ++iter)
		{
			*iter = VAL;
		}
	}

	template<typename T, bool PERFORM_TRIM, bool OWNERSHIP_FLAG>
	static void trim_internal(T** target_low, T** target_high)
	{
		if constexpr (PERFORM_TRIM)
		{
			*target_high = gda::rewind_trailing_zeroes_internal<T>(*target_low, *target_high);
			if (!*target_high)
			{
				if constexpr (OWNERSHIP_FLAG)
				{
					delete[] * target_low;
				}
				*target_low = nullptr;
			}
		}
	}

	template<typename T_SOURCE, typename T_TARGET>
	static void copy_internal(T_SOURCE* source_low, T_SOURCE* source_high, T_TARGET* target_low)
	{
		T_TARGET* target_iter = target_low;
		T_SOURCE* source_iter = source_low;
		for (; source_iter != source_high; ++source_iter, ++target_iter)
		{
			*target_iter = static_cast<T_TARGET>(*source_iter);
		}
	}

	template<typename T>
	static void copy_internal(T* source_low, T* source_high, T* target_low)
	{
		T* target_iter = target_low;
		T* source_iter = source_low;
		for (; source_iter != source_high; ++source_iter, ++target_iter)
		{
			*target_iter = *source_iter;
		}
	}

	template<typename T_SOURCE, typename T_TARGET, bool AUTO_TRIM_TARGET>
	static void dupe_internal(T_SOURCE* source_low, T_SOURCE* source_high, T_TARGET** result_low, T_TARGET** result_high)
	{
		if (_NEQ0_BY_PTR(source_low, source_high))
		{
			*result_low = new T_TARGET[source_high - source_low];
			*result_high = *result_low + (source_high - source_low);
			gda::copy_internal<T_SOURCE, T_TARGET>(source_low, source_high, *result_low);
			gda::trim_internal<T_TARGET, AUTO_TRIM_TARGET, true>(result_low, result_high);
		}
		else
		{
			*result_low = nullptr;
			*result_high = nullptr;
		}
	}

	template<typename T, bool AUTO_TRIM_SOURCE, bool AUTO_TRIM_TARGET>
	static void dupe_internal(T* source_low, T* source_high, T** result_low, T** result_high)
	{
		gda::trim_internal<T, AUTO_TRIM_TARGET && !AUTO_TRIM_SOURCE, false>(&source_low, &source_high);

		if (_NEQ0_BY_PTR(source_low, source_high))
		{
			*result_low = new T[source_high - source_low];
			*result_high = *result_low + (source_high - source_low);
			gda::copy_internal<T>(source_low, source_high, *result_low);
		}
		else
		{
			*result_low = nullptr;
			*result_high = nullptr;
		}
	}

	template<typename T, bool AUTO_TRIM_SOURCE, bool AUTO_TRIM_TARGET>
	static void take_ownership_internal(T* source_low, T* source_high, T** target_low, T** target_high)
	{
		gda::trim_internal<T, AUTO_TRIM_TARGET && !AUTO_TRIM_SOURCE, true>(&source_low, &source_high);

		*target_low = source_low;
		*target_high = source_high;
	}

#pragma endregion

	template<typename T_COEF, typename T_DEG, bool AUTO_TRIM = true>
	class uvp
	{
	private:
		T_COEF* _coefs_low,
			* _coefs_high;

#pragma region CTORS

	public:
		constexpr uvp()
			:_coefs_low(nullptr), _coefs_high(nullptr)
		{
#ifdef CONSOLE_LOG
			std::cout << "ctor()" << std::endl;
#endif
		}

	public:
		uvp(const T_COEF& a_0)
		{
#ifdef CONSOLE_LOG
			std::cout << "ctor(" << a_0 << ")";
#endif
			if constexpr (AUTO_TRIM)
			{
				if (a_0 == static_cast<T_COEF>(0))
				{
					_coefs_low = nullptr;
					_coefs_high = nullptr;
				}
				else
				{
					_coefs_low = new T_COEF[1];
					*_coefs_low = a_0;
					_coefs_high = _coefs_low + 1;
				}
			}
			else
			{
				_coefs_low = new T_COEF[1];
				*_coefs_low = a_0;
				_coefs_high = _coefs_low + 1;
			}
#ifdef CONSOLE_LOG
			std::cout << " -> (" << _coefs_low << " - " << _coefs_high << ")" << std::endl;
#endif
		}

	public:
		explicit uvp(T_COEF* coefs_low, T_COEF* coefs_high)
		{
#ifdef CONSOLE_LOG
			std::cout << "ctor(" << coefs_low << "; " << coefs_high << ")";
#endif

			gda::take_ownership_internal<T_COEF, false, AUTO_TRIM>(coefs_low, coefs_high, &_coefs_low, &_coefs_high);

#ifdef CONSOLE_LOG
			std::cout << " -> (" << _coefs_low << " - " << _coefs_high << ")" << std::endl;
#endif
		}

	public:
		template<typename OTHER_T_COEF, bool OTHER_AUTO_TRIM>
		uvp(const uvp<OTHER_T_COEF, T_DEG, OTHER_AUTO_TRIM>& other)
		{
#ifdef CONSOLE_LOG
			std::cout << "ctor(const &" << other << ")";
#endif

			gda::dupe_internal<OTHER_T_COEF, T_COEF, AUTO_TRIM>(other.cc_iter_ctl(), other.lc_iter_ctl(), &_coefs_low, &_coefs_high);

#ifdef CONSOLE_LOG
			std::cout << " -> (" << _coefs_low << " - " << _coefs_high << ")" << std::endl;
#endif
		}

	public:
		template<bool OTHER_AUTO_TRIM>
		uvp(const uvp<T_COEF, T_DEG, OTHER_AUTO_TRIM>& other)
		{
#ifdef CONSOLE_LOG
			std::cout << "ctor(const &" << other << ")";
#endif

			gda::dupe_internal<T_COEF, OTHER_AUTO_TRIM, AUTO_TRIM>(other.cc_iter_ctl(), other.lc_iter_ctl(), &_coefs_low, &_coefs_high);

#ifdef CONSOLE_LOG
			std::cout << " -> (" << _coefs_low << " - " << _coefs_high << ")" << std::endl;
#endif
		}

	public:
		/*
			This ctor was nonsense
		*/
		template<typename OTHER_T_COEF, bool OTHER_AUTO_TRIM>
		uvp(uvp<OTHER_T_COEF, T_DEG, OTHER_AUTO_TRIM>&& other) = delete;

	public:
		template<bool OTHER_AUTO_TRIM>
		uvp(uvp<T_COEF, T_DEG, OTHER_AUTO_TRIM>&& other) noexcept
		{
#ifdef CONSOLE_LOG
			std::cout << "ctor(&&" << other << ")";
#endif

			gda::take_ownership_internal<T_COEF, OTHER_AUTO_TRIM, AUTO_TRIM>(other.cc_iter_ctl(), other.lc_iter_ctl(), &_coefs_low, &_coefs_high);

			other.wipe_internal_shallow();

#ifdef CONSOLE_LOG
			std::cout << " -> (" << _coefs_low << " - " << _coefs_high << ")" << std::endl;
#endif
		}

	public:
		~uvp()
		{
#ifdef CONSOLE_LOG
			std::cout << "dtor(" << _coefs_low << "; " << _coefs_high << ")" << std::endl;
#endif
			delete[] _coefs_low;
		}

#pragma endregion

#pragma region ASSIGNMENTS

	public:
		template<typename OTHER_T_COEF, bool OTHER_AUTO_TRIM>
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator =(const uvp<OTHER_T_COEF, T_DEG, OTHER_AUTO_TRIM>& other)
		{
#ifdef CONSOLE_LOG
			std::cout << "assignment(&" << other << "); (" << _coefs_low << " - " << _coefs_high << ")";
#endif
			if (static_cast<const void*>(this) == static_cast<const void*>(&other))
			{
#ifdef CONSOLE_LOG
				std::cout << std::endl;
#endif
				return *this;
			}

			delete[] _coefs_low;

			gda::dupe_internal<OTHER_T_COEF, T_COEF, AUTO_TRIM>(other.cc_iter_ctl(), other.lc_iter_ctl(), &_coefs_low, &_coefs_high);

			return *this;
		}

	public:
		template<bool OTHER_AUTO_TRIM>
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator =(const uvp<T_COEF, T_DEG, OTHER_AUTO_TRIM>& other)
		{
#ifdef CONSOLE_LOG
			std::cout << "assignment(&" << other << "); (" << _coefs_low << " - " << _coefs_high << ")";
#endif
			if (static_cast<const void*>(this) == static_cast<const void*>(&other))
			{
#ifdef CONSOLE_LOG
				std::cout << std::endl;
#endif
				return *this;
			}

			delete[] _coefs_low;

			gda::dupe_internal<T_COEF, OTHER_AUTO_TRIM, AUTO_TRIM>(other.cc_iter_ctl(), other.lc_iter_ctl(), &_coefs_low, &_coefs_high);

#ifdef CONSOLE_LOG
			std::cout << " -> (" << _coefs_low << " - " << _coefs_high << ")" << std::endl;
#endif

			return *this;
		}

	public:
		/*
			This assignment was nonsense aswell
		*/
		template<typename OTHER_T_COEF, bool OTHER_AUTO_TRIM>
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator =(uvp<OTHER_T_COEF, T_DEG, OTHER_AUTO_TRIM>&& other) = delete;

	public:
		template<bool OTHER_AUTO_TRIM>
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator =(uvp<T_COEF, T_DEG, OTHER_AUTO_TRIM>&& other) noexcept
		{
#ifdef CONSOLE_LOG
			std::cout << "assignment(&&" << other << "); (" << _coefs_low << " - " << _coefs_high << ")";
#endif
			if (static_cast<void*>(this) == static_cast<void*>(&other))
			{
#ifdef CONSOLE_LOG
				std::cout << std::endl;
#endif
				return *this;
			}

			delete[] _coefs_low;

			gda::take_ownership_internal<T_COEF, OTHER_AUTO_TRIM, AUTO_TRIM>(other.cc_iter_ctl(), other.lc_iter_ctl(), &_coefs_low, &_coefs_high);

			other.wipe_internal_shallow();

#ifdef CONSOLE_LOG
			std::cout << " -> (" << _coefs_low << " - " << _coefs_high << ")" << std::endl;
#endif
			return *this;
		}

#pragma endregion

#pragma region PROPS

	public:
		/*
			Returns the degree of the polynomial
		*/
		T_DEG deg() const
		{
			if constexpr (AUTO_TRIM)
			{
				return _coefs_high - _coefs_low - 1;
			}
			else
			{
				T_COEF* t_coefs_high = gda::rewind_trailing_zeroes_internal<T_COEF>(_coefs_low, _coefs_high);
				return t_coefs_high ? t_coefs_high - _coefs_low - 1 : static_cast<T_DEG>(-1);
			}
		}

	public:
		/*
			Returns whether the polynomial is zero
		*/
		bool is_zero() const
		{
			if constexpr (AUTO_TRIM)
			{
				return _EQ0_BY_PTR(_coefs_low, _coefs_high);
			}
			else
			{
				T_COEF* t_coefs_high = gda::rewind_trailing_zeroes_internal<T_COEF>(_coefs_low, _coefs_high);
				return t_coefs_high ? false : true;
			}
		}

	public:
		/*
			Returns a pointer to the initial (constant) coefficient of the polynomial, for iteration purposes
		*/
		T_COEF* cc_iter_ctl() const
		{
			return _coefs_low;
		}

	public:
		/*
			Returns a pointer one past the terminal (leading) coefficient of the polynomial, for iteration purposes
		*/
		T_COEF* lc_iter_ctl() const
		{
			return _coefs_high;
		}

	public:
		/*
			Returns the constant coefficient of the polynomial
		*/
		T_COEF cc() const
		{
			return _NEQ0_BY_PTR(_coefs_low, _coefs_high) ? *_coefs_low : static_cast<T_COEF>(0);
		}

	public:
		/*
			Returns the leading coefficient of the polynomial
		*/
		T_COEF lc() const
		{
			if constexpr (AUTO_TRIM)
			{
				return _NEQ0_BY_PTR(_coefs_low, _coefs_high) ? *(_coefs_high - 1) : static_cast<T_COEF>(0);
			}
			else
			{
				T_COEF* t_coefs_high = gda::rewind_trailing_zeroes_internal<T_COEF>(_coefs_low, _coefs_high);
				return t_coefs_high ? *(t_coefs_high - 1) : static_cast<T_COEF>(0);
			}
		}

#pragma endregion

#pragma region UTIL

	public:
		void trim()
		{
			gda::trim_internal<T_COEF, !AUTO_TRIM, true>(&_coefs_low, &_coefs_high);
		}

	public:
		void wipe_internal_shallow()
		{
			_coefs_low = nullptr;
			_coefs_high = nullptr;
		}

	public:
		void wipe_internal()
		{
			delete[] _coefs_low;
			_coefs_low = nullptr;
			_coefs_high = nullptr;
		}

#pragma endregion

#pragma region SUBSCRIPT

	public:
		/*
			Bound checks included; negative index provides access from the end
		*/
		const T_COEF& operator[](const T_DEG index) const noexcept
		{
			return index < static_cast<T_DEG>(0) ?
				_coefs_high - _coefs_low < -index ? static_cast<T_COEF>(0) : *(index + _coefs_high) :
				_coefs_high - _coefs_low > index ? *(_coefs_low + index) : static_cast<T_COEF>(0);
		}

	public:
		/*
			Provides unprotected access, do your own bound checks; negative index provides access from the end
		*/
		T_COEF& operator[](const T_DEG index) noexcept
		{
			return index < static_cast<T_DEG>(0) ?
				_coefs_high[index] :
				_coefs_low[index];
		}

#pragma endregion

#pragma region CALL

	public:
		T_COEF operator ()(const T_COEF& x) const
		{
			T_COEF result = static_cast<T_COEF>(0);

			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl(),
				* t_iter;
			if constexpr (AUTO_TRIM)
			{
				t_iter = t_high;
			}
			else
			{
				t_iter = gda::rewind_trailing_zeroes_internal<T_COEF>(t_low, t_high);
			}

			if (!t_iter)
			{
				return result;
			}

			for (--t_iter; t_iter != t_low; --t_iter)
			{
				result += *t_iter;
				result *= x;
			}
			result += *t_iter;

			return result;
		}

#pragma endregion

#pragma region ADD

	public:
		template <bool OTHER_AUTO_TRIM>
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator += (const uvp<T_COEF, T_DEG, OTHER_AUTO_TRIM>& other)
		{
			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl(),
				* o_low = other.cc_iter_ctl(),
				* o_high = other.lc_iter_ctl();

			gda::trim_internal<T_COEF, !OTHER_AUTO_TRIM, false>(&o_low, &o_high);

			if (_EQ0_BY_PTR(o_low, o_high))
			{
				return *this;
			}

			if (t_high - t_low < o_high - o_low)
			{
				T_COEF* result_low = new T_COEF[o_high - o_low],
					* result_high = result_low + (o_high - o_low),
					* result_iter = result_low,
					* t_iter = t_low,
					* o_iter = o_low;

				for (; t_iter != t_high; ++t_iter, ++o_iter, ++result_iter)
				{
					*result_iter = *t_iter + *o_iter;
				}

				for (; o_iter != o_high; ++o_iter, ++result_iter)
				{
					*result_iter = *o_iter;
				}

				*this = uvp<T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
				return *this;
			}
			else
			{
				T_COEF* t_iter = t_low,
					* o_iter = o_low;
				for (; o_iter != o_high; ++o_iter, ++t_iter)
				{
					*t_iter += *o_iter;
				}

				gda::trim_internal<T_COEF, AUTO_TRIM, true>(&_coefs_low, &_coefs_high);

				return *this;
			}
		}

#pragma endregion

#pragma region SUB

	public:
		template <bool OTHER_AUTO_TRIM>
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator -= (const uvp<T_COEF, T_DEG, OTHER_AUTO_TRIM>& other)
		{
			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl(),
				* o_low = other.cc_iter_ctl(),
				* o_high = other.lc_iter_ctl();

			gda::trim_internal<T_COEF, !OTHER_AUTO_TRIM, false>(&o_low, &o_high);

			if (_EQ0_BY_PTR(o_low, o_high))
			{
				return *this;
			}

			if (t_high - t_low < o_high - o_low)
			{
				T_COEF* result_low = new T_COEF[o_high - o_low],
					* result_high = result_low + (o_high - o_low),
					* result_iter = result_low,
					* t_iter = t_low,
					* o_iter = o_low;

				for (; t_iter != t_high; ++t_iter, ++o_iter, ++result_iter)
				{
					*result_iter = *t_iter - *o_iter;
				}

				for (; o_iter != o_high; ++o_iter, ++result_iter)
				{
					*result_iter = -*o_iter;
				}

				*this = uvp<T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
				return *this;
			}
			else
			{
				T_COEF* t_iter = t_low,
					o_iter = o_low;
				for (; o_iter != o_high; ++o_iter, ++t_iter)
				{
					*t_iter -= *o_iter;
				}

				gda::trim_internal<T_COEF, AUTO_TRIM, true>(&_coefs_low, &_coefs_high);

				return *this;
			}
		}

#pragma endregion

#pragma region MUL

	public:
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator *= (const T_COEF& other)
		{
			if constexpr (AUTO_TRIM)
			{
				if (other == static_cast<T_COEF>(0))
				{
					delete[] _coefs_low;
					_coefs_low = nullptr;
					_coefs_high = nullptr;
					return *this;
				}
			}

			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl(),
				* t_iter;

			gda::trim_internal<T_COEF, !AUTO_TRIM, false>(&t_low, &t_high);

			for (t_iter = t_low; t_iter != t_high; ++t_iter)
			{
				*t_iter *= other;
			}

			gda::trim_internal<T_COEF, AUTO_TRIM, true>(&_coefs_low, &_coefs_high);

			return *this;
		}

#pragma endregion

#pragma region DIV

	public:
		uvp<T_COEF, T_DEG, AUTO_TRIM>& operator /= (const T_COEF& other)
		{
			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl(),
				* t_iter;

			gda::trim_internal<T_COEF, !AUTO_TRIM, false>(&t_low, &t_high);

			for (t_iter = t_low; t_iter != t_high; ++t_iter)
			{
				*t_iter /= other;
			}

			gda::trim_internal<T_COEF, AUTO_TRIM, true>(&_coefs_low, &_coefs_high);

			return *this;
		}

#pragma endregion

#pragma region UTIL

	public:
		uvp<T_COEF, T_DEG, false> pad_to(const T_DEG length) const
		{
			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl();

			if (t_high - t_low < length)
			{
				T_COEF* result_low = new T_COEF[length],
					* result_high = result_low + length;

				gda::copy_internal<T_COEF>(t_low, t_high, result_low);
				gda::init_internal<T_COEF, static_cast<T_COEF>(0)>(result_low + (t_high - t_low), result_high);

				return uvp<T_COEF, T_DEG, false>(result_low, result_high);
			}
			else
			{
				T_COEF* result_low,
					* result_high;
				gda::dupe_internal<T_COEF, AUTO_TRIM, false>(t_low, t_high, &result_low, &result_high);
				return uvp<T_COEF, T_DEG, false>(result_low, result_high);
			}
		}

	public:
		T_COEF sum_coefs() const
		{
			T_COEF result = static_cast<T_COEF>(0);
			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl();

			for (T_COEF* t_iter = t_low; t_iter != t_high; ++t_iter)
			{
				result += *t_iter;
			}

			return result;
		}

#pragma endregion

#pragma region RAND

	public:
		static uvp<T_COEF, T_DEG, AUTO_TRIM> make_random(const T_DEG deg, T_COEF(*rcg)())
		{
			if (deg < static_cast<T_DEG>(0))
			{
				return uvp<T_COEF, T_DEG, AUTO_TRIM>();
			}

			T_COEF* result_low = new T_COEF[deg + 1],
				* result_high = result_low + (deg + 1);

			for (T_COEF* result_iter = result_low; result_iter != result_high; ++result_iter)
			{
				*result_iter = (*rcg)();
			}

			return uvp<T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
		}

#pragma endregion

#pragma region STR_OPS

	public:
		std::string to_string_lth() const
		{
			std::ostringstream builder;

			T_COEF* t_low = cc_iter_ctl(),
				* t_high = lc_iter_ctl();
			if constexpr (!AUTO_TRIM)
			{
				t_high = gda::rewind_trailing_zeroes_internal<T_COEF>(t_low, t_high);
				if (!t_high)
				{
					t_low = nullptr;
				}
			}

			if (_EQ0_BY_PTR(t_low, t_high))
			{
				return "0";
			}

			T_COEF* t_iter;
			for (t_iter = t_low;; ++t_iter)
			{
				if (t_iter == t_high)
				{
					goto RETURN;
				}

				if (to_string_lc(*t_iter, t_iter - t_low, builder))
				{
					break;
				}
			}

			for (++t_iter;; ++t_iter)
			{
				if (t_iter == t_high)
				{
					goto RETURN;
				}

				to_string_tc(*t_iter, t_iter - t_low, builder);
			}

		RETURN:
			return builder.str();
		}

	private:
		static constexpr char VAR = 'x';

	private:
		static bool to_string_lc(const T_COEF& a_i, const T_DEG i, std::ostringstream& builder)
		{
			if (a_i == static_cast<T_COEF>(0))
			{
				return false;
			}

			builder << a_i;
			if (i < static_cast<T_DEG>(1))
			{
				return true;
			}

			builder << VAR;
			if (i < static_cast<T_DEG>(2))
			{
				return true;
			}

			builder << "^";
			builder << i;

			return true;
		}

	private:
		static bool to_string_tc(const T_COEF& a_i, const T_DEG i, std::ostringstream& builder)
		{
			if (a_i == static_cast<T_COEF>(0))
			{
				return false;
			}

			if (a_i < static_cast<T_COEF>(0))
			{
				builder << " - ";
				builder << -a_i;
			}
			else
			{
				builder << " + ";
				builder << a_i;
			}

			if (i < static_cast<T_DEG>(1))
			{
				return true;
			}

			builder << VAR;
			if (i < static_cast<T_DEG>(2))
			{
				return true;
			}

			builder << "^";
			builder << i;

			return true;
		}

#pragma endregion
	};

#pragma region LEN

	template<typename T_COEF, typename T_DEG, bool AUTO_TRIM>
	static T_DEG len_raw(const uvp<T_COEF, T_DEG, AUTO_TRIM>& p)
	{
		return static_cast<T_DEG>(p.lc_iter_ctl() - p.cc_iter_ctl());
	}

#pragma endregion

#pragma region SHIFT

	template<typename T_COEF, typename OUT_T_COEF = CL_1<T_COEF>::shift_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> shr_internal(T_COEF* left_low, T_COEF* left_high, const T_DEG right)
	{
		OUT_T_COEF* result_low = new OUT_T_COEF[left_high - left_low - right],
			* result_high = result_low + (left_high - left_low - right),
			* result_iter = result_low;

		for (T_COEF* left_iter = left_low + right; left_iter != left_high; ++left_iter, ++result_iter)
		{
			*result_iter = static_cast<OUT_T_COEF>(*left_iter);
		}

		return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
	}

	template<typename T_COEF, typename OUT_T_COEF = CL_1<T_COEF>::shift_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> shl_internal(T_COEF* left_low, T_COEF* left_high, const T_DEG right)
	{
		OUT_T_COEF* result_low = new OUT_T_COEF[left_high - left_low + right],
			* result_high = result_low + (left_high - left_low + right),
			* result_iter = result_low;

		for (; result_iter != result_low + right; ++result_iter)
		{
			*result_iter = static_cast<OUT_T_COEF>(0);
		}

		for (T_COEF* left_iter = left_low; left_iter != left_high; ++left_iter, ++result_iter)
		{
			*result_iter = static_cast<OUT_T_COEF>(*left_iter);
		}

		return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
	}

	template<typename T_COEF, typename OUT_T_COEF = CL_1<T_COEF>::shift_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> operator >>(const uvp<T_COEF, T_DEG, AUTO_TRIM>& left, const T_DEG right)
	{
		if constexpr (AUTO_TRIM)
		{
			if (right < static_cast<T_DEG>(0))
			{
				if (static_cast<T_DEG>(0) < (left.lc_iter_ctl() - left.cc_iter_ctl()))
				{
					return shl_internal<T_COEF, OUT_T_COEF, T_DEG, AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), -right);
				}
				return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
			}
			else
			{
				if (right < (left.lc_iter_ctl() - left.cc_iter_ctl()))
				{
					return shr_internal<T_COEF, OUT_T_COEF, T_DEG, AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), right);
				}
				return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
			}
		}
		else
		{
			if (right < static_cast<T_DEG>(0))
			{
				return shl_internal<T_COEF, OUT_T_COEF, T_DEG, AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), -right);
			}
			else
			{
				if (right < (left.lc_iter_ctl() - left.cc_iter_ctl()))
				{
					return shr_internal<T_COEF, OUT_T_COEF, T_DEG, AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), right);
				}
				return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
			}
		}
	}

	template<typename T_COEF, typename OUT_T_COEF = CL_1<T_COEF>::shift_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> operator <<(const uvp<T_COEF, T_DEG, AUTO_TRIM>& left, const T_DEG right)
	{
		return left >> -right;
	}

#pragma endregion

#pragma region ADD

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::add_type, typename T_DEG, bool AUTO_TRIM>
	static uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> add_internal(const L_T_COEF* left_low, const L_T_COEF* left_high, const R_T_COEF* right_low, const R_T_COEF* right_high)
	{
		const L_T_COEF* left_iter = left_low;
		const R_T_COEF* right_iter = right_low;
		if (left_high - left_low < right_high - right_low)
		{
			OUT_T_COEF* result_low = new OUT_T_COEF[right_high - right_low],
				* result_high = result_low + (right_high - right_low),
				* result_iter = result_low;

			for (; left_iter != left_high; ++left_iter, ++right_iter, ++result_iter)
				*result_iter = *left_iter + *right_iter;

			for (; right_iter != right_high; ++right_iter, ++result_iter)
				*result_iter = *right_iter;

			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
		}
		else
		{
			OUT_T_COEF* result_low = new OUT_T_COEF[left_high - left_low],
				* result_high = result_low + (left_high - left_low),
				* result_iter = result_low;

			for (; right_iter != right_high; ++left_iter, ++right_iter, ++result_iter)
				*result_iter = *left_iter + *right_iter;

			for (; left_iter != left_high; ++left_iter, ++result_iter)
				*result_iter = *left_iter;

			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
		}
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::add_type, typename T_DEG, bool L_AUTO_TRIM, bool R_AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM> operator +(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		return add_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), right.cc_iter_ctl(), right.lc_iter_ctl());
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::add_type, typename T_DEG, bool L_AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, L_AUTO_TRIM> operator +(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const R_T_COEF& right)
	{
		return add_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, L_AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), &right, &right + 1);
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::add_type, typename T_DEG, bool R_AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, R_AUTO_TRIM> operator +(const L_T_COEF& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		return add_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, R_AUTO_TRIM>(&left, &left + 1, right.cc_iter_ctl(), right.lc_iter_ctl());
	}

#pragma endregion

#pragma region SUB

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::add_type, typename T_DEG, bool AUTO_TRIM>
	static uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> sub_internal(const L_T_COEF* left_low, const L_T_COEF* left_high, const R_T_COEF* right_low, const R_T_COEF* right_high)
	{
		const L_T_COEF* left_iter = left_low;
		const R_T_COEF* right_iter = right_low;
		if (left_high - left_low < right_high - right_low)
		{
			OUT_T_COEF* result_low = new OUT_T_COEF[right_high - right_low],
				* result_high = result_low + (right_high - right_low),
				* result_iter = result_low;

			for (; left_iter != left_high; ++left_iter, ++right_iter, ++result_iter)
				*result_iter = *left_iter - *right_iter;

			for (; right_iter != right_high; ++right_iter, ++result_iter)
				*result_iter = -*right_iter;

			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
		}
		else
		{
			OUT_T_COEF* result_low = new OUT_T_COEF[left_high - left_low],
				* result_high = result_low + (left_high - left_low),
				* result_iter = result_low;

			for (; right_iter != right_high; ++left_iter, ++right_iter, ++result_iter)
				*result_iter = *left_low - *right_iter;

			for (; left_iter != left_high; ++left_iter, ++result_iter)
				*result_iter = *left_iter;

			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
		}
	}

	template<typename T_COEF, typename OUT_T_COEF = CL_1<T_COEF>::neg_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> operator -(const uvp<T_COEF, T_DEG, AUTO_TRIM>& p)
	{
		T_COEF* p_low = p.cc_iter_ctl(),
			* p_high = p.lc_iter_ctl();

		if (_EQ0_BY_PTR(p_low, p_high))
		{
			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
		}

		OUT_T_COEF* result_low = new OUT_T_COEF[p_high - p_low],
			* result_high = result_low + (p_high - p_low),
			* result_iter = result_low;

		for (; p_low != p_high; ++p_low, ++result_iter)
		{
			*result_iter = -*p_low;
		}

		return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::sub_type, typename T_DEG, bool L_AUTO_TRIM, bool R_AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM> operator -(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		return sub_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), right.cc_iter_ctl(), right.lc_iter_ctl());
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::sub_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> operator -(const uvp<L_T_COEF, T_DEG, AUTO_TRIM>& left, const R_T_COEF& right)
	{
		return sub_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), &right, &right + 1);
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::sub_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> operator -(const L_T_COEF& left, const uvp<R_T_COEF, T_DEG, AUTO_TRIM>& right)
	{
		return sub_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, AUTO_TRIM>(&left, &left + 1, right.cc_iter_ctl(), right.lc_iter_ctl());
	}

#pragma endregion

#pragma region MUL

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::mul_type, typename T_DEG>
	static void schoolbook_mul_internal(L_T_COEF* left_low, L_T_COEF* left_high,
		R_T_COEF* right_low, R_T_COEF* right_high,
		OUT_T_COEF* result_low)
	{
		OUT_T_COEF* result_iter;

		L_T_COEF* left_iter;
		R_T_COEF* right_iter;
		for (left_iter = left_low; left_iter != left_high; ++left_iter)
		{
			for (right_iter = right_low, result_iter = result_low + (left_iter - left_low); right_iter != right_high; ++right_iter, ++result_iter)
			{
				*result_iter += *left_iter * *right_iter;
			}
		}
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::mul_type, typename T_DEG, bool L_AUTO_TRIM, bool R_AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM> schoolbook_mul(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		if (left.is_zero())
			return uvp<OUT_T_COEF, T_DEG>();

		if (right.is_zero())
			return uvp<OUT_T_COEF, T_DEG>();

		OUT_T_COEF* result_low = new OUT_T_COEF[left.deg() + right.deg() + 1],
			* result_high = result_low + left.deg() + right.deg() + 1;

		init_internal<OUT_T_COEF, static_cast<OUT_T_COEF>(0)>(result_low, result_high);
		schoolbook_mul_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG>(left.cc_iter_ctl(), left.lc_iter_ctl(),
			right.cc_iter_ctl(), right.lc_iter_ctl(),
			result_low);

		return uvp<OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM>(result_low, result_high);
	}

	template<typename T_COEF>
	static void accumulate_add_karatsuba_internal(T_COEF* source_low, T_COEF* source_high, T_COEF* target_low)
	{
		for (T_COEF* source_iter = source_low, *target_iter = target_low; source_iter != source_high; ++source_iter, ++target_iter)
		{
			*target_iter += *source_iter;
		}
	}

	template<typename T_COEF>
	static void accumulate_sub_karatsuba_internal(T_COEF* source_low, T_COEF* source_high, T_COEF* target_low)
	{
		for (T_COEF* source_iter = source_low, *target_iter = target_low; source_iter != source_high; ++source_iter, ++target_iter)
		{
			*target_iter -= *source_iter;
		}
	}

	//Trivial cases: midpoint == high
	template<typename L_T_COEF, typename R_T_COEF, typename T_DEG>
	static void karatsuba_plan_internal(L_T_COEF* left_low, L_T_COEF* left_high, R_T_COEF* right_low, R_T_COEF* right_high, L_T_COEF** left_midpoint, R_T_COEF** right_midpoint)
	{
		static constexpr T_DEG length_threshold = 33;

		T_DEG left_msb = extract_msb_internal<T_DEG>(left_high - left_low),
			right_msb = extract_msb_internal<T_DEG>(right_high - right_low);

		if (left_msb < length_threshold || right_msb < length_threshold)
		{
			*left_midpoint = left_high;
			*right_midpoint = right_high;
			return;
		}

		if (left_msb < right_msb)
		{
			*left_midpoint = left_high;
			*right_midpoint = right_low + left_msb;
			return;
		}
		if (left_msb > right_msb)
		{
			*left_midpoint = left_low + right_msb;
			*right_midpoint = right_high;
			return;
		}
		//if (left_msb == right_msb)
		{
			*left_midpoint = left_low + left_msb;
			*right_midpoint = right_low + right_msb;
			return;
		}
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::mul_type, typename T_DEG, bool OUT_AUTO_TRIM>
	static uvp<OUT_T_COEF, T_DEG, OUT_AUTO_TRIM> karatsuba_internal(L_T_COEF* left_low, L_T_COEF* left_high, R_T_COEF* right_low, R_T_COEF* right_high)
	{
		L_T_COEF* left_midpoint;
		R_T_COEF* right_midpoint;
		karatsuba_plan_internal<L_T_COEF, R_T_COEF, T_DEG>(left_low, left_high, right_low, right_high, &left_midpoint, &right_midpoint);

		if (_EQ0_BY_PTR(left_midpoint, left_high) && _EQ0_BY_PTR(right_midpoint, right_high))
		{
			if constexpr (OUT_AUTO_TRIM)
			{
				left_midpoint = gda::rewind_trailing_zeroes_internal<L_T_COEF>(left_low, left_midpoint);
				right_midpoint = gda::rewind_trailing_zeroes_internal<R_T_COEF>(right_low, right_midpoint);

				if (_EQ0_BY_PTR(left_low, left_midpoint) || _EQ0_BY_PTR(right_low, right_midpoint))
				{
					return uvp<OUT_T_COEF, T_DEG, OUT_AUTO_TRIM>();
				}

				OUT_T_COEF* result_low = new OUT_T_COEF[(left_midpoint - left_low) + (right_midpoint - right_low) - 1],
					* result_high = result_low + (left_midpoint - left_low) + (right_midpoint - right_low) - 1;

				init_internal<OUT_T_COEF, static_cast<OUT_T_COEF>(0)>(result_low, result_high);
				schoolbook_mul_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG>(left_low, left_midpoint,
					right_low, right_midpoint,
					result_low);

				return uvp<OUT_T_COEF, T_DEG, OUT_AUTO_TRIM>(result_low, result_high);
			}
			else
			{
				OUT_T_COEF* result_low = new OUT_T_COEF[(left_midpoint - left_low) + (right_midpoint - right_low) - 1],
					* result_high = result_low + (left_midpoint - left_low) + (right_midpoint - right_low) - 1;

				init_internal<OUT_T_COEF, static_cast<OUT_T_COEF>(0)>(result_low, result_high);

				left_midpoint = gda::rewind_trailing_zeroes_internal<L_T_COEF>(left_low, left_midpoint);
				right_midpoint = gda::rewind_trailing_zeroes_internal<R_T_COEF>(right_low, right_midpoint);

				schoolbook_mul_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG>(left_low, left_midpoint,
					right_low, right_midpoint,
					result_low);

				return uvp<OUT_T_COEF, T_DEG, OUT_AUTO_TRIM>(result_low, result_high);
			}
		}

		if (_EQ0_BY_PTR(left_midpoint, left_high))
		{
			uvp<OUT_T_COEF, T_DEG, true> tmp_low = karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, true>(left_low, left_high, right_low, right_midpoint);
			uvp<OUT_T_COEF, T_DEG, true> tmp_high = karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, true>(left_low, left_high, right_midpoint, right_high);

			OUT_T_COEF* result_low = new OUT_T_COEF[tmp_high.deg() + (right_midpoint - right_low) + 1],
				* result_high = result_low + tmp_high.deg() + (right_midpoint - right_low) + 1;
			init_internal<OUT_T_COEF, static_cast<OUT_T_COEF>(0)>(result_low, result_high);
			accumulate_add_karatsuba_internal<OUT_T_COEF>(tmp_low.cc_iter_ctl(), tmp_low.lc_iter_ctl(), result_low);
			accumulate_add_karatsuba_internal<OUT_T_COEF>(tmp_high.cc_iter_ctl(), tmp_high.lc_iter_ctl(), result_low + (right_midpoint - right_low));

			return uvp<OUT_T_COEF, T_DEG, OUT_AUTO_TRIM>(result_low, result_high);
		}

		if (_EQ0_BY_PTR(right_midpoint, right_high))
		{
			uvp<OUT_T_COEF, T_DEG, true> tmp_low = karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, true>(left_low, left_midpoint, right_low, right_high);
			uvp<OUT_T_COEF, T_DEG, true> tmp_high = karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, true>(left_midpoint, left_high, right_low, right_high);

			OUT_T_COEF* result_low = new OUT_T_COEF[tmp_high.deg() + (left_midpoint - left_low) + 1],
				* result_high = result_low + tmp_high.deg() + (left_midpoint - left_low) + 1;
			init_internal<OUT_T_COEF, static_cast<OUT_T_COEF>(0)>(result_low, result_high);
			accumulate_add_karatsuba_internal<OUT_T_COEF>(tmp_low.cc_iter_ctl(), tmp_low.lc_iter_ctl(), result_low);
			accumulate_add_karatsuba_internal<OUT_T_COEF>(tmp_high.cc_iter_ctl(), tmp_high.lc_iter_ctl(), result_low + (left_midpoint - left_low));

			return uvp<OUT_T_COEF, T_DEG, OUT_AUTO_TRIM>(result_low, result_high);
		}

		//if (we can actually apply Karatsuba's trick)
		{
			uvp<L_T_COEF, T_DEG, true> left_hl = add_internal<L_T_COEF, L_T_COEF, L_T_COEF, T_DEG, true>(left_low, left_midpoint, left_midpoint, left_high);
			uvp<R_T_COEF, T_DEG, true> right_hl = add_internal<R_T_COEF, R_T_COEF, R_T_COEF, T_DEG, true>(right_low, right_midpoint, right_midpoint, right_high);

			uvp<OUT_T_COEF, T_DEG, true> lr_high = karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, true>(left_midpoint, left_high, right_midpoint, right_high),
				lr_hl = karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, true>(left_hl.cc_iter_ctl(), left_hl.lc_iter_ctl(), right_hl.cc_iter_ctl(), right_hl.lc_iter_ctl()),
				lr_low = karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, true>(left_low, left_midpoint, right_low, right_midpoint);

			T_DEG result_len = std::max((right_midpoint - right_low) + (left_midpoint - left_low), (right_high - right_midpoint) + (left_high - left_low)) + (left_midpoint - left_low) - 1;
			OUT_T_COEF* result_low = new OUT_T_COEF[result_len],
				* result_high = result_low + result_len;

			/*
			//don't ask
			std::cout << "result    : " << result_low << " - " << result_high << std::endl;
			std::cout << "op  1     : " << result_low << " - " << result_low + (lr_low.lc_iter_ctl() - lr_low.cc_iter_ctl()) << std::endl;
			std::cout << "result+os : " << result_low + (left_midpoint - left_low) << " - " << result_high << std::endl;
			std::cout << "op  2     : " << result_low + (left_midpoint - left_low) << " - " << result_low + (left_midpoint - left_low) + (lr_hl.lc_iter_ctl() - lr_hl.cc_iter_ctl()) << std::endl;
			std::cout << "op  3     : " << result_low + (left_midpoint - left_low) << " - " << result_low + (left_midpoint - left_low) + (lr_high.lc_iter_ctl() - lr_high.cc_iter_ctl()) << std::endl;
			std::cout << "op  4     : " << result_low + (left_midpoint - left_low) << " - " << result_low + (left_midpoint - left_low) + (lr_low.lc_iter_ctl() - lr_low.cc_iter_ctl()) << std::endl;
			std::cout << "result+2os: " << result_low + (left_midpoint - left_low) + (left_midpoint - left_low) << " - " << result_high << std::endl;
			std::cout << "op  5     : " << result_low + (left_midpoint - left_low) + (left_midpoint - left_low) << " - " << result_low + (left_midpoint - left_low) + (left_midpoint - left_low) + (lr_high.lc_iter_ctl() - lr_high.cc_iter_ctl()) << std::endl;
			*/

			init_internal<OUT_T_COEF, static_cast<OUT_T_COEF>(0)>(result_low, result_high);
			accumulate_add_karatsuba_internal<OUT_T_COEF>(lr_low.cc_iter_ctl(), lr_low.lc_iter_ctl(), result_low);

			accumulate_add_karatsuba_internal<OUT_T_COEF>(lr_hl.cc_iter_ctl(), lr_hl.lc_iter_ctl(), result_low + (left_midpoint - left_low));
			accumulate_sub_karatsuba_internal<OUT_T_COEF>(lr_high.cc_iter_ctl(), lr_high.lc_iter_ctl(), result_low + (left_midpoint - left_low));
			accumulate_sub_karatsuba_internal<OUT_T_COEF>(lr_low.cc_iter_ctl(), lr_low.lc_iter_ctl(), result_low + (left_midpoint - left_low));

			accumulate_add_karatsuba_internal<OUT_T_COEF>(lr_high.cc_iter_ctl(), lr_high.lc_iter_ctl(), result_low + (left_midpoint - left_low) + (left_midpoint - left_low));

			return uvp<OUT_T_COEF, T_DEG, OUT_AUTO_TRIM>(result_low, result_high);
		}
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::mul_type, typename T_DEG, bool L_AUTO_TRIM, bool R_AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM> karatsuba(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		return karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), right.cc_iter_ctl(), right.lc_iter_ctl());
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::mul_type, typename T_DEG, bool L_AUTO_TRIM, bool R_AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM> operator *(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		return karatsuba_internal<L_T_COEF, R_T_COEF, OUT_T_COEF, T_DEG, L_AUTO_TRIM || R_AUTO_TRIM>(left.cc_iter_ctl(), left.lc_iter_ctl(), right.cc_iter_ctl(), right.lc_iter_ctl());
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::mul_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> operator *(const uvp<L_T_COEF, T_DEG, AUTO_TRIM>& left, const R_T_COEF& right)
	{
		if constexpr (AUTO_TRIM)
		{
			if (right == static_cast<L_T_COEF>(0))
			{
				return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
			}
		}

		L_T_COEF* left_low = left.cc_iter_ctl(),
			* left_high = left.lc_iter_ctl(),
			* left_iter = left_low;

		if (left_low < left_high)
		{
			OUT_T_COEF* result_low = new OUT_T_COEF[left_high - left_low],
				* result_high = result_low + (left_high - left_low),
				* result_iter = result_low;

			for (; result_iter != result_high; ++left_iter, ++result_iter)
			{
				*result_iter = *left_iter * right;
			}

			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
		}
		else
		{
			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
		}
	}

	template<typename L_T_COEF, typename R_T_COEF, typename OUT_T_COEF = CL_2<L_T_COEF, R_T_COEF>::mul_type, typename T_DEG, bool AUTO_TRIM>
	uvp<OUT_T_COEF, T_DEG, AUTO_TRIM> operator *(const L_T_COEF& left, const uvp<R_T_COEF, T_DEG, AUTO_TRIM>& right)
	{
		if constexpr (AUTO_TRIM)
		{
			if (left == static_cast<L_T_COEF>(0))
			{
				return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
			}
		}

		R_T_COEF* right_low = right.cc_iter_ctl(),
			* right_high = right.lc_iter_ctl(),
			* right_iter = right_low;

		if (right_low < right_high)
		{
			OUT_T_COEF* result_low = new OUT_T_COEF[right_high - right_low],
				* result_high = result_low + (right_high - right_low),
				* result_iter = result_low;

			for (; result_iter != result_high; ++right_iter, ++result_iter)
			{
				*result_iter = left * *right_iter;
			}

			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>(result_low, result_high);
		}
		else
		{
			return uvp<OUT_T_COEF, T_DEG, AUTO_TRIM>();
		}
	}

#pragma endregion

#pragma region CMP
	
	//uvp<L> left == uvp<R> right \iff \forall i left[i] == right[i]; L == R is assumed to by symmetric; L != R doesn't matter

	/*
		left is presumed to be at most as long as right
	*/
	template<typename L_T_COEF, typename R_T_COEF>
	static bool eq_body(L_T_COEF* left_low, L_T_COEF* left_high, R_T_COEF* right_low, R_T_COEF* right_high)
	{
		L_T_COEF* left_iter = left_low;
		R_T_COEF* right_iter = right_low;
		for (; left_iter != left_high; ++left_iter, ++right_iter)
		{
			if (!(*left_iter == *right_iter))
			{
				return false;
			}
		}

		for (; right_iter != right_high; ++left_iter, ++right_iter)
		{
			if (!(static_cast<L_T_COEF>(0) == *right_iter))
			{
				return false;
			}
		}

		return true;
	}

	template<typename L_T_COEF, typename R_T_COEF, typename T_DEG, bool L_AUTO_TRIM, bool R_AUTO_TRIM>
	bool operator ==(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		L_T_COEF* l_low = left.cc_iter_ctl(),
			* l_high = left.lc_iter_ctl();
		R_T_COEF* r_low = right.cc_iter_ctl(),
			* r_high = right.lc_iter_ctl();

		if constexpr (L_AUTO_TRIM)
		{
			if constexpr (R_AUTO_TRIM)
			{
				if (l_high - l_low != r_high - r_low)
				{
					return false;
				}

				L_T_COEF* l_iter = l_low;
				R_T_COEF* r_iter = r_low;
				for (; l_iter != l_high; ++l_iter, ++r_iter)
				{
					if (!(*l_iter == *r_iter))
					{
						return false;
					}
				}

				return true;
			}
			else
			{
				if (l_high - l_low > r_high - r_low)
				{
					return false;
				}
				else
				{
					return eq_body<L_T_COEF, R_T_COEF>(l_low, l_high, r_low, r_high);
				}
			}
		}
		else
		{
			if constexpr (R_AUTO_TRIM)
			{
				if (l_high - l_low < r_high - r_low)
				{
					return false;
				}
				else
				{
					return eq_body<R_T_COEF, L_T_COEF>(r_low, r_high, l_low, l_high);
				}
			}
			else
			{
				if (l_high - l_low < r_high - r_low)
				{
					return eq_body<L_T_COEF, R_T_COEF>(l_low, l_high, r_low, r_high);
				}
				else
				{
					return eq_body<R_T_COEF, L_T_COEF>(r_low, r_high, l_low, l_high);
				}
			}
		}
	}

	template<typename L_T_COEF, typename R_T_COEF, typename T_DEG, bool L_AUTO_TRIM, bool R_AUTO_TRIM>
	bool operator !=(const uvp<L_T_COEF, T_DEG, L_AUTO_TRIM>& left, const uvp<R_T_COEF, T_DEG, R_AUTO_TRIM>& right)
	{
		return !(left == right);
	}

#pragma endregion

#pragma region OSTREAM

	template<typename T_COEF, typename T_DEG, bool AUTO_TRIM>
	std::ostream& operator <<(std::ostream& left, const uvp<T_COEF, T_DEG, AUTO_TRIM>& right)
	{
		return left << right.to_string_lth();
	}

#pragma endregion

}