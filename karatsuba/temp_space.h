#ifndef _TEMP_SPACE_H
#define _TEMP_SPACE_H

int *temp_space(size_t size) {
    static const size_t n = 4096 / sizeof(int);
    int *base;
    base = (size <= n) ? ((int *) malloc(sizeof(int) * n))
                       : ((int *) malloc(sizeof(int) * size));
    return base;
}
#endif  // _TEMP_SPACE_H
