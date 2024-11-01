#include "lists.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
    ListStruct List = {};

    ListCtor(&List);
    DotDump(&List);

    ListDtor(&List);
    DotDump(&List);

    return 0;
}