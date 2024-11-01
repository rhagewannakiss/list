#include "lists.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <memory.h>
#include <math.h>

static IsEmpty_t IsEmpty(ListStruct* list);
static Status    ReallocUp(ListStruct* list);
static Status    ReallocDown(ListStruct* list);
static Status    ListPush(ListStruct* list, const elem_t elem);
static Status    ListPop(ListStruct* list, const elem_t elem);


//---------------------------------- PUBLIC ------------------------------------
//=============================== VERIFICATION =================================
VerificationStatus_t Verificator(ListStruct* list) { //еще будет дописываться
    assert(list != nullptr);

    return VERIFICATION_PASSED;
}

//=================================== DUMP =====================================
void_sex DotDump(ListStruct* list) {
    assert(list != nullptr);

}

//=============================== GET FRONT PTR ================================
index_t GetFrontPtr(ListStruct* list) { // чо за хуйня вс это должно возвращать индекс если это и так первый элемент че
    assert(list != nullptr);
    index_t searched_index = 0;

    if (IsEmpty(list) == kEmpty) {
        list->error = ListError_kFrontIndexOnEmptyList;
        list->verif = VERIFICATION_FAILED;
        return -666;
    }

    list->verif = VERIFICATION_PASSED;
    return searched_index;
}

//================================ GET BACK PTR ================================
index_t GetBackPtr(ListStruct* list) {
    assert(list != nullptr);

    if (IsEmpty(list) == kEmpty) {
        list->error = ListError_kBackIndexOnEmptyList;
        return -666;
    }
}

//================================ GET NEXT PTR ================================
index_t GetNextPtr(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    index_t index_of_next_elem = 0;

    if (IsEmpty(list) == kEmpty) {
        list->error = ListError_kNextIndexOnEmptyList;
        return -666;
    }

    if (IsEmpty(list) == kFull) {
        if (ReallocUp(list) == FAILURE) {
            list->error = ListError_kMemoryAllocationError;
            return -666;
        };
    }



    return index_of_next_elem;
}

//================================ GET PREV PTR ================================
// получения указателя на элемент, предшествующий данному
index_t GetPrevPtr(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    if (IsEmpty(list) == kEmpty) {
        list->error = ListError_kPrevIndexOnEmptyList;
        return -666;
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
// удаления заданного элемента
void_sex Erase(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    list->error = ListError_kOk;
}

//=================================== FIND =====================================
// поиска элемента по его значению
index_t Find(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    index_t searched_index = 0;

    list->error = ListError_kOk;
    return searched_index;
}

//================================ FIND INDEX ==================================
// поиска элемента по его номеру в последовательности (операция индексации)
elem_t FindIndex(ListStruct* list, index_t ind_of_given_elem) {
    assert(list != nullptr);
}

//=================================== CTOR =====================================
Status ListCtor(ListStruct* list) {
    if (list == nullptr) {
        return FAILURE;
    }

    list->capacity = kMinNumOfElems;
    list->data = (node_t*)calloc(list->capacity, sizeof(node_t));

    list->FreeList = list->data->next;

    list->head =  0;
    list->tail =  0;

    list->error = ListError_kOk;
    list->verif = VERIFICATION_PASSED;

    return SUCCESS;
}

//=================================== DTOR =====================================
Status ListDtor(ListStruct* list) {
    if (list == nullptr) {
        list->error = ListError_kMemoryAllocationError;
        return FAILURE;
    }

    list->capacity = 0;

    free(list->data);
    list->data = nullptr;

    list->error = ListError_kOk;
    list->verif = VERIFICATION_PASSED;

    return SUCCESS;
}

//---------------------------------- STATIC ------------------------------------

//================================= IS EMPTY ===================================
static IsEmpty_t IsEmpty(ListStruct* list) { //возможно и не нужно если работаем со списком содержащим фантомный элемент
    assert(list != nullptr);

    if ((list->head - list->tail) == 1) {
        return kEmpty;
    }
    else if ((list->tail - list->head) == 1) {
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
    list->data = (node_t*)realloc(list->data, (size_t)(list->capacity * sizeof(node_t)));

    if (list->data == nullptr) {
        list->error = ListError_kMemoryAllocationError;
        //тут не нужно ли тогда free()-шить?
        return FAILURE;
    }

    return SUCCESS;
}

//================================ REALLOC DOWN =================================
static Status ReallocDown(ListStruct* list) {
    assert(list != nullptr);

    return SUCCESS;
}
//================================= LIST PUSH ===================================
static Status ListPush(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    if (list->head >= list->capacity) {
        if (ReallocUp(list) == FAILURE) {
            return FAILURE;
        }
    }

    list->data[list->head].value = elem;
    list->data[list->head].next = list->head + 1;
    list->data[list->head].prev = list->head - 1;
    list->head++;

    // написать для circular

    return SUCCESS;
}

//================================== LIST POP ===================================
static Status ListPop(ListStruct* list, const elem_t elem) {
    assert(list != nullptr);

    if (IsEmpty(list) == kEmpty) {
        list->error = ListError_kEraseOnEmptyList;
        return FAILURE;
    }

    list->head--;

    if (list->head < list->capacity / kDivForReallocDown
     && list->capacity > kMinNumOfElems) {
        if (ReallocDown(list) == FAILURE) {
            list->error = ListError_kReallocationfailed;
            return FAILURE;
        }
    }

    return SUCCESS;
}
