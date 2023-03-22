#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"


typedef struct AdptArray_
{
    PElement *PElement;
    int ArrSize;

    COPY_FUNC CopyElementFunc;
    DEL_FUNC DelElementFunc;
    PRINT_FUNC PrintElementFunc;
} AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC CopyElementFunc, DEL_FUNC DelElementFunc, PRINT_FUNC PrintElementFunc){

    PAdptArray pAA = (PAdptArray)malloc(sizeof(AdptArray));
    if (!pAA){
        return NULL;
    }

    pAA->ArrSize = 0;
    pAA->PElement = NULL;
    pAA->CopyElementFunc = CopyElementFunc;
    pAA->DelElementFunc = DelElementFunc;
    pAA->PrintElementFunc = PrintElementFunc;
    
    return pAA;
}


void DeleteAdptArray(PAdptArray pAA){

    if (!pAA){
        return;
    }

    for (int i = 0; i < pAA->ArrSize; ++i){
        if (pAA->PElement[i] != NULL){
            pAA->DelElementFunc(pAA->PElement[i]);
        }
    }

    free(pAA->PElement);
    free(pAA);
}


Result SetAdptArrayAt(PAdptArray pAA, int x, PElement pElem){

    PElement* ElemAA;

    if (!pAA){
        return FAIL;
    }

    //Extand Array
    if (pAA->ArrSize <= x){
        if(!(ElemAA = (PElement*)calloc((x+1), sizeof(PElement)))){
            return FAIL;
        }

        if(pAA->PElement != NULL){
            for(int i = 0; i < pAA->ArrSize; ++i){
                if(pAA->PElement[i] != NULL){
                    ElemAA[i] = pAA->CopyElementFunc(pAA->PElement[i]);
                    pAA->DelElementFunc(pAA->PElement[i]);
                }
            }
        }

        free(pAA->PElement);
        pAA->PElement = ElemAA;
    }

    //Delete Previous Element
    if(pAA->PElement[x] != NULL){
        pAA->DelElementFunc(pAA->PElement[x]);
    }

    pAA->PElement[x] = pAA->CopyElementFunc(pElem);
    pAA->ArrSize = (pAA->ArrSize <= x) ? (x+1) : pAA->ArrSize;

    return SUCCESS;

}


PElement GetAdptArrayAt(PAdptArray pAA, int x){

    if (!pAA){
        return NULL;
    }

    if(x<0 || x>= pAA->ArrSize){
        return NULL;
    }

    if(pAA->PElement[x] != NULL){
        return pAA->CopyElementFunc(pAA->PElement[x]);
    }

    return NULL;

}


int GetAdptArraySize(PAdptArray pAA){

    if (!pAA){
        return -1;
    }

    return pAA->ArrSize;

}


void PrintDB(PAdptArray pAA){

    if(!pAA){
        return;
    }

    printf("The AdptArray contains the following:\n");
    for (int i = 0; i < pAA->ArrSize; i++){
        if (pAA->PElement[i] != NULL){
            pAA->PrintElementFunc(pAA->PElement[i]);
        }
    }
}