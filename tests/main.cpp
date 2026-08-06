#include "fb/concepts/concepts.hpp"
#include "fb/math/math.hpp"
#include "fb/Tuple.hpp"
#include "fb/type_traits/type_traits.hpp"

int main()
{
    static_assert(fb::is_same_v<fb::add_const_t<int>, const int>);
    static_assert(fb::is_same_v<fb::add_volatile_t<int>, volatile int>);
    static_assert(fb::is_same_v<fb::add_cv_t<int>, const volatile int>);
    static_assert(fb::is_same_v<fb::remove_const_t<const int>, int>);
    static_assert(fb::is_same_v<fb::remove_volatile_t<volatile int>, int>);
    
    using clean_cv = fb::remove_cv_t<const volatile int>;
    static_assert(fb::is_same_v<clean_cv, int>);

    static_assert(fb::is_same_v<fb::add_lvalue_reference_t<int>, int&>);
    static_assert(fb::is_same_v<fb::add_rvalue_reference_t<int>, int&&>);
    
    using clean_lval_ref = fb::remove_reference_t<int&>;
    static_assert(fb::is_same_v<clean_lval_ref, int>);
    
    using clean_rval_ref = fb::remove_reference_t<int&&>;
    static_assert(fb::is_same_v<clean_rval_ref, int>);
    
    using clean_cvref = fb::remove_cvref_t<const int&>;
    static_assert(fb::is_same_v<clean_cvref, int>);

    static_assert(fb::is_same_v<fb::add_pointer_t<int&>, int*>);
    static_assert(fb::is_same_v<fb::remove_pointer_t<int* const>, int>);

    static_assert(fb::is_void_v<void>);
    static_assert(fb::is_integral_v<int>);
    static_assert(fb::is_floating_point_v<float>);
    static_assert(fb::is_array_v<int[]>);
    static_assert(fb::is_pointer_v<int*>);
    static_assert(fb::is_function_v<void(int)>);

    static_assert(fb::is_lvalue_reference_v<int&>);
    static_assert(fb::is_rvalue_reference_v<int&&>);
    static_assert(fb::is_reference_v<int&> && fb::is_reference_v<int&&>);

    static_assert(fb::is_arithmetic<int>::value && fb::is_arithmetic<double>::value);

    static_assert(fb::is_trivially_copyable_v<int>);
    static_assert(fb::is_nontrivially_copyable_v<int> == false);

    static_assert(fb::is_same_v<int, int>);
    static_assert(fb::is_convertible<int, double>::value);

    static_assert(fb::integral_constant<int, 42>::value == 42);
    static_assert(fb::is_same_v<fb::conditional_t<true, int, double>, int>);
    static_assert(fb::is_same_v<fb::decay_t<int[]>, int*>);
    
    typename fb::enable_if<true, int>::type compile_check = 0;
    (void)compile_check;

    using declval_test = decltype(fb::declval<int>() + fb::declval<double>());
    static_assert(fb::is_same_v<declval_test, double>);

    static_assert(fb::is_same_v<fb::void_t<int, double, char>, void>);

    static_assert(fb::is_same_v<fb::add_lvalue_reference_t<void>, void>);
    static_assert(fb::is_trivially_copyable_v<int>);
}
