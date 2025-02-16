#ifndef SUPPORT_H_
#define SUPPORT_H_

#include <recomp_libc.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * @brief Finds the last (most significant) bit set in the given mask
 *
 * Finds the last (most significant) bit set in the given (int) mask and return the index of that
 * bit.
 *
 * Bits are numbered starting at 1, the least significant bit.
 *
 * @param mask The bit mask
 * @return The index of the bit if mask is not zero, 0 otherwise.
 * */
RECOMP_SUPPORT_DECLARATION(int fls(int mask));

/**
 * @brief Finds the last (most significant) bit set in the given mask
 *
 * Finds the last (most significant) bit set in the given (long) mask and return the index of that
 * bit.
 *
 * Bits are numbered starting at 1, the least significant bit.
 *
 * @param mask The bit mask
 * @return The index of the bit if mask is not zero, 0 otherwise.
 * */
RECOMP_SUPPORT_DECLARATION(int flsl(long mask));

/**
 * @brief Finds the last (most significant) bit set in the given mask
 *
 * Finds the last (most significant) bit set in the given (long long) mask and return the index of
 * that bit.
 *
 * Bits are numbered starting at 1, the least significant bit.
 *
 * @param mask The bit mask
 * @return The index of the bit if mask is not zero, 0 otherwise.
 * */
RECOMP_SUPPORT_DECLARATION(int flsll(long long mask));

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // SUPPORT_H_
