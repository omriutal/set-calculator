#include "set.h"
#include "massages.h"
#include <stdio.h>
#include <stdlib.h>


Error read_set(Set x, int* nums) {
    int i = 0;
    set tmp;
    
    if (!nums || !x) {
        return NULL_ARGUMENT;
    }

    clean(&tmp);
    for (i = 0; i < (MAX_LEN/2); i++) {
        if (nums[i] == -1) {
            copy_set(&tmp, x);
            return NONE;
        } else if (nums[i] < START_RANGE || nums[i] > END_RANGE) {
            return INVALID_MEMBER_RANGE;
        }
        tmp.bits[nums[i]].value = 1;
    }
    return ILLEGAL_READ_ENDING;
}

void print_set(Set x) {
    int i = 0, j = 0;/* i for loop, j for counting vars */

    if (!x) {
        null_argument();
        return;
    }

    for (i = 0; i < SIZE; i++) {
        if (x->bits[i].value) {/* bit is 1 */
            if (j == MAX_PRINT) {/* max vars in line */
                printf(",\n");
                j = 0;
            } else if (j) {/* j != 0 -> not first var in line*/
                printf(", ");
            }
            printf("%d", i);
            j += 1;
        }
    }
    if (!j) {
        printf("This set is empty");
    }
    putchar('\n');
}

void union_set(Set x, Set y, Set z) {
    int i = 0;
    set g;

    if (!x || !y || !z) {
        return;
    }

    clean(&g);
    /* incase z is the same as x or y, we don't want to lose data so will put
        everything in g and then copy it to z */
    for (i = 0; i < SIZE; i ++) {
        if (x->bits[i].value || y->bits[i].value) {/* n belongs to x or y*/
            g.bits[i].value = 1;
        }
    }
    copy_set(&g, z);/* z = g */
}

void intersect_set(Set x, Set y, Set z) {
    int i = 0;
    set g;

    if (!x || !y || !z) {
        return;
    }

    clean(&g);
    /* incase z is the same as x or y, we don't want to lose data so will put
        everything in g and then copy it to z */
    for (i = 0; i < SIZE; i ++) {
        if (x->bits[i].value && y->bits[i].value) { /* n belongs to x and y */
            g.bits[i].value = 1;
        }
    }
    copy_set(&g, z);/* z = g */
}

void sub_set(Set x, Set y, Set z) {
    int i = 0;
    set g;

    if (!x || !y || !z) {
        return;
    }

    clean(&g);
    /* incase z is the same as x or y, we don't want to lose data so will put
        everything in g and then copy it to z */
    for (i = 0; i < SIZE; i ++) {
        if (x->bits[i].value) {/* n belongs to x */
            if (y->bits[i].value) {/* n belongs to y */
                g.bits[i].value = 0;
            } else {/* n doesn't belong to y */
                g.bits[i].value = 1;
            }
        }
    }
    copy_set(&g, z);/* z = g */
}

void symdiff_set(Set x, Set y, Set z) {
    set g, h, k;/* no need to 'clean' them since that happens in the functions */

    if (!x || !y || !z) {
        return;
    }

    sub_set(x, y, &g);/* g = x\y*/
    sub_set(y, x, &h);/* h = y\x */
    union_set(&g, &h, &k);/* k = (g and h) = (x\y) and (y\x) */
    copy_set(&k, z);/* z = k */
}

void stop() {
    exit(0);
}

void clean(Set x) {
    int i = 0;
    if (x) {
        for (i = 0; i < SIZE; i++) {
            x->bits[i].value = 0;
        }
    }
}

void copy_set(Set original, Set destination) {
    int i = 0;

    if (!original || !destination) {
        return;
    }

    if (original && destination) {/* og and dest aren't NULL */
        for (i = 0; i < SIZE; i ++) {
            destination->bits[i].value = original->bits[i].value;
        }
    }
}

