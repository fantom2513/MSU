int satsum(int v1, int v2)
{
    enum { ZERO = 0 };
    unsigned int int_min, int_max;
    int_max = ~ZERO;
    int_max = int_max >> 1;
    int_min = ~int_max;

    if (v1 >= 0 && v2 >= 0) {
        if (int_max - v1 <= v2)
            return int_max;
        return v1 + v2;
    } else if (v1 < 0 && v2 < 0) {
        if ((signed) int_min - v1 >= v2)
            return int_min;
        return v1 + v2;
    }
    return v1 + v2;
}