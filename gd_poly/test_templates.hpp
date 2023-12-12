#include <iostream>
#include <string>

#include "univariate_polynomial.hpp"

#pragma region UNIT_TEST

template<typename T, T EXPECTED_VAL>
void report_unit(std::string test_id, T actual_val)
{
	if (actual_val == EXPECTED_VAL)
	{
		std::cout << test_id << " : OK" << std::endl;
	}
	else
	{
		std::cout << test_id << " : ERR; EXPECTED: " << EXPECTED_VAL << "; ACTUAL: " << actual_val << std::endl;
	}
}

template<typename T_COEF_1, typename T_COEF_2, typename T_DEG>
void gda_uvp_ctor_unit_test()
{
	gda::uvp<T_COEF_1, T_DEG> poly_1_1 = gda::uvp<T_COEF_1, T_DEG>();
	T_COEF_1* poly_1_1_cc_ptr = poly_1_1.cc_iter_ctl(),
		* poly_1_1_lc_ptr = poly_1_1.lc_iter_ctl();
	report_unit<bool, true>("empty_autotrim_ctor", poly_1_1_cc_ptr == poly_1_1_lc_ptr);

	gda::uvp<T_COEF_1, T_DEG, false> poly_2_1 = gda::uvp<T_COEF_1, T_DEG, false>();
	T_COEF_1* poly_2_1_cc_ptr = poly_2_1.cc_iter_ctl(),
		* poly_2_1_lc_ptr = poly_2_1.lc_iter_ctl();
	report_unit<bool, true>("empty_notrim_ctor", poly_2_1_cc_ptr == poly_2_1_lc_ptr);

	using war_crime_3_1 = T_COEF_1********;
	gda::uvp<war_crime_3_1, std::string, false> poly_3_1 = gda::uvp<war_crime_3_1, std::string, false>();
	war_crime_3_1* poly_3_1_cc_ptr = poly_3_1.cc_iter_ctl(),
		* poly_3_1_lc_ptr = poly_3_1.lc_iter_ctl();
	report_unit<bool, true>("empty_nonsense_ctor", poly_3_1_cc_ptr == poly_3_1_lc_ptr);

	constexpr T_COEF_1 val_4_1 = static_cast<T_COEF_1>(0);
	gda::uvp<T_COEF_1, T_DEG, true> poly_4_1 = gda::uvp<T_COEF_1, T_DEG, true>(val_4_1);
	T_COEF_1* poly_4_1_cc_ptr = poly_4_1.cc_iter_ctl(),
		* poly_4_1_lc_ptr = poly_4_1.lc_iter_ctl();
	report_unit<bool, true>("zero_const_autotrim_ex_ctor", poly_4_1_cc_ptr == poly_4_1_lc_ptr);

	constexpr T_COEF_1 val_5_1 = static_cast<T_COEF_1>(0);
	gda::uvp<T_COEF_1, T_DEG, true> poly_5_1 = val_5_1;
	T_COEF_1* poly_5_1_cc_ptr = poly_5_1.cc_iter_ctl(),
		* poly_5_1_lc_ptr = poly_5_1.lc_iter_ctl();
	report_unit<bool, true>("zero_const_autotrim_im_ctor", poly_5_1_cc_ptr == poly_5_1_lc_ptr);

	constexpr T_COEF_1 val_6_1 = static_cast<T_COEF_1>(1);
	gda::uvp<T_COEF_1, T_DEG, true> poly_6_1 = gda::uvp<T_COEF_1, T_DEG, true>(val_6_1);
	T_COEF_1* poly_6_1_cc_ptr = poly_6_1.cc_iter_ctl(),
		* poly_6_1_lc_ptr = poly_6_1.lc_iter_ctl();
	report_unit<bool, true>("nonzero_const_autotrim_ex_ctor:ptr", poly_6_1_cc_ptr + 1 == poly_6_1_lc_ptr);
	report_unit<T_COEF_1, val_6_1>("nonzero_const_autotrim_ex_ctor:val", *poly_6_1_cc_ptr);

	constexpr T_COEF_1 val_7_1 = static_cast<T_COEF_1>(1);
	gda::uvp<T_COEF_1, T_DEG, true> poly_7_1 = val_7_1;
	T_COEF_1* poly_7_1_cc_ptr = poly_7_1.cc_iter_ctl(),
		* poly_7_1_lc_ptr = poly_7_1.lc_iter_ctl();
	report_unit<bool, true>("nonzero_const_autotrim_im_ctor:ptr", poly_7_1_cc_ptr + 1 == poly_7_1_lc_ptr);
	report_unit<T_COEF_1, val_7_1>("nonzero_const_autotrim_im_ctor:val", *poly_7_1_cc_ptr);

	constexpr T_COEF_1 val_8_1 = static_cast<T_COEF_1>(0);
	gda::uvp<T_COEF_1, T_DEG, false> poly_8_1 = gda::uvp<T_COEF_1, T_DEG, false>(val_8_1);
	T_COEF_1* poly_8_1_cc_ptr = poly_8_1.cc_iter_ctl(),
		* poly_8_1_lc_ptr = poly_8_1.lc_iter_ctl();
	report_unit<bool, true>("zero_const_notrim_ex_ctor", poly_8_1_cc_ptr + 1 == poly_8_1_lc_ptr);
	report_unit<T_COEF_1, val_8_1>("zero_const_notrim_ex_ctor:val", *poly_8_1_cc_ptr);

	constexpr T_COEF_1 val_9_1 = static_cast<T_COEF_1>(0);
	gda::uvp<T_COEF_1, T_DEG, false> poly_9_1 = val_9_1;
	T_COEF_1* poly_9_1_cc_ptr = poly_9_1.cc_iter_ctl(),
		* poly_9_1_lc_ptr = poly_9_1.lc_iter_ctl();
	report_unit<bool, true>("zero_const_notrim_im_ctor", poly_9_1_cc_ptr + 1 == poly_9_1_lc_ptr);
	report_unit<T_COEF_1, val_9_1>("zero_const_notrim_im_ctor:val", *poly_9_1_cc_ptr);

	constexpr T_COEF_1 val_10_1 = static_cast<T_COEF_1>(1);
	gda::uvp<T_COEF_1, T_DEG, false> poly_10_1 = gda::uvp<T_COEF_1, T_DEG, false>(val_10_1);
	T_COEF_1* poly_10_1_cc_ptr = poly_10_1.cc_iter_ctl(),
		* poly_10_1_lc_ptr = poly_10_1.lc_iter_ctl();
	report_unit<bool, true>("nonzero_const_notrim_ex_ctor:ptr", poly_10_1_cc_ptr + 1 == poly_10_1_lc_ptr);
	report_unit<T_COEF_1, val_10_1>("nonzero_const_autotrim_ex_ctor:val", *poly_10_1_cc_ptr);

	constexpr T_COEF_1 val_11_1 = static_cast<T_COEF_1>(1);
	gda::uvp<T_COEF_1, T_DEG, false> poly_11_1 = val_11_1;
	T_COEF_1* poly_11_1_cc_ptr = poly_11_1.cc_iter_ctl(),
		* poly_11_1_lc_ptr = poly_11_1.lc_iter_ctl();
	report_unit<bool, true>("nonzero_const_notrim_im_ctor:ptr", poly_11_1_cc_ptr + 1 == poly_11_1_lc_ptr);
	report_unit<T_COEF_1, val_11_1>("nonzero_const_notrim_im_ctor:val", *poly_11_1_cc_ptr);

	constexpr T_COEF_1 val_12_1 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_12_1 = 7;
	T_COEF_1* arr_12_1_low = new T_COEF_1[len_12_1],
		* arr_12_1_high = arr_12_1_low + len_12_1;
	gda::init_internal<T_COEF_1, val_12_1>(arr_12_1_low, arr_12_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_12_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_12_1_low, arr_12_1_high);
	T_COEF_1* poly_12_1_cc_ptr = poly_12_1.cc_iter_ctl(),
		* poly_12_1_lc_ptr = poly_12_1.lc_iter_ctl();
	report_unit<bool, true>("zero_array_trim_ex_ctor", poly_12_1_cc_ptr == poly_12_1_lc_ptr);

	constexpr T_COEF_1 val_13_1 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_13_1 = 10;
	T_COEF_1* arr_13_1_low = new T_COEF_1[len_13_1],
		* arr_13_1_high = arr_13_1_low + len_13_1;
	gda::init_internal<T_COEF_1, val_13_1>(arr_13_1_low, arr_13_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_13_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_13_1_low, arr_13_1_high);
	T_COEF_1* poly_13_1_cc_ptr = poly_13_1.cc_iter_ctl(),
		* poly_13_1_lc_ptr = poly_13_1.lc_iter_ctl();
	report_unit<bool, true>("zero_array_notrim_ex_ctor:ptr", poly_13_1_cc_ptr + len_13_1 == poly_13_1_lc_ptr);
	report_unit<T_COEF_1, val_13_1>("zero_array_notrim_ex_ctor:val0", *poly_13_1_cc_ptr++);
	report_unit<T_COEF_1, val_13_1>("zero_array_notrim_ex_ctor:val1", *poly_13_1_cc_ptr++);
	report_unit<T_COEF_1, val_13_1>("zero_array_notrim_ex_ctor:val2", *poly_13_1_cc_ptr);
	poly_13_1_cc_ptr += len_13_1 - 3;
	report_unit<T_COEF_1, val_13_1>("zero_array_notrim_ex_ctor:vallast", *poly_13_1_cc_ptr);

	constexpr T_COEF_1 val_14_1 = static_cast<T_COEF_1>(1);
	constexpr T_DEG len_14_1 = 7;
	T_COEF_1* arr_14_1_low = new T_COEF_1[len_14_1],
		* arr_14_1_high = arr_14_1_low + len_14_1;
	gda::init_internal<T_COEF_1, val_14_1>(arr_14_1_low, arr_14_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_14_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_14_1_low, arr_14_1_high);
	T_COEF_1* poly_14_1_cc_ptr = poly_14_1.cc_iter_ctl(),
		* poly_14_1_lc_ptr = poly_14_1.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_trim_ex_ctor", poly_14_1_cc_ptr + len_14_1 == poly_14_1_lc_ptr);
	report_unit<T_COEF_1, val_14_1>("nonzero_array_trim_ex_ctor:val0", *poly_14_1_cc_ptr++);
	report_unit<T_COEF_1, val_14_1>("nonzero_array_trim_ex_ctor:val1", *poly_14_1_cc_ptr++);
	report_unit<T_COEF_1, val_14_1>("nonzero_array_trim_ex_ctor:val2", *poly_14_1_cc_ptr);
	poly_14_1_cc_ptr += len_14_1 - 3;
	report_unit<T_COEF_1, val_14_1>("nonzero_array_trim_ex_ctor:vallast", *poly_14_1_cc_ptr);


	constexpr T_COEF_1 val_15_1 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_15_1 = 7;
	T_COEF_1* arr_15_1_low = new T_COEF_1[len_15_1],
		* arr_15_1_high = arr_15_1_low + len_15_1;
	gda::init_internal<T_COEF_1, val_15_1>(arr_15_1_low, arr_15_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_15_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_15_1_low, arr_15_1_high);
	T_COEF_1* poly_15_1_cc_ptr = poly_15_1.cc_iter_ctl(),
		* poly_15_1_lc_ptr = poly_15_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_15_2 = gda::uvp<T_COEF_1, T_DEG, true>(poly_15_1);
	T_COEF_1* poly_15_2_cc_ptr = poly_15_2.cc_iter_ctl(),
		* poly_15_2_lc_ptr = poly_15_2.lc_iter_ctl();
	report_unit<bool, true>("zero_array_notrim_to_trim_copy_ctor:notrim_ptr", poly_15_1_cc_ptr + len_15_1 == poly_15_1_lc_ptr);
	report_unit<bool, true>("zero_array_notrim_to_trim_copy_ctor:trim_ptr", poly_15_2_cc_ptr == poly_15_2_lc_ptr);

	constexpr T_COEF_1 val_16_1 = static_cast<T_COEF_1>(1),
		val_16_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_16_1 = 28;
	T_COEF_1* arr_16_1_low = new T_COEF_1[len_16_1],
		* arr_16_1_high = arr_16_1_low + len_16_1;
	gda::init_internal<T_COEF_1, val_16_1>(arr_16_1_low, arr_16_1_high - 7);
	gda::init_internal<T_COEF_1, val_16_2>(arr_16_1_high - 7, arr_16_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_16_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_16_1_low, arr_16_1_high);
	T_COEF_1* poly_16_1_cc_ptr = poly_16_1.cc_iter_ctl(),
		* poly_16_1_lc_ptr = poly_16_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_16_2 = gda::uvp<T_COEF_1, T_DEG, true>(poly_16_1);
	T_COEF_1* poly_16_2_cc_ptr = poly_16_2.cc_iter_ctl(),
		* poly_16_2_lc_ptr = poly_16_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_notrim_to_trim_copy_ctor:notrim_ptr", poly_16_1_cc_ptr + len_16_1 == poly_16_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_notrim_to_trim_copy_ctor:trim_ptr", poly_16_2_cc_ptr + len_16_1 - 7 == poly_16_2_lc_ptr);

	constexpr T_COEF_1 val_17_1 = static_cast<T_COEF_1>(1),
		val_17_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_17_1 = 28;
	T_COEF_1* arr_17_1_low = new T_COEF_1[len_17_1],
		* arr_17_1_high = arr_17_1_low + len_17_1;
	gda::init_internal<T_COEF_1, val_17_1>(arr_17_1_low, arr_17_1_high - 7);
	gda::init_internal<T_COEF_1, val_17_2>(arr_17_1_high - 7, arr_17_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_17_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_17_1_low, arr_17_1_high);
	T_COEF_1* poly_17_1_cc_ptr = poly_17_1.cc_iter_ctl(),
		* poly_17_1_lc_ptr = poly_17_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, false> poly_17_2 = gda::uvp<T_COEF_1, T_DEG, false>(poly_17_1);
	T_COEF_1* poly_17_2_cc_ptr = poly_17_2.cc_iter_ctl(),
		* poly_17_2_lc_ptr = poly_17_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_trim_to_notrim_copy_ctor:notrim_ptr", poly_17_1_cc_ptr + len_17_1 - 7 == poly_17_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_trim_to_notrim_copy_ctor:trim_ptr", poly_17_2_cc_ptr + len_17_1 - 7 == poly_17_2_lc_ptr);

	constexpr T_COEF_1 val_18_1 = static_cast<T_COEF_1>(1),
		val_18_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_18_3 = static_cast<T_COEF_2>(val_18_1),
		val_18_4 = static_cast<T_COEF_2>(val_18_2);
	constexpr T_DEG len_18_1 = 28;
	T_COEF_1* arr_18_1_low = new T_COEF_1[len_18_1],
		* arr_18_1_high = arr_18_1_low + len_18_1;
	gda::init_internal<T_COEF_1, val_18_1>(arr_18_1_low, arr_18_1_high - 7);
	gda::init_internal<T_COEF_1, val_18_2>(arr_18_1_high - 7, arr_18_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_18_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_18_1_low, arr_18_1_high);
	T_COEF_1* poly_18_1_cc_ptr = poly_18_1.cc_iter_ctl(),
		* poly_18_1_lc_ptr = poly_18_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_18_2 = gda::uvp<T_COEF_2, T_DEG, true>(poly_18_1);
	T_COEF_2* poly_18_2_cc_ptr = poly_18_2.cc_iter_ctl(),
		* poly_18_2_lc_ptr = poly_18_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_trim_copy_ctor:t1_ptr", poly_18_1_cc_ptr + len_18_1 - 7 == poly_18_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_trim_copy_ctor:t2_ptr", poly_18_2_cc_ptr + len_18_1 - 7 == poly_18_2_lc_ptr);
	report_unit<T_COEF_1, val_18_1>("array_trim_to_trim_copy_ctor:t1_val0", *poly_18_1_cc_ptr);
	report_unit<T_COEF_2, val_18_3>("array_trim_to_trim_copy_ctor:t2_val0", *poly_18_2_cc_ptr);

	constexpr T_COEF_1 val_19_1 = static_cast<T_COEF_1>(1),
		val_19_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_19_3 = static_cast<T_COEF_2>(val_19_1),
		val_19_4 = static_cast<T_COEF_2>(val_19_2);
	constexpr T_DEG len_19_1 = 28;
	T_COEF_1* arr_19_1_low = new T_COEF_1[len_19_1],
		* arr_19_1_high = arr_19_1_low + len_19_1;
	gda::init_internal<T_COEF_1, val_19_1>(arr_19_1_low, arr_19_1_high - 7);
	gda::init_internal<T_COEF_1, val_19_2>(arr_19_1_high - 7, arr_19_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_19_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_19_1_low, arr_19_1_high);
	T_COEF_1* poly_19_1_cc_ptr = poly_19_1.cc_iter_ctl(),
		* poly_19_1_lc_ptr = poly_19_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_19_2 = gda::uvp<T_COEF_2, T_DEG, false>(poly_19_1);
	T_COEF_2* poly_19_2_cc_ptr = poly_19_2.cc_iter_ctl(),
		* poly_19_2_lc_ptr = poly_19_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_copy_ctor:t1_ptr", poly_19_1_cc_ptr + len_19_1 - 7 == poly_19_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_copy_ctor:t2_ptr", poly_19_2_cc_ptr + len_19_1 - 7 == poly_19_2_lc_ptr);
	report_unit<T_COEF_1, val_19_1>("array_trim_to_notrim_copy_ctor:t1_val0", *poly_19_1_cc_ptr);
	report_unit<T_COEF_2, val_19_3>("array_trim_to_notrim_copy_ctor:t2_val0", *poly_19_2_cc_ptr);

	constexpr T_COEF_1 val_20_1 = static_cast<T_COEF_1>(1),
		val_20_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_20_3 = static_cast<T_COEF_2>(val_20_1),
		val_20_4 = static_cast<T_COEF_2>(val_20_2);
	constexpr T_DEG len_20_1 = 28;
	T_COEF_1* arr_20_1_low = new T_COEF_1[len_20_1],
		* arr_20_1_high = arr_20_1_low + len_20_1;
	gda::init_internal<T_COEF_1, val_20_1>(arr_20_1_low, arr_20_1_high - 7);
	gda::init_internal<T_COEF_1, val_20_2>(arr_20_1_high - 7, arr_20_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_20_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_20_1_low, arr_20_1_high);
	T_COEF_1* poly_20_1_cc_ptr = poly_20_1.cc_iter_ctl(),
		* poly_20_1_lc_ptr = poly_20_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_20_2 = gda::uvp<T_COEF_2, T_DEG, true>(poly_20_1);
	T_COEF_2* poly_20_2_cc_ptr = poly_20_2.cc_iter_ctl(),
		* poly_20_2_lc_ptr = poly_20_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_copy_ctor:t1_ptr", poly_20_1_cc_ptr + len_20_1 == poly_20_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_copy_ctor:t2_ptr", poly_20_2_cc_ptr + len_20_1 - 7 == poly_20_2_lc_ptr);
	report_unit<T_COEF_1, val_20_1>("array_notrim_to_trim_copy_ctor:t1_val0", *poly_20_1_cc_ptr);
	report_unit<T_COEF_2, val_20_3>("array_notrim_to_trim_copy_ctor:t2_val0", *poly_20_2_cc_ptr);
	report_unit<T_COEF_1, val_20_2>("array_notrim_to_trim_copy_ctor:t1_vallast", *(poly_20_1_lc_ptr - 1));


	constexpr T_COEF_1 val_21_1 = static_cast<T_COEF_1>(1),
		val_21_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_21_3 = static_cast<T_COEF_2>(val_21_1),
		val_21_4 = static_cast<T_COEF_2>(val_21_2);
	constexpr T_DEG len_21_1 = 28;
	T_COEF_1* arr_21_1_low = new T_COEF_1[len_21_1],
		* arr_21_1_high = arr_21_1_low + len_21_1;
	gda::init_internal<T_COEF_1, val_21_1>(arr_21_1_low, arr_21_1_high - 7);
	gda::init_internal<T_COEF_1, val_21_2>(arr_21_1_high - 7, arr_21_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_21_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_21_1_low, arr_21_1_high);
	T_COEF_1* poly_21_1_cc_ptr = poly_21_1.cc_iter_ctl(),
		* poly_21_1_lc_ptr = poly_21_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_21_2 = gda::uvp<T_COEF_2, T_DEG, false>(poly_21_1);
	T_COEF_2* poly_21_2_cc_ptr = poly_21_2.cc_iter_ctl(),
		* poly_21_2_lc_ptr = poly_21_2.lc_iter_ctl();
	report_unit<bool, true>("array_notrim_to_notrim_copy_ctor:t1_ptr", poly_21_1_cc_ptr + len_21_1 == poly_21_1_lc_ptr);
	report_unit<bool, true>("array_notrim_to_notrim_copy_ctor:t2_ptr", poly_21_2_cc_ptr + len_21_1 == poly_21_2_lc_ptr);
	report_unit<T_COEF_1, val_21_1>("array_notrim_to_notrim_copy_ctor:t1_val0", *poly_21_1_cc_ptr);
	report_unit<T_COEF_2, val_21_3>("array_notrim_to_notrim_copy_ctor:t2_val0", *poly_21_2_cc_ptr);
	report_unit<T_COEF_1, val_21_2>("array_notrim_to_notrim_copy_ctor:t1_vallast", *(poly_21_1_lc_ptr - 1));
	report_unit<T_COEF_2, val_21_4>("array_notrim_to_notrim_copy_ctor:t2_vallast", *(poly_21_2_lc_ptr - 1));



	constexpr T_COEF_1 val_22_1 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_22_1 = 7;
	T_COEF_1* arr_22_1_low = new T_COEF_1[len_22_1],
		* arr_22_1_high = arr_22_1_low + len_22_1;
	gda::init_internal<T_COEF_1, val_22_1>(arr_22_1_low, arr_22_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_22_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_22_1_low, arr_22_1_high);
	T_COEF_1* poly_22_1_cc_ptr = poly_22_1.cc_iter_ctl(),
		* poly_22_1_lc_ptr = poly_22_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_22_2 = gda::uvp<T_COEF_1, T_DEG, true>(std::move(poly_22_1));
	T_COEF_1* poly_22_2_cc_ptr = poly_22_2.cc_iter_ctl(),
		* poly_22_2_lc_ptr = poly_22_2.lc_iter_ctl();
	report_unit<bool, true>("zero_array_notrim_to_trim_move_ctor:notrim_ptr", poly_22_1_cc_ptr + len_22_1 == poly_22_1_lc_ptr);
	report_unit<bool, true>("zero_array_notrim_to_trim_move_ctor:trim_ptr", poly_22_2_cc_ptr == poly_22_2_lc_ptr);

	constexpr T_COEF_1 val_23_1 = static_cast<T_COEF_1>(1),
		val_23_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_23_1 = 28;
	T_COEF_1* arr_23_1_low = new T_COEF_1[len_23_1],
		* arr_23_1_high = arr_23_1_low + len_23_1;
	gda::init_internal<T_COEF_1, val_23_1>(arr_23_1_low, arr_23_1_high - 7);
	gda::init_internal<T_COEF_1, val_23_2>(arr_23_1_high - 7, arr_23_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_23_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_23_1_low, arr_23_1_high);
	T_COEF_1* poly_23_1_cc_ptr = poly_23_1.cc_iter_ctl(),
		* poly_23_1_lc_ptr = poly_23_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_23_2 = gda::uvp<T_COEF_1, T_DEG, true>(std::move(poly_23_1));
	T_COEF_1* poly_23_2_cc_ptr = poly_23_2.cc_iter_ctl(),
		* poly_23_2_lc_ptr = poly_23_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_notrim_to_trim_move_ctor:notrim_ptr", poly_23_1_cc_ptr + len_23_1 == poly_23_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_notrim_to_trim_move_ctor:trim_ptr", poly_23_2_cc_ptr + len_23_1 - 7 == poly_23_2_lc_ptr);
	report_unit<bool, true>("nonzero_array_notrim_to_trim_move_ctor:low_ptr", poly_23_1_cc_ptr == poly_23_2_cc_ptr);

	constexpr T_COEF_1 val_24_1 = static_cast<T_COEF_1>(1),
		val_24_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_24_1 = 28;
	T_COEF_1* arr_24_1_low = new T_COEF_1[len_24_1],
		* arr_24_1_high = arr_24_1_low + len_24_1;
	gda::init_internal<T_COEF_1, val_24_1>(arr_24_1_low, arr_24_1_high - 7);
	gda::init_internal<T_COEF_1, val_24_2>(arr_24_1_high - 7, arr_24_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_24_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_24_1_low, arr_24_1_high);
	T_COEF_1* poly_24_1_cc_ptr = poly_24_1.cc_iter_ctl(),
		* poly_24_1_lc_ptr = poly_24_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, false> poly_24_2 = gda::uvp<T_COEF_1, T_DEG, false>(std::move(poly_24_1));
	T_COEF_1* poly_24_2_cc_ptr = poly_24_2.cc_iter_ctl(),
		* poly_24_2_lc_ptr = poly_24_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_trim_to_notrim_move_ctor:notrim_ptr", poly_24_1_cc_ptr + len_24_1 - 7 == poly_24_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_trim_to_notrim_move_ctor:trim_ptr", poly_24_2_cc_ptr + len_24_1 - 7 == poly_24_2_lc_ptr);
	report_unit<bool, true>("nonzero_array_trim_to_notrim_move_ctor:low_ptr", poly_24_1_cc_ptr == poly_24_2_cc_ptr);

	/*
	constexpr T_COEF_1 val_25_1 = static_cast<T_COEF_1>(1),
		val_25_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_25_3 = static_cast<T_COEF_2>(val_25_1),
		val_25_4 = static_cast<T_COEF_2>(val_25_2);
	constexpr T_DEG len_25_1 = 28;
	T_COEF_1* arr_25_1_low = new T_COEF_1[len_25_1],
		* arr_25_1_high = arr_25_1_low + len_25_1;
	gda::init_internal<T_COEF_1, val_25_1>(arr_25_1_low, arr_25_1_high - 7);
	gda::init_internal<T_COEF_1, val_25_2>(arr_25_1_high - 7, arr_25_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_25_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_25_1_low, arr_25_1_high);
	T_COEF_1* poly_25_1_cc_ptr = poly_25_1.cc_iter_ctl(),
		* poly_25_1_lc_ptr = poly_25_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_25_2 = gda::uvp<T_COEF_2, T_DEG, true>(std::move(poly_25_1));
	T_COEF_2* poly_25_2_cc_ptr = poly_25_2.cc_iter_ctl(),
		* poly_25_2_lc_ptr = poly_25_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_trim_move_ctor:t1_ptr", poly_25_1_cc_ptr + len_25_1 - 7 == poly_25_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_trim_move_ctor:t2_ptr", poly_25_2_cc_ptr + len_25_1 - 7 == poly_25_2_lc_ptr);
	report_unit<T_COEF_1, val_25_1>("array_trim_to_trim_move_ctor:t1_val0", *poly_25_1_cc_ptr);
	report_unit<T_COEF_2, val_25_3>("array_trim_to_trim_move_ctor:t2_val0", *poly_25_2_cc_ptr);

	constexpr T_COEF_1 val_26_1 = static_cast<T_COEF_1>(1),
		val_26_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_26_3 = static_cast<T_COEF_2>(val_26_1),
		val_26_4 = static_cast<T_COEF_2>(val_26_2);
	constexpr T_DEG len_26_1 = 28;
	T_COEF_1* arr_26_1_low = new T_COEF_1[len_26_1],
		* arr_26_1_high = arr_26_1_low + len_26_1;
	gda::init_internal<T_COEF_1, val_26_1>(arr_26_1_low, arr_26_1_high - 7);
	gda::init_internal<T_COEF_1, val_26_2>(arr_26_1_high - 7, arr_26_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_26_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_26_1_low, arr_26_1_high);
	T_COEF_1* poly_26_1_cc_ptr = poly_26_1.cc_iter_ctl(),
		* poly_26_1_lc_ptr = poly_26_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_26_2 = gda::uvp<T_COEF_2, T_DEG, false>(std::move(poly_26_1));
	T_COEF_2* poly_26_2_cc_ptr = poly_26_2.cc_iter_ctl(),
		* poly_26_2_lc_ptr = poly_26_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_move_ctor:t1_ptr", poly_26_1_cc_ptr + len_26_1 - 7 == poly_26_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_move_ctor:t2_ptr", poly_26_2_cc_ptr + len_26_1 - 7 == poly_26_2_lc_ptr);
	report_unit<T_COEF_1, val_26_1>("array_trim_to_notrim_move_ctor:t1_val0", *poly_26_1_cc_ptr);
	report_unit<T_COEF_2, val_26_3>("array_trim_to_notrim_move_ctor:t2_val0", *poly_26_2_cc_ptr);

	constexpr T_COEF_1 val_27_1 = static_cast<T_COEF_1>(1),
		val_27_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_27_3 = static_cast<T_COEF_2>(val_27_1),
		val_27_4 = static_cast<T_COEF_2>(val_27_2);
	constexpr T_DEG len_27_1 = 28;
	T_COEF_1* arr_27_1_low = new T_COEF_1[len_27_1],
		* arr_27_1_high = arr_27_1_low + len_27_1;
	gda::init_internal<T_COEF_1, val_27_1>(arr_27_1_low, arr_27_1_high - 7);
	gda::init_internal<T_COEF_1, val_27_2>(arr_27_1_high - 7, arr_27_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_27_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_27_1_low, arr_27_1_high);
	T_COEF_1* poly_27_1_cc_ptr = poly_27_1.cc_iter_ctl(),
		* poly_27_1_lc_ptr = poly_27_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_27_2 = gda::uvp<T_COEF_2, T_DEG, true>(std::move(poly_27_1));
	T_COEF_2* poly_27_2_cc_ptr = poly_27_2.cc_iter_ctl(),
		* poly_27_2_lc_ptr = poly_27_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_move_ctor:t1_ptr", poly_27_1_cc_ptr + len_27_1 == poly_27_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_move_ctor:t2_ptr", poly_27_2_cc_ptr + len_27_1 - 7 == poly_27_2_lc_ptr);
	report_unit<T_COEF_1, val_27_1>("array_notrim_to_trim_move_ctor:t1_val0", *poly_27_1_cc_ptr);
	report_unit<T_COEF_2, val_27_3>("array_notrim_to_trim_move_ctor:t2_val0", *poly_27_2_cc_ptr);
	report_unit<T_COEF_1, val_27_2>("array_notrim_to_trim_move_ctor:t1_vallast", *(poly_27_1_lc_ptr - 1));


	constexpr T_COEF_1 val_28_1 = static_cast<T_COEF_1>(1),
		val_28_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_28_3 = static_cast<T_COEF_2>(val_28_1),
		val_28_4 = static_cast<T_COEF_2>(val_28_2);
	constexpr T_DEG len_28_1 = 28;
	T_COEF_1* arr_28_1_low = new T_COEF_1[len_28_1],
		* arr_28_1_high = arr_28_1_low + len_28_1;
	gda::init_internal<T_COEF_1, val_28_1>(arr_28_1_low, arr_28_1_high - 7);
	gda::init_internal<T_COEF_1, val_28_2>(arr_28_1_high - 7, arr_28_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_28_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_28_1_low, arr_28_1_high);
	T_COEF_1* poly_28_1_cc_ptr = poly_28_1.cc_iter_ctl(),
		* poly_28_1_lc_ptr = poly_28_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_28_2 = gda::uvp<T_COEF_2, T_DEG, false>(std::move(poly_28_1));
	T_COEF_2* poly_28_2_cc_ptr = poly_28_2.cc_iter_ctl(),
		* poly_28_2_lc_ptr = poly_28_2.lc_iter_ctl();
	report_unit<bool, true>("array_notrim_to_notrim_move_ctor:t1_ptr", poly_28_1_cc_ptr + len_28_1 == poly_28_1_lc_ptr);
	report_unit<bool, true>("array_notrim_to_notrim_move_ctor:t2_ptr", poly_28_2_cc_ptr + len_28_1 == poly_28_2_lc_ptr);
	report_unit<T_COEF_1, val_28_1>("array_notrim_to_notrim_move_ctor:t1_val0", *poly_28_1_cc_ptr);
	report_unit<T_COEF_2, val_28_3>("array_notrim_to_notrim_move_ctor:t2_val0", *poly_28_2_cc_ptr);
	report_unit<T_COEF_1, val_28_2>("array_notrim_to_notrim_move_ctor:t1_vallast", *(poly_28_1_lc_ptr - 1));
	report_unit<T_COEF_2, val_28_4>("array_notrim_to_notrim_move_ctor:t2_vallast", *(poly_28_2_lc_ptr - 1));

	*/
}

