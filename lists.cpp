#include "lists.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static IsEmpty EmptyChecker(ListStruct* list);
static Status  ReallocUp(ListStruct* list);
static Status  ReallocDown(ListStruct* list);
static Status  ReallocIfNeeded(ListStruct* list);
static index_t FindValRecursion(ListStruct* list, index_t current_ind, index_t node_ind, const elem_t elem);

//---------------------------------- PUBLIC ------------------------------------

//=================================== CTOR =====================================
Status ListCtor(ListStruct* list) {
    assert(list != nullptr);

    list->capacity = kMinNumOfElems;
    list->data = (Node*)calloc(list->capacity, sizeof(Node));

    assert(list->data != nullptr);

    list->FreeList = 1;

    list->data[0].value = 0;
    list->data[0].next =  0;
    list->data[0].prev =  0;

    for (size_t i = 1; i < list->capacity; i++) {
        list->data[i].value = 0;
        list->data[i].next =  i + 1;
        list->data[i].prev =  0;
    }

    list->data[list->capacity - 1].next =  0;

    list->error = ListError_kOk;
    list->verif = VERIFICATION_PASSED;

    return SUCCESS;
}

//=================================== DTOR =====================================
Status ListDtor(ListStruct* list) {
    assert(list != nullptr);

    free(list->data);
    memset(list, 0, sizeof(ListStruct));

    return SUCCESS;
}

//================================= LIST PUSH ===================================
Status ListPush(ListStruct* list, const elem_t elem) { //useless
    assert(list != nullptr);

    ReallocIfNeeded(list);

    list->data[list->data[0].next].value = elem;
    list->data[list->data[0].next].next++;
    list->data[list->data[0].next].prev--;
    list->data[0].next++;

    return SUCCESS;
}

//================================== LIST POP ===================================
Status ListPop(ListStruct* list) { //useless
    assert(list != nullptr);

    if (EmptyChecker(list) == kEmpty) {
        list->error = ListError_kEraseOnEmptyList;
        return FAILURE;
    }

    list->data[0].next--;

    ReallocIfNeeded(list);

    return SUCCESS;
}

//=============================== VERIFICATION =================================
VerificationStatus Verificator(ListStruct* list) { //еще будет дописываться
    assert(list != nullptr);

    return VERIFICATION_PASSED;
}

//=================================== DUMP =====================================
void_sex DotDump(ListStruct* list) {
    assert(list != nullptr);

}

//================================ INSERT FRONT ================================
// вставки элемента в начало списка
Status InsertFront(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    if (ReallocIfNeeded(list) == FAILURE) {
        list->error = ListError_kMemoryAllocationError;
        return FAILURE;
    }

    // if (InsertNextInd(list, elem, list->data[0].next) == SUCCESS) {
    //     return SUCCESS;
    // }
    // else {
    //     return FAILURE;
    // }

    //по идее одно и то же самое  ^3^

    index_t ind_inserted_front = list->FreeList;

    list->FreeList = list->data[ind_inserted_front].next;

    list->data[ind_inserted_front].value = elem;
    list->data[ind_inserted_front].next = list->data[0].next;
    list->data[ind_inserted_front].prev = 0;

    list->data[list->data[0].next].prev = ind_inserted_front;
    list->data[0].next = ind_inserted_front;

    return SUCCESS;
}

//================================ INSERT BACK =================================
// вставки элемента в конец списка
Status InsertBack(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    if (ReallocIfNeeded(list) == FAILURE) {
        list->error = ListError_kMemoryAllocationError;
        return FAILURE;
    }

//    if (InsertPrevInd(list, elem, list->data[0].prev) == SUCCESS) {
//     return SUCCESS;
//    }
//    else return FAILURE;

    index_t ind_inserted_back = list->FreeList;

    list->FreeList = list->data[ind_inserted_back].next;

    list->data[ind_inserted_back].value = elem;
    list->data[ind_inserted_back].next =  0;
    list->data[ind_inserted_back].prev =  list->data[0].prev;

    list->data[list->data[0].prev].next = ind_inserted_back;
    list->data[0].prev = ind_inserted_back;

    return SUCCESS;
}

