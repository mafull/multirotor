#ifndef __ASSERT_HPP
#define __ASSERT_HPP

/// Assert macro that calls a custom callback function
#define ASSERT(expr) \
    if (!(expr)) \
        assert_failed(__FILE__, __LINE__)

/// A function pointer typedef used to configure the assert callback
typedef void (*assert_funcptr_t)(const char *, int);
static assert_funcptr_t assert_failed = nullptr;

/**
 * Configure the assert callback function
 * @param[in] funcPtr Function pointer for the external callback function
 */
static void assert_init(assert_funcptr_t funcPtr)
{
    assert_failed = funcPtr;
}

#endif  // __ASSERT_HPP
