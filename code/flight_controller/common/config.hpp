#ifndef CONGIG_HPP
#define CONFIG_HPP

typedef void (*assert_funcptr_t)(const char *, int);
assert_funcptr_t assert_failed = nullptr;

#define ASSERT(expr) \
    if (!(expr)) \
        assert_failed(__FILE__, __LINE__)

void assert_init(const assert_funcptr_t funcptr)
{
    assert_failed = funcptr;
}

#endif  // CONFIG_HPP
