#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	const class nullptr_t{
	public:
		// convertible to any type of null non-member pointer...
		template<class T>
		operator T*() const { return 0; }

		// or any type of null member pointer...
		template<class C, class T>	// any type T for any class type C
		operator T C::*() const { return 0; }

	private:
		void operator&() const;	// Can't take address of nullptr
	} ft_nullptr = {};

	/**
	 * @brief enable_if
	 * At this time, we pass the condition we want to check to part B.
	 * If B is evaluated as true, the type of enable_if::value becomes T.
	 * And if B is false, value does not exist in enable_if.
	 * 
	 * @tparam B is_bool
	 * @tparam T type
	 */
	template <bool Cond, typename T = void>
	struct enable_if {};

	/**
	 * @brief enable_if
	 * 
	 * When B is true, type is defined in the specialized version.
	 * And in other cases, nothing is defined inside it.
	 * 
	 * @tparam T type
	 */
	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	/**
	 * @brief true_type / false_type
	 * It acts like an interface
	 * so that the value is not displayed every time.
	 */
	struct true_type { enum _value { value = true }; };
	struct false_type { enum _value { value = false }; };

	/**
	 * @brief remove_const
	 * remove const from template type.
	 * This is a specialization
	 * so that only T can be imported from const T.
	 * 
	 * @tparam T type
	 */
	template <typename T>
	struct remove_const { typedef T type };
	template <typename T>
	struct remove_const<T const> { typedef T type };

	/**
	 * @brief remove_volatile
	 * remove volatile from template type.
	 * This is a specialization
	 * so that only T can be imported from volatile T.
	 * 
	 * @tparam T type
	 */
	template<typename T>
	struct remove_volatile { typedef T type; };
	template<typename T>
	struct remove_volatile<T volatile> { typedef T type; };

	/**
	 * @brief remove_cv
	 * remove const and volatile from template type.
	 * 
	 * @tparam T type
	 */
	template<typename T>
	struct remove_cv { typedef typename remove_const<typename remove_volatile<T>::type>::type type; };

	/**
	 * @brief is_integral_helper
	 * Declare a meta function to remove the const qualifier.
	 */
	template <typename T>
	struct is_integral_helper : false_type {};

	/**
	 * @brief 
	 * After define so that specialization can be easily made into a macro,
	 * the integral type is specialized.
	 */
	#define IS_INTEGRAL_SPECIALIZATION(T) template<> struct is_integral_helper<T> : true_type {}

	IS_INTEGRAL_SPECIALIZATION(bool);
	IS_INTEGRAL_SPECIALIZATION(char);
	IS_INTEGRAL_SPECIALIZATION(signed char);
	IS_INTEGRAL_SPECIALIZATION(short int);
	IS_INTEGRAL_SPECIALIZATION(int);
	IS_INTEGRAL_SPECIALIZATION(long int);
	IS_INTEGRAL_SPECIALIZATION(long long int);
	IS_INTEGRAL_SPECIALIZATION(unsigned char);
	IS_INTEGRAL_SPECIALIZATION(unsigned short int);
	IS_INTEGRAL_SPECIALIZATION(unsigned int);
	IS_INTEGRAL_SPECIALIZATION(unsigned long int);
	IS_INTEGRAL_SPECIALIZATION(unsigned long long int);

/**
 * @brief is_integral
 * Identifies whether T is an integral type.
 * It inherits is_integral_helper<T> and has a different type according to T.
 * Whether the const and volatile qualifier is attached or not,
 * it does not change whether it is an integral type or not,
 * so remove it and pass it over.
 * 
 * @tparam T type
 */
	template <typename T>
	struct is_integral : public is_integral_helper<typename remove_cv<T>::type> {};

} // namespace ft

#endif