template<typename T_COEF_1, typename T_COEF_2, typename T_DEG>
void gda_uvp_assignment_unit_test()
{
	constexpr T_COEF_1 val_15_1 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_15_1 = 7;
	T_COEF_1* arr_15_1_low = new T_COEF_1[len_15_1],
		* arr_15_1_high = arr_15_1_low + len_15_1;
	gda::init_internal<T_COEF_1, val_15_1>(arr_15_1_low, arr_15_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_15_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_15_1_low, arr_15_1_high);
	T_COEF_1* poly_15_1_cc_ptr = poly_15_1.cc_iter_ctl(),
		* poly_15_1_lc_ptr = poly_15_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_15_2;
	poly_15_2 = poly_15_1;
	T_COEF_1* poly_15_2_cc_ptr = poly_15_2.cc_iter_ctl(),
		* poly_15_2_lc_ptr = poly_15_2.lc_iter_ctl();
	report_unit<bool, true>("zero_array_notrim_to_trim_copy_assgn:notrim_ptr", poly_15_1_cc_ptr + len_15_1 == poly_15_1_lc_ptr);
	report_unit<bool, true>("zero_array_notrim_to_trim_copy_assgn:trim_ptr", poly_15_2_cc_ptr == poly_15_2_lc_ptr);

	constexpr T_COEF_1 val_16_1 = static_cast<T_COEF_1>(1),
		val_16_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_16_1 = 28;
	T_COEF_1* arr_16_1_low = new T_COEF_1[len_16_1],
		* arr_16_1_high = arr_16_1_low + len_16_1;
	gda::init_internal<T_COEF_1, val_16_1>(arr_16_1_low, arr_16_1_high - 7);
	gda::init_internal<T_COEF_1, val_16_2>(arr_16_1_high - 7, arr_16_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_16_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_16_1_low, arr_16_1_high);
	T_COEF_1* poly_16_1_cc_ptr = poly_16_1.cc_iter_ctl(),
		* poly_16_1_lc_ptr = poly_16_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_16_2;
	poly_16_2 = poly_16_1;
	T_COEF_1* poly_16_2_cc_ptr = poly_16_2.cc_iter_ctl(),
		* poly_16_2_lc_ptr = poly_16_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_notrim_to_trim_copy_assgn:notrim_ptr", poly_16_1_cc_ptr + len_16_1 == poly_16_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_notrim_to_trim_copy_assgn:trim_ptr", poly_16_2_cc_ptr + len_16_1 - 7 == poly_16_2_lc_ptr);

	constexpr T_COEF_1 val_17_1 = static_cast<T_COEF_1>(1),
		val_17_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_17_1 = 28;
	T_COEF_1* arr_17_1_low = new T_COEF_1[len_17_1],
		* arr_17_1_high = arr_17_1_low + len_17_1;
	gda::init_internal<T_COEF_1, val_17_1>(arr_17_1_low, arr_17_1_high - 7);
	gda::init_internal<T_COEF_1, val_17_2>(arr_17_1_high - 7, arr_17_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_17_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_17_1_low, arr_17_1_high);
	T_COEF_1* poly_17_1_cc_ptr = poly_17_1.cc_iter_ctl(),
		* poly_17_1_lc_ptr = poly_17_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, false> poly_17_2;
	poly_17_2 = poly_17_1;
	T_COEF_1* poly_17_2_cc_ptr = poly_17_2.cc_iter_ctl(),
		* poly_17_2_lc_ptr = poly_17_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_trim_to_notrim_copy_assgn:notrim_ptr", poly_17_1_cc_ptr + len_17_1 - 7 == poly_17_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_trim_to_notrim_copy_assgn:trim_ptr", poly_17_2_cc_ptr + len_17_1 - 7 == poly_17_2_lc_ptr);

	constexpr T_COEF_1 val_18_1 = static_cast<T_COEF_1>(1),
		val_18_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_18_3 = static_cast<T_COEF_2>(val_18_1),
		val_18_4 = static_cast<T_COEF_2>(val_18_2);
	constexpr T_DEG len_18_1 = 28;
	T_COEF_1* arr_18_1_low = new T_COEF_1[len_18_1],
		* arr_18_1_high = arr_18_1_low + len_18_1;
	gda::init_internal<T_COEF_1, val_18_1>(arr_18_1_low, arr_18_1_high - 7);
	gda::init_internal<T_COEF_1, val_18_2>(arr_18_1_high - 7, arr_18_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_18_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_18_1_low, arr_18_1_high);
	T_COEF_1* poly_18_1_cc_ptr = poly_18_1.cc_iter_ctl(),
		* poly_18_1_lc_ptr = poly_18_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_18_2;
	poly_18_2 = poly_18_1;
	T_COEF_2* poly_18_2_cc_ptr = poly_18_2.cc_iter_ctl(),
		* poly_18_2_lc_ptr = poly_18_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_trim_copy_assgn:t1_ptr", poly_18_1_cc_ptr + len_18_1 - 7 == poly_18_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_trim_copy_assgn:t2_ptr", poly_18_2_cc_ptr + len_18_1 - 7 == poly_18_2_lc_ptr);
	report_unit<T_COEF_1, val_18_1>("array_trim_to_trim_copy_assgn:t1_val0", *poly_18_1_cc_ptr);
	report_unit<T_COEF_2, val_18_3>("array_trim_to_trim_copy_assgn:t2_val0", *poly_18_2_cc_ptr);

	constexpr T_COEF_1 val_19_1 = static_cast<T_COEF_1>(1),
		val_19_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_19_3 = static_cast<T_COEF_2>(val_19_1),
		val_19_4 = static_cast<T_COEF_2>(val_19_2);
	constexpr T_DEG len_19_1 = 28;
	T_COEF_1* arr_19_1_low = new T_COEF_1[len_19_1],
		* arr_19_1_high = arr_19_1_low + len_19_1;
	gda::init_internal<T_COEF_1, val_19_1>(arr_19_1_low, arr_19_1_high - 7);
	gda::init_internal<T_COEF_1, val_19_2>(arr_19_1_high - 7, arr_19_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_19_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_19_1_low, arr_19_1_high);
	T_COEF_1* poly_19_1_cc_ptr = poly_19_1.cc_iter_ctl(),
		* poly_19_1_lc_ptr = poly_19_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_19_2;
	poly_19_2 = poly_19_1;
	T_COEF_2* poly_19_2_cc_ptr = poly_19_2.cc_iter_ctl(),
		* poly_19_2_lc_ptr = poly_19_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_copy_assgn:t1_ptr", poly_19_1_cc_ptr + len_19_1 - 7 == poly_19_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_copy_assgn:t2_ptr", poly_19_2_cc_ptr + len_19_1 - 7 == poly_19_2_lc_ptr);
	report_unit<T_COEF_1, val_19_1>("array_trim_to_notrim_copy_assgn:t1_val0", *poly_19_1_cc_ptr);
	report_unit<T_COEF_2, val_19_3>("array_trim_to_notrim_copy_assgn:t2_val0", *poly_19_2_cc_ptr);

	constexpr T_COEF_1 val_20_1 = static_cast<T_COEF_1>(1),
		val_20_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_20_3 = static_cast<T_COEF_2>(val_20_1),
		val_20_4 = static_cast<T_COEF_2>(val_20_2);
	constexpr T_DEG len_20_1 = 28;
	T_COEF_1* arr_20_1_low = new T_COEF_1[len_20_1],
		* arr_20_1_high = arr_20_1_low + len_20_1;
	gda::init_internal<T_COEF_1, val_20_1>(arr_20_1_low, arr_20_1_high - 7);
	gda::init_internal<T_COEF_1, val_20_2>(arr_20_1_high - 7, arr_20_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_20_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_20_1_low, arr_20_1_high);
	T_COEF_1* poly_20_1_cc_ptr = poly_20_1.cc_iter_ctl(),
		* poly_20_1_lc_ptr = poly_20_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_20_2;
	poly_20_2 = poly_20_1;
	T_COEF_2* poly_20_2_cc_ptr = poly_20_2.cc_iter_ctl(),
		* poly_20_2_lc_ptr = poly_20_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_copy_assgn:t1_ptr", poly_20_1_cc_ptr + len_20_1 == poly_20_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_copy_assgn:t2_ptr", poly_20_2_cc_ptr + len_20_1 - 7 == poly_20_2_lc_ptr);
	report_unit<T_COEF_1, val_20_1>("array_notrim_to_trim_copy_assgn:t1_val0", *poly_20_1_cc_ptr);
	report_unit<T_COEF_2, val_20_3>("array_notrim_to_trim_copy_assgn:t2_val0", *poly_20_2_cc_ptr);
	report_unit<T_COEF_1, val_20_2>("array_notrim_to_trim_copy_assgn:t1_vallast", *(poly_20_1_lc_ptr - 1));


	constexpr T_COEF_1 val_21_1 = static_cast<T_COEF_1>(1),
		val_21_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_21_3 = static_cast<T_COEF_2>(val_21_1),
		val_21_4 = static_cast<T_COEF_2>(val_21_2);
	constexpr T_DEG len_21_1 = 28;
	T_COEF_1* arr_21_1_low = new T_COEF_1[len_21_1],
		* arr_21_1_high = arr_21_1_low + len_21_1;
	gda::init_internal<T_COEF_1, val_21_1>(arr_21_1_low, arr_21_1_high - 7);
	gda::init_internal<T_COEF_1, val_21_2>(arr_21_1_high - 7, arr_21_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_21_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_21_1_low, arr_21_1_high);
	T_COEF_1* poly_21_1_cc_ptr = poly_21_1.cc_iter_ctl(),
		* poly_21_1_lc_ptr = poly_21_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_21_2;
	poly_21_2 = poly_21_1;
	T_COEF_2* poly_21_2_cc_ptr = poly_21_2.cc_iter_ctl(),
		* poly_21_2_lc_ptr = poly_21_2.lc_iter_ctl();
	report_unit<bool, true>("array_notrim_to_notrim_copy_assgn:t1_ptr", poly_21_1_cc_ptr + len_21_1 == poly_21_1_lc_ptr);
	report_unit<bool, true>("array_notrim_to_notrim_copy_assgn:t2_ptr", poly_21_2_cc_ptr + len_21_1 == poly_21_2_lc_ptr);
	report_unit<T_COEF_1, val_21_1>("array_notrim_to_notrim_copy_assgn:t1_val0", *poly_21_1_cc_ptr);
	report_unit<T_COEF_2, val_21_3>("array_notrim_to_notrim_copy_assgn:t2_val0", *poly_21_2_cc_ptr);
	report_unit<T_COEF_1, val_21_2>("array_notrim_to_notrim_copy_assgn:t1_vallast", *(poly_21_1_lc_ptr - 1));
	report_unit<T_COEF_2, val_21_4>("array_notrim_to_notrim_copy_assgn:t2_vallast", *(poly_21_2_lc_ptr - 1));



	constexpr T_COEF_1 val_22_1 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_22_1 = 7;
	T_COEF_1* arr_22_1_low = new T_COEF_1[len_22_1],
		* arr_22_1_high = arr_22_1_low + len_22_1;
	gda::init_internal<T_COEF_1, val_22_1>(arr_22_1_low, arr_22_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_22_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_22_1_low, arr_22_1_high);
	T_COEF_1* poly_22_1_cc_ptr = poly_22_1.cc_iter_ctl(),
		* poly_22_1_lc_ptr = poly_22_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_22_2;
	poly_22_2 = std::move(poly_22_1);
	T_COEF_1* poly_22_2_cc_ptr = poly_22_2.cc_iter_ctl(),
		* poly_22_2_lc_ptr = poly_22_2.lc_iter_ctl();
	report_unit<bool, true>("zero_array_notrim_to_trim_move_assgn:notrim_ptr", poly_22_1_cc_ptr + len_22_1 == poly_22_1_lc_ptr);
	report_unit<bool, true>("zero_array_notrim_to_trim_move_assgn:trim_ptr", poly_22_2_cc_ptr == poly_22_2_lc_ptr);

	constexpr T_COEF_1 val_23_1 = static_cast<T_COEF_1>(1),
		val_23_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_23_1 = 28;
	T_COEF_1* arr_23_1_low = new T_COEF_1[len_23_1],
		* arr_23_1_high = arr_23_1_low + len_23_1;
	gda::init_internal<T_COEF_1, val_23_1>(arr_23_1_low, arr_23_1_high - 7);
	gda::init_internal<T_COEF_1, val_23_2>(arr_23_1_high - 7, arr_23_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_23_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_23_1_low, arr_23_1_high);
	T_COEF_1* poly_23_1_cc_ptr = poly_23_1.cc_iter_ctl(),
		* poly_23_1_lc_ptr = poly_23_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, true> poly_23_2;
	poly_23_2 = std::move(poly_23_1);
	T_COEF_1* poly_23_2_cc_ptr = poly_23_2.cc_iter_ctl(),
		* poly_23_2_lc_ptr = poly_23_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_notrim_to_trim_move_assgn:notrim_ptr", poly_23_1_cc_ptr + len_23_1 == poly_23_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_notrim_to_trim_move_assgn:trim_ptr", poly_23_2_cc_ptr + len_23_1 - 7 == poly_23_2_lc_ptr);
	report_unit<bool, true>("nonzero_array_notrim_to_trim_move_assgn:low_ptr", poly_23_1_cc_ptr == poly_23_2_cc_ptr);

	constexpr T_COEF_1 val_24_1 = static_cast<T_COEF_1>(1),
		val_24_2 = static_cast<T_COEF_1>(0);
	constexpr T_DEG len_24_1 = 28;
	T_COEF_1* arr_24_1_low = new T_COEF_1[len_24_1],
		* arr_24_1_high = arr_24_1_low + len_24_1;
	gda::init_internal<T_COEF_1, val_24_1>(arr_24_1_low, arr_24_1_high - 7);
	gda::init_internal<T_COEF_1, val_24_2>(arr_24_1_high - 7, arr_24_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_24_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_24_1_low, arr_24_1_high);
	T_COEF_1* poly_24_1_cc_ptr = poly_24_1.cc_iter_ctl(),
		* poly_24_1_lc_ptr = poly_24_1.lc_iter_ctl();
	gda::uvp<T_COEF_1, T_DEG, false> poly_24_2;
	poly_24_2 = std::move(poly_24_1);
	T_COEF_1* poly_24_2_cc_ptr = poly_24_2.cc_iter_ctl(),
		* poly_24_2_lc_ptr = poly_24_2.lc_iter_ctl();
	report_unit<bool, true>("nonzero_array_trim_to_notrim_move_assgn:notrim_ptr", poly_24_1_cc_ptr + len_24_1 - 7 == poly_24_1_lc_ptr);
	report_unit<bool, true>("nonzero_array_trim_to_notrim_move_assgn:trim_ptr", poly_24_2_cc_ptr + len_24_1 - 7 == poly_24_2_lc_ptr);
	report_unit<bool, true>("nonzero_array_trim_to_notrim_move_assgn:low_ptr", poly_24_1_cc_ptr == poly_24_2_cc_ptr);

	/*

	constexpr T_COEF_1 val_25_1 = static_cast<T_COEF_1>(1),
		val_25_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_25_3 = static_cast<T_COEF_2>(val_25_1),
		val_25_4 = static_cast<T_COEF_2>(val_25_2);
	constexpr T_DEG len_25_1 = 28;
	T_COEF_1* arr_25_1_low = new T_COEF_1[len_25_1],
		* arr_25_1_high = arr_25_1_low + len_25_1;
	gda::init_internal<T_COEF_1, val_25_1>(arr_25_1_low, arr_25_1_high - 7);
	gda::init_internal<T_COEF_1, val_25_2>(arr_25_1_high - 7, arr_25_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_25_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_25_1_low, arr_25_1_high);
	T_COEF_1* poly_25_1_cc_ptr = poly_25_1.cc_iter_ctl(),
		* poly_25_1_lc_ptr = poly_25_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_25_2;
	poly_25_2 = std::move(poly_25_1);
	T_COEF_2* poly_25_2_cc_ptr = poly_25_2.cc_iter_ctl(),
		* poly_25_2_lc_ptr = poly_25_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_trim_move_assgn:t1_ptr", poly_25_1_cc_ptr + len_25_1 - 7 == poly_25_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_trim_move_assgn:t2_ptr", poly_25_2_cc_ptr + len_25_1 - 7 == poly_25_2_lc_ptr);
	report_unit<T_COEF_1, val_25_1>("array_trim_to_trim_move_assgn:t1_val0", *poly_25_1_cc_ptr);
	report_unit<T_COEF_2, val_25_3>("array_trim_to_trim_move_assgn:t2_val0", *poly_25_2_cc_ptr);

	constexpr T_COEF_1 val_26_1 = static_cast<T_COEF_1>(1),
		val_26_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_26_3 = static_cast<T_COEF_2>(val_26_1),
		val_26_4 = static_cast<T_COEF_2>(val_26_2);
	constexpr T_DEG len_26_1 = 28;
	T_COEF_1* arr_26_1_low = new T_COEF_1[len_26_1],
		* arr_26_1_high = arr_26_1_low + len_26_1;
	gda::init_internal<T_COEF_1, val_26_1>(arr_26_1_low, arr_26_1_high - 7);
	gda::init_internal<T_COEF_1, val_26_2>(arr_26_1_high - 7, arr_26_1_high);
	gda::uvp<T_COEF_1, T_DEG, true> poly_26_1 = gda::uvp<T_COEF_1, T_DEG, true>(arr_26_1_low, arr_26_1_high);
	T_COEF_1* poly_26_1_cc_ptr = poly_26_1.cc_iter_ctl(),
		* poly_26_1_lc_ptr = poly_26_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_26_2;
	poly_26_2 = std::move(poly_26_1);
	T_COEF_2* poly_26_2_cc_ptr = poly_26_2.cc_iter_ctl(),
		* poly_26_2_lc_ptr = poly_26_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_move_assgn:t1_ptr", poly_26_1_cc_ptr + len_26_1 - 7 == poly_26_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_move_assgn:t2_ptr", poly_26_2_cc_ptr + len_26_1 - 7 == poly_26_2_lc_ptr);
	report_unit<T_COEF_1, val_26_1>("array_trim_to_notrim_move_assgn:t1_val0", *poly_26_1_cc_ptr);
	report_unit<T_COEF_2, val_26_3>("array_trim_to_notrim_move_assgn:t2_val0", *poly_26_2_cc_ptr);

	constexpr T_COEF_1 val_27_1 = static_cast<T_COEF_1>(1),
		val_27_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_27_3 = static_cast<T_COEF_2>(val_27_1),
		val_27_4 = static_cast<T_COEF_2>(val_27_2);
	constexpr T_DEG len_27_1 = 28;
	T_COEF_1* arr_27_1_low = new T_COEF_1[len_27_1],
		* arr_27_1_high = arr_27_1_low + len_27_1;
	gda::init_internal<T_COEF_1, val_27_1>(arr_27_1_low, arr_27_1_high - 7);
	gda::init_internal<T_COEF_1, val_27_2>(arr_27_1_high - 7, arr_27_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_27_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_27_1_low, arr_27_1_high);
	T_COEF_1* poly_27_1_cc_ptr = poly_27_1.cc_iter_ctl(),
		* poly_27_1_lc_ptr = poly_27_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, true> poly_27_2;
	poly_27_2 = std::move(poly_27_1);
	T_COEF_2* poly_27_2_cc_ptr = poly_27_2.cc_iter_ctl(),
		* poly_27_2_lc_ptr = poly_27_2.lc_iter_ctl();
	report_unit<bool, true>("array_trim_to_notrim_move_assgn:t1_ptr", poly_27_1_cc_ptr + len_27_1 == poly_27_1_lc_ptr);
	report_unit<bool, true>("array_trim_to_notrim_move_assgn:t2_ptr", poly_27_2_cc_ptr + len_27_1 - 7 == poly_27_2_lc_ptr);
	report_unit<T_COEF_1, val_27_1>("array_notrim_to_trim_move_assgn:t1_val0", *poly_27_1_cc_ptr);
	report_unit<T_COEF_2, val_27_3>("array_notrim_to_trim_move_assgn:t2_val0", *poly_27_2_cc_ptr);
	report_unit<T_COEF_1, val_27_2>("array_notrim_to_trim_move_assgn:t1_vallast", *(poly_27_1_lc_ptr - 1));


	constexpr T_COEF_1 val_28_1 = static_cast<T_COEF_1>(1),
		val_28_2 = static_cast<T_COEF_1>(0);
	constexpr T_COEF_2 val_28_3 = static_cast<T_COEF_2>(val_28_1),
		val_28_4 = static_cast<T_COEF_2>(val_28_2);
	constexpr T_DEG len_28_1 = 28;
	T_COEF_1* arr_28_1_low = new T_COEF_1[len_28_1],
		* arr_28_1_high = arr_28_1_low + len_28_1;
	gda::init_internal<T_COEF_1, val_28_1>(arr_28_1_low, arr_28_1_high - 7);
	gda::init_internal<T_COEF_1, val_28_2>(arr_28_1_high - 7, arr_28_1_high);
	gda::uvp<T_COEF_1, T_DEG, false> poly_28_1 = gda::uvp<T_COEF_1, T_DEG, false>(arr_28_1_low, arr_28_1_high);
	T_COEF_1* poly_28_1_cc_ptr = poly_28_1.cc_iter_ctl(),
		* poly_28_1_lc_ptr = poly_28_1.lc_iter_ctl();
	gda::uvp<T_COEF_2, T_DEG, false> poly_28_2;
	poly_28_2 = std::move(poly_28_1);
	T_COEF_2* poly_28_2_cc_ptr = poly_28_2.cc_iter_ctl(),
		* poly_28_2_lc_ptr = poly_28_2.lc_iter_ctl();
	report_unit<bool, true>("array_notrim_to_notrim_move_assgn:t1_ptr", poly_28_1_cc_ptr + len_28_1 == poly_28_1_lc_ptr);
	report_unit<bool, true>("array_notrim_to_notrim_move_assgn:t2_ptr", poly_28_2_cc_ptr + len_28_1 == poly_28_2_lc_ptr);
	report_unit<T_COEF_1, val_28_1>("array_notrim_to_notrim_move_assgn:t1_val0", *poly_28_1_cc_ptr);
	report_unit<T_COEF_2, val_28_3>("array_notrim_to_notrim_move_assgn:t2_val0", *poly_28_2_cc_ptr);
	report_unit<T_COEF_1, val_28_2>("array_notrim_to_notrim_move_assgn:t1_vallast", *(poly_28_1_lc_ptr - 1));
	report_unit<T_COEF_2, val_28_4>("array_notrim_to_notrim_move_assgn:t2_vallast", *(poly_28_2_lc_ptr - 1));
	*/
}

#pragma endregion