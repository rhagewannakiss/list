#ifndef LISTS_H_
#define LISTS_H_

#include <stdio.h>

static const int kMinNumOfElems =     8;
static const int kMultiplier =        2;
static const int kDivForReallocDown = 4;

typedef void    void_sex;
typedef int     elem_t;
typedef int     index_t;

// typedef struct node_t {
//     elem_t  value;

//     node_t* next;
//     node_t* prev;
// } node_t;

typedef struct node_t {
    elem_t  value;

    index_t next;
    index_t prev;
} node_t;


typedef enum VerificationStatus_t {
    VERIFICATION_PASSED = 0,
    VERIFICATION_FAILED = 1
} VerificationStatus_t;

typedef enum Status {
    SUCCESS = 0,
    FAILURE = 1
} Status;

typedef enum IsEmpty_t {
    kEmpty =    0x00,
    kNotEmpty = 0x01,
    kFull =     0xFF
} IsEmpty_t;

typedef enum ListError {
    ListError_kOk =                    0x00,

    ListError_kMemoryAllocationError = 0x01,
    ListError_kEraseOnEmptyList =      0x02,
    ListError_kReallocationfailed =    0x03,
    ListError_kHeadOutOfList =         0x04,
    ListError_kTailOutOfList =         0x05,
    ListError_kFrontIndexOnEmptyList = 0x06,
    ListError_kBackIndexOnEmptyList =  0x07,
    ListError_kNextIndexOnEmptyList =  0x08,
    ListError_kPrevIndexOnEmptyList =  0x09,
} ListError;


typedef struct ListStruct {
    int                  capacity;

    node_t*              data;

    int                  head;
    int                  tail;

    index_t              FreeList;

    ListError            error;

    VerificationStatus_t verif;
} ListStruct;


//---------------------------------- PUBLIC ------------------------------------
VerificationStatus_t Verificator(ListStruct* list);
void_sex             DotDump(ListStruct* list);

Status               ListCtor(ListStruct* list);
Status               ListDtor(ListStruct* list);

index_t              GetFrontPtr(ListStruct* list);
index_t              GetBackPtr(ListStruct* list);
index_t              GetNextPtr(ListStruct* list, const elem_t elem);
index_t              GetPrevPtr(ListStruct* list, const elem_t elem);

Status               InsertFront(ListStruct* list, const elem_t elem);
Status               InsertBack(ListStruct* list, const elem_t elem);
Status               InsertNext(ListStruct* list, const elem_t elem, index_t ind_of_given_elem);
Status               InsertPrev(ListStruct* list, const elem_t elem, index_t ind_of_given_elem);

void_sex             Erase(ListStruct* list, const elem_t elem);

index_t              Find(ListStruct* list, const elem_t elem);
elem_t               FindIndex(ListStruct* list, index_t ind_of_given_elem);


#endif //LISTS_H_