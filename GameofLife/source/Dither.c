#include "../include/Dither.h"
static size_t bit_reverse(size_t szam, size_t bitlen) {
    size_t result = 0;
    for (size_t i = 0; i < bitlen; i++) {
        int shift = (bitlen - 1 - 2 * i);
        size_t get_bit = (szam & 1 << i);
        result |= shift >= 0 ? get_bit << shift : get_bit >> -shift;
    }
    return result;
}
static size_t bit_interleave(size_t szam1, size_t szam2) {
    size_t bitlen = sizeof(size_t) * 8;
    size_t result = 0;
    for (size_t i = 0; i < bitlen; i++) {
        result |= (szam1 & 1 << i) << i;
        result |= (szam2 & 1 << i) << (i + 1);
    }
    return result;
}
static size_t log_base_2(size_t szam) {
    for (size_t i = 0; i < sizeof(size_t) * 8; i++) {
        if ((szam & 1 << i) != 0) return i;
    }
    return 0;
}
/**
 * @brief Elkesziti a Bayer matrixot a rendezett ditheringhez
 * @param n a matrix merete
 * @return Az elkeszitett bayer matrix, a memoria felszabaditas a hivo feladata,
 *  az erre keszitett fugvennyel
 * @remark A matematika keplet forrasa: https://en.wikipedia.org/wiki/Ordered_dithering
 */
size_t **Dgenerate_bayer_matrix(size_t n) {
    size_t **matrix = (size_t **)malloc(n * sizeof(size_t *));
    matrix[0] = (size_t *)malloc(n * n * sizeof(size_t));
    size_t bitlen = log_base_2(n);
    for (size_t i = 0; i < n; i++) {
        matrix[i] = matrix[0] + i * n;
        for (size_t j = 0; j < n; j++) {
            matrix[i][j] = bit_reverse(bit_interleave(i ^ j, i), 2 * bitlen);
        }
    }
    return matrix;
}
void Dfree_bayer_matrix(size_t **matrix) {
    free(matrix[0]);
    free(matrix);
}