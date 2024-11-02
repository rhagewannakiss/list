#include "lists.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <memory.h>
#include <math.h>

static IsEmpty EmptyChecker(ListStruct* list);
static Status  ReallocUp(ListStruct* list);
static Status  ReallocDown(ListStruct* list);
static Status  ReallocIfNeeded(ListStruct* list);

//---------------------------------- PUBLIC ------------------------------------

//=================================== CTOR =====================================
Status ListCtor(ListStruct* list) {
    assert(list != nullptr);

    list->capacity = kMinNumOfElems;
    list->data = (Node*)calloc(list->capacity, sizeof(Node));

    list->FreeList = list->data->next;
    // FIXME сформировать список свободных элементов
    list->data[0].value = 0;
    list->data[0].next =  0;
    list->data[0].prev =  0;

    for (size_t i = 1; i < list->capacity; i++) {
        list->data[i].value = 0;
        list->data[i].next =  i + 1;
        list->data[i].prev =  0;
    }

    list->error = ListError_kOk;
    list->verif = VERIFICATION_PASSED;

    return SUCCESS;
}

//=================================== DTOR =====================================
Status ListDtor(ListStruct* list) {
    assert(list != nullptr);

    free(list);
    memset(list, 0, sizeof(list));

    return SUCCESS;
}

//================================= LIST PUSH ===================================
Status ListPush(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    ReallocIfNeeded(list);

    list->data[list->data[0].next].value = elem;
    list->data[list->data[0].next].next++;
    list->data[list->data[0].next].prev--;
    list->data[0].next++;

    return SUCCESS;
}

//================================== LIST POP ===================================
Status ListPop(ListStruct* list, const elem_t elem) {
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

//=============================== GET FRONT PTR ================================
index_t GetFrontPtr(ListStruct* list) {
    //NOTE всм возвращать индекс первого элемента если это буквально первый элемент непон пойман
    assert(list != nullptr);
    index_t searched_index = 0;

    if (EmptyChecker(list) == kEmpty) {
        list->error = ListError_kFrontIndexOnEmptyList;
        list->verif = VERIFICATION_FAILED;
        return -1;
    }

    list->verif = VERIFICATION_PASSED;
    return searched_index;
}

//================================ GET BACK PTR ================================
index_t GetBackPtr(ListStruct* list) {
    assert(list != nullptr);

    if (EmptyChecker(list) == kEmpty) {
        list->error = ListError_kBackIndexOnEmptyList;
        return -1;
    }


}

//================================ GET NEXT PTR ================================
index_t GetNextPtr(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    index_t index_of_next_elem = 0;

    if (EmptyChecker(list) == kEmpty) {
        list->error = ListError_kNextIndexOnEmptyList;
        return -666;
    }

    if (EmptyChecker(list) == kFull) {
        if (ReallocIfNeeded(list) == FAILURE) {
            list->error = ListError_kMemoryAllocationError;
            return -1;
        };
    }



    return index_of_next_elem;
}

//================================ GET PREV PTR ================================
// получения указателя на элемент, предшествующий данному
index_t GetPrevPtr(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    if (EmptyChecker(list) == kEmpty) {
        list->error = ListError_kPrevIndexOnEmptyList;
        return -1;
    }
}

//================================ INSERT FRONT ================================
// вставки элемента в начало списка
Status InsertFront(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    //тут еще какие-нибудь проверки например

    if (InsertNext(list, elem, list->data[0].next) == SUCCESS) {
        return SUCCESS;
    }
}

//================================ INSERT BACK =================================
// вставки элемента в конец списка
Status InsertBack(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    //еще проверки если будет нужно

   if (InsertPrev(list, elem, list->data[0].prev) == SUCCESS) {
    return SUCCESS;
   }

}

//================================ INSERT NEXT =================================
// вставки элемента перед заданным элементом
Status InsertNext(ListStruct* list, const elem_t elem, /*const??*/ index_t ind_of_given_elem) {
    assert(list != nullptr);

    index_t current_index = ListPush(list, elem);

}

//================================ INSERT PREV =================================
// вставки элемента после заданного элемента
Status InsertPrev(ListStruct* list, const elem_t elem, index_t ind_of_given_elem) {
    assert(list != nullptr);


}

//================================== ERASE =====================================
// удаления заданного элемента + с конца с начала с заданного элемента и т.д.
void_sex Erase(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    index_t current_ind = list->data[0].next;

    while (current_ind != list->capacity) {
        if (list->data[current_ind].value == elem) {
            if (list->data[current_ind].prev != -1) {
                list->data[list->data[current_ind].next].next = list->data[current_ind].next;
            }
        }
         if (list->data[current_ind].next != -1) {
                list->data[list->data[current_ind].next].prev = list->data[current_ind].prev;
        }
        current_ind = list->data[current_ind].next;
    }
    list->error = ListError_kOk;
}

//=================================== FIND =====================================
// поиска элемента по его значению
index_t Find(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    index_t current_index = list->data[0].next;

    while (current_index > 0) {
        if (list->data[current_index].value == elem) {
            return current_index;
        }
        current_index = list->data[current_index].next;
    }

    return -1;
}

//================================ FIND INDEX ==================================
elem_t FindIndex(ListStruct* list, index_t ind_of_given_elem) {
    assert(list != nullptr);

    if (ind_of_given_elem >= list->capacity) {
        list->error = ListError_kHeadOutOfList;
        return -1;
    }
    //NOTE нужно ли проверять size_t на отрицательность если это априори unsigned

    return list->data[ind_of_given_elem].value;
}

//---------------------------------- STATIC ------------------------------------

//================================= IS EMPTY ===================================
static IsEmpty EmptyChecker(ListStruct* list) {
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
    list->data = (Node*)realloc(list->data, (size_t)(list->capacity * sizeof(Node)));

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
    list->data = (Node*)realloc(list->data, (size_t)(list->capacity * sizeof(Node)));

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