//============================== INSERT NEXT IND ===============================
// вставки элемента после заданного индекса
Status InsertNextInd(ListStruct* list, const elem_t elem, /*const??*/ index_t ind_of_given_elem) {
    assert(list != nullptr);

    if (ReallocIfNeeded(list) == FAILURE) {
        list->error = ListError_kMemoryAllocationError;
        return FAILURE;
    }
    if (ind_of_given_elem >= list->capacity) {
        list->error = ListError_kWrongIndex;
        return FAILURE;
    }

    index_t inserted_ind = list->FreeList;

    if (inserted_ind == 0) {
        list->error = ListError_kWrongIndex;
        return FAILURE;
    }
    if (inserted_ind >= list->capacity) {
        list->error = ListError_kWrongIndex;
        return FAILURE;
    }

    list->FreeList = list->data[inserted_ind].next;

    list->data[inserted_ind].value = elem;
    list->data[inserted_ind].prev =  ind_of_given_elem;
    list->data[inserted_ind].next =  list->data[ind_of_given_elem].next;

    if (list->data[ind_of_given_elem].next != 0
     && list->data[ind_of_given_elem].next < list->capacity) {
        list->data[list->data[ind_of_given_elem].next].prev = inserted_ind;
    }

    list->data[ind_of_given_elem].next = inserted_ind;

    return SUCCESS;
}

