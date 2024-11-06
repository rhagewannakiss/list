#include "lists.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
    ListStruct list = {};

    if (ListCtor(&list) == SUCCESS) {
        printf("meow1\n");
    }

    elem_t num_array[] = {23, 56, 765, 456, 34, 2, 45, 7, 34, 65, 745, 57, 56, 3, 45, 6, 76, 4, 4, 34, 5, 2, 326, 457, 56, 8, 6, 45, 64, 43, 64, 57};
    for (size_t i = 0; i < sizeof(num_array)/sizeof(elem_t); i++) {
        if (InsertFront(&list, num_array[i]) == FAILURE) {
            printf("popa\n");
        }
    }

    if (InsertFront(&list, 78) == FAILURE) {
        printf("chikinsssss\n");
    } printf("kiki\n");

    for (size_t i = 0; i < sizeof(num_array)/sizeof(elem_t); i++) {
        if (InsertPrevVal(&list, num_array[i], 65) == FAILURE) {
            printf("popa\n");
        }
    }

   if (InsertNextInd(&list, 299, 8) == FAILURE) {
       printf("gooofyyasss\n");
   } else printf("haha");

   if (InsertPrevInd(&list, 34, 6) == FAILURE) {
        printf("eshkereee\n");
   } else printf("dfpsdif\n");

    if (InsertNextVal(&list, 67, 57) == FAILURE) {
        printf("hooodaaa\n");
    } else printf("kfdks\n");

    if (InsertPrevVal(&list, 56, 67) == FAILURE) {
        printf("bitchwhaaat\n");
    } else printf("gogo\n");

    if (Erase(&list, 4) == FAILURE) {
        printf("byebye");
    } else printf("jaja");

    if (Erase(&list, 457) == FAILURE) {
        printf("dafuq\n");
    } else printf("kaka)");

    printf("find 7: %X\n", FindVal(&list, 7));
    printf("find 4: %X\n", FindVal(&list, 4));
    printf("find 23: %X\n", FindVal(&list, 23));
    printf("find 56: %X\n", FindVal(&list, 56));
    printf("find 456: %X\n", FindVal(&list, 456));
    printf("find 34: %X\n", FindVal(&list, 34));
    printf("find 2: %X\n", FindVal(&list, 2));
    printf("find 45: %X\n", FindVal(&list, 45));
    printf("find 65: %X\n", FindVal(&list, 65));
    printf("find 745: %X\n", FindVal(&list, 745));
    printf("find 57: %X\n", FindVal(&list, 57));
    printf("find 3: %X\n", FindVal(&list, 3));
    printf("find 45: %X\n", FindVal(&list, 45));
    printf("find 6: %X\n", FindVal(&list, 6));
    printf("find 76: %X\n", FindVal(&list, 76));
    printf("find 326: %X\n", FindVal(&list, 326));
    printf("find 8: %X\n", FindVal(&list, 8));

    printf("find ind 7: %X\n", FindIndex(&list, 7));
    printf("find ind 70: %X\n", FindIndex(&list, 70));

    if (InsertPrevInd(&list, 45, 20) == FAILURE) {
        printf("lolloolol\n");
    } else printf("apapaap\n");

    if (ListDtor(&list) == SUCCESS) {
        printf("meow4\n");
    } else printf("juju\n");

    return 0;
}