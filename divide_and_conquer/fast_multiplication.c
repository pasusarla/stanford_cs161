#include <stdio.h>
#include <string.h>
#include <gmp.h>

#define DEBUG 0

void karatsuba_mult(mpz_t res, mpz_t first, mpz_t second) {
    char _a[16384], _b[16384], _c[16384], _d[16384], *_first, *_second;
    int size_first, size_second;
    mpz_t a, b, c, d, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, libres;

#ifdef DEBUG
    mpz_mul(libres, first, second);
#endif

    if (mpz_cmp_si(first, (long)10) < 0 || mpz_cmp_si(second, (long)10) < 0) {
#ifdef DEBUG
#if (DEBUG > 1)
        gmp_printf("In recursive base case with first: %Zd and second: %Zd\n", first, second);
#endif
#endif
        mpz_mul(res, first, second);
#ifdef DEBUG
#if (DEBUG > 1)
        gmp_printf("first: %Zd, second: %Zd, res: %Zd\n", first, second, res);
#endif
#endif
        return;
    }

    _first = mpz_get_str(NULL, 10, first);
    size_first = strlen(_first);
    _second = mpz_get_str(NULL, 10, second);
    size_second = strlen(_second);

    if (size_first == size_second) {
        memcpy(_a, _first, size_first/2 + size_first%2);
        _a[size_first/2 + size_first%2] = '\0';
        mpz_init_set_str(a, _a, 10);

        memcpy(_b, _first + size_first/2 + size_first%2, size_first/2);
        _b[size_first/2] = '\0';
        mpz_init_set_str(b, _b, 10);

        memcpy(_c, _second, size_second/2 + size_second%2);
        _c[size_second/2 + size_second%2] = '\0';
        mpz_init_set_str(c, _c, 10);

        memcpy(_d, _second + size_second/2 + size_second%2, size_second/2);
        _d[size_second/2] = '\0';
        mpz_init_set_str(d, _d, 10);
    } else if (size_first > size_second) {
        memcpy(_a, _first, size_first/2 + size_first%2);
        _a[size_first/2 + size_first%2] = '\0';
        mpz_init_set_str(a, _a, 10);

        memcpy(_b, _first + size_first/2 + size_first%2, size_first/2);
        _b[size_first/2] = '\0';
        mpz_init_set_str(b, _b, 10);

        memcpy(_c, _second, size_second/2);
        _c[size_second/2] = '\0';
        mpz_init_set_str(c, _c, 10);

        memcpy(_d, _second + size_second/2, size_second/2 + size_second%2);
        _d[size_second/2 + size_second%2] = '\0';
        mpz_init_set_str(d, _d, 10);
    } else {
        memcpy(_a, _first, size_first/2);
        _a[size_first/2] = '\0';
        mpz_init_set_str(a, _a, 10);

        memcpy(_b, _first + size_first/2, size_first/2 + size_first%2);
        _b[size_first/2 + size_first%2] = '\0';
        mpz_init_set_str(b, _b, 10);

        memcpy(_c, _second, size_second/2 + size_second%2);
        _c[size_second/2 + size_second%2] = '\0';
        mpz_init_set_str(c, _c, 10);

        memcpy(_d, _second + size_second/2 + size_second%2, size_second/2);
        _d[size_second/2] = '\0';
        mpz_init_set_str(d, _d, 10);
    }

#ifdef DEBUG
#if (DEBUG > 1)
    printf("_first: %s, with size: %d\n", _first, size_first);
    printf("_second: %s, with size: %d\n", _second, size_second);
    gmp_printf("a: %Zd, b: %Zd, c: %Zd, d: %Zd\n", a, b, c, d);
#endif

#if (DEBUG == 1)
    printf("_first: %s, _second: %s\n", _first, _second);
#endif
#endif

    karatsuba_mult(p1, a, c);
    karatsuba_mult(p2, b, d);

    mpz_add(p4, a, b);
    mpz_add(p5, c, d);
    karatsuba_mult(p3, p4, p5);
    mpz_add(p6, p1, p2);
    mpz_sub(p7, p3, p6);

#ifdef DEBUG
#if (DEBUG > 1)
    gmp_printf("ac: %Zd, bd: %Zd, (a+b)(c+d): %Zd, 3-2-1: %Zd\n", p1, p2, p3, p7);
#endif
#endif

    mpz_ui_pow_ui(p11, 10, 2*((size_first >= size_second ? size_first : size_second)/2));
    mpz_ui_pow_ui(p12, 10, (size_first >= size_second ? size_first : size_second)/2);
    mpz_mul(p8, p1, p11);
    mpz_mul(p9, p7, p12);
    mpz_add(p10, p8, p9);

#ifdef DEBUG
#if (DEBUG > 1)
    gmp_printf("10nac: %Zd, 10n/2(3-2-1): %Zd, bd: %Zd\n", p8, p9, p2);
#endif
#endif

    mpz_add(res, p10, p2);

#ifdef DEBUG
    if (mpz_cmp(res, libres) != 0) gmp_printf("first: %Zd, second: %Zd, res: %Zd\n", first, second, res);
#endif
}

int main() {
    mpz_t a, b, res;

    mpz_inits(a, b, res);

    printf("Enter the first integer: ");
    printf("%d\n",gmp_scanf("%Zd", a));

    printf("Enter the second integer: ");
    printf("%d\n", gmp_scanf("%Zd", b));

    karatsuba_mult(res, a, b);
    gmp_printf("The result with the Karatsuba method is          %Zd.\n", res);
#ifdef DEBUG
    mpz_mul(res, a, b);
    gmp_printf("The result with the built-in library function is %Zd.\n", res);
#endif

    return 0;
}