//============================== INSERT NEXT VAL ===============================
// вставки элемента после заданного элемента
Status InsertNextVal(ListStruct* list, const elem_t inserted_elem, const elem_t value) {
    assert(list != nullptr);

    index_t ind_of_value = FindVal(list, value);

    if (ind_of_value == (size_t)-1) {
        return FAILURE;
    }

    if (InsertNextInd(list, inserted_elem, ind_of_value) == SUCCESS) {
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
}

//============================== INSERT PREV IND ===============================
// вставки элемента перед заданным индексом
Status InsertPrevInd(ListStruct* list, const elem_t elem, index_t ind_of_given_elem) {
    assert(list != nullptr);

    if (ReallocIfNeeded(list) == FAILURE) {
        list->error = ListError_kMemoryAllocationError;
        return FAILURE;
    }
    if (ind_of_given_elem > list->capacity) {
        list->error = ListError_kWrongIndex;
        return FAILURE;
    }

    index_t ind_inserted = list->FreeList;

    list->FreeList = list->data[ind_inserted].next;

    list->data[ind_inserted].value = elem;
    list->data[ind_inserted].next =  ind_of_given_elem;
    list->data[ind_inserted].prev =  list->data[ind_of_given_elem].prev;

    if (list->data[ind_of_given_elem].prev != 0) {
        list->data[list->data[ind_of_given_elem].prev].next = ind_inserted;
    }
    list->data[ind_of_given_elem].prev = ind_inserted;

    return SUCCESS;
}

//============================== INSERT PREV VAL ===============================
// вставки элемента перед заданным элементом
Status InsertPrevVal(ListStruct* list, const elem_t inserted_elem, const elem_t value) {
    assert(list != nullptr);

    index_t ind_of_value = FindVal(list, value);

    if (ind_of_value == (size_t)-1) {
        return FAILURE;
    }

    if (InsertPrevInd(list, inserted_elem, ind_of_value) == SUCCESS) {
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
}

//================================== ERASE =====================================
// удаления заданного элемента + с конца с начала с заданного элемента и т.д.
Status Erase(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    index_t current_ind = list->data[0].next;

    while (current_ind < list->capacity && current_ind != 0) {
        if (list->data[current_ind].value == elem) {
            if (list->data[current_ind].prev != 0) {
                list->data[list->data[current_ind].next].next = list->data[current_ind].next;
            }
            if (list->data[current_ind].next != 0) {
                if (list->data[current_ind].next < list->capacity) {
                    list->data[list->data[current_ind].next].prev = list->data[current_ind].prev;
                }
            }
            list->data[current_ind].next = list->FreeList;
            list->data[current_ind].prev = 0;

            list->FreeList = current_ind;

            list->error = ListError_kOk;
            return SUCCESS;
        }
        current_ind = list->data[current_ind].next;
    }

    return FAILURE;
}

//================================= FIND VAL ==================================
// поиска элемента по его значению
//index_t FindVal(ListStruct* list, const elem_t elem) {
//     assert(list != nullptr);

//     index_t current_index = list->data[0].next;

//     while (current_index != 0 && current_index < list->capacity) {
//         if (list->data[current_index].value == elem) {
//             return current_index;
//         }
//         current_index = list->data[current_index].next;
//     }

//     return -1;
// }

index_t FindVal(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    return FindValRecursion(list, list->data[0].next, 0, elem);
}

static index_t FindValRecursion(ListStruct* list, index_t current_ind, index_t node_ind, const elem_t elem) {
    assert(list != nullptr);

    if (current_ind == 0) {
        list->error = ListError_kWrongIndex;
        return -1;
    }
    if (current_ind >= list->capacity) {
        list->error = ListError_kWrongIndex;
        return -1;
    }

    if (list->data[current_ind].value == elem) {
        return current_ind;
    }

    return FindValRecursion(list, list->data[current_ind].next, node_ind++, elem);
}

//================================ FIND INDEX ==================================
elem_t FindIndex(ListStruct* list, index_t ind_of_given_elem) {
    assert(list != nullptr);

    if (ind_of_given_elem >= list->capacity) {
        list->error = ListError_kHeadOutOfList;
        return -1;
    }
    if (ind_of_given_elem == 0) {
        list->error = ListError_kWrongIndex;
        return -1;
    }

    return list->data[ind_of_given_elem].value;
}

//---------------------------------- STATIC ------------------------------------

//================================= IS EMPTY ===================================
static IsEmpty EmptyChecker(ListStruct* list) { //мем в том что реально нужен только для попа а нам поп и не нужен
    //NOTE возможно и не нужно если работаем со списком содержащим фантомный элемент
    assert(list != nullptr);

    if ((list->data[0].next - list->data[0].prev) == 1) {
        return kEmpty;
    }
    else if ((list->data[0].prev - list->data[0].next) == 1) {
        return kFull;
    }
    else {
        return kNotEmpty;
    }
}

//================================= REALLOC UP =================================
static Status ReallocUp(ListStruct* list) {
    assert(list != nullptr);

    list->capacity *= kMultiplier;
    list->data = (Node*)realloc(list->data, (list->capacity * sizeof(Node)));

    if (list->data == nullptr) {
        list->error = ListError_kMemoryAllocationError;
        //NOTE тут не нужно ли тогда free()-шить?
        return FAILURE;
    }

    return SUCCESS;
}

//================================ REALLOC DOWN =================================
static Status ReallocDown(ListStruct* list) {
    assert(list != nullptr);

    list->capacity /= kMultiplier;
    list->data = (Node*)realloc(list->data, (list->capacity * sizeof(Node)));

    if (list->data == nullptr) {
        list->error = ListError_kMemoryAllocationError;
        return FAILURE;
    }

    return SUCCESS;
}

//============================= REALLOC IF NEEDED ===============================
static Status ReallocIfNeeded(ListStruct* list) {
    assert(list != nullptr);

    if (list->data[0].next < list->capacity / kDivForReallocDown
     && list->capacity > kMinNumOfElems) {
        if (ReallocDown(list) == FAILURE) {
            list->error = ListError_kReallocationfailed;
            return FAILURE;
        }
    }

    if (list->data[0].next >= list->capacity) {
        if (ReallocUp(list) == FAILURE) {
            return FAILURE;
        }
    }

    return SUCCESS;
}
