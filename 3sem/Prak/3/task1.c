#include <limits.h>
STYPE bit_reverse(STYPE value)
{
    enum
    {
        SHIFT = 1,
        DEF_VALUE = 0
    };
    UTYPE res = DEF_VALUE;
    value = (UTYPE) value;

    for (int i = 0;i < sizeof(STYPE) * CHAR_BIT; i++) {
        res = res << SHIFT;
        res = res + (value & 0x1);
        value = value >> SHIFT;
    }
    return (STYPE) res;
}