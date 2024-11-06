#ifndef LISTS_H_
#define LISTS_H_

#include <stdio.h>

static const int kMinNumOfElems =     8;
static const int kMultiplier =        2;
static const int kDivForReallocDown = 4;

typedef void   void_sex;
typedef size_t elem_t;
typedef size_t index_t;


typedef struct Node {
    elem_t  value;

    index_t next;
    index_t prev;
} Node;



typedef enum VerificationStatus  {
    VERIFICATION_PASSED = 0,
    VERIFICATION_FAILED = 1
} VerificationStatus ;

typedef enum Status {
    SUCCESS = 0,
    FAILURE = 1
} Status;

typedef enum IsEmpty {
    kEmpty =    0x00,
    kNotEmpty = 0x01,
    kFull =     0xFF
} IsEmpty;

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
    ListError_kWrongIndex =            0x10
} ListError;

typedef struct ListStruct {
    size_t             capacity;

    Node*              data;

    index_t            FreeList;
    ListError          error;

    VerificationStatus verif;
} ListStruct;

//---------------------------------- PUBLIC ------------------------------------
// NOTE главное 5 функций: ctor, dtor, вставка в начало, вставка в конец, вставка после какого то элеменнта, аналогичные функции для удаленя
VerificationStatus Verificator(ListStruct* list);
void_sex           DotDump(ListStruct* list);

Status             ListCtor(ListStruct* list); //с
Status             ListDtor(ListStruct* list); //с

Status             ListPush(ListStruct* list, const elem_t elem); //лол ладно я хз зачем сделала их это угарно
Status             ListPop(ListStruct* list);

Status             InsertFront(ListStruct* list, const elem_t elem);
Status             InsertBack(ListStruct* list, const elem_t elem);
Status             InsertNextInd(ListStruct* list, const elem_t elem, index_t ind_of_given_elem);
Status             InsertNextVal(ListStruct* list, const elem_t inserted_elem, const elem_t value);
Status             InsertPrevInd(ListStruct* list, const elem_t elem, index_t ind_of_given_elem);
Status             InsertPrevVal(ListStruct* list, const elem_t inserted_elem, const elem_t value);

Status             Erase(ListStruct* list, const elem_t elem);

index_t            FindVal(ListStruct* list, const elem_t elem);
elem_t             FindIndex(ListStruct* list, index_t ind_of_given_elem);


#endif //LISTS_H_