#include <string.h>
#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>

typedef struct AdptArray_{    // building a structor of AdptArray
    PElement* pElement;
    int sizeArr;
    COPY_FUNC copyFun;
    DEL_FUNC deleteFun;
    PRINT_FUNC printFun;

} AdptArray, *PAdptArray;

// A function that initializes an empty array with no elements
 PAdptArray CreateAdptArray(COPY_FUNC copyFun, DEL_FUNC deleteFun, PRINT_FUNC printFun) {
    PAdptArray arrP = (PAdptArray) malloc(sizeof(struct AdptArray_));  // we create an array but without define size
    if (arrP == NULL){   // if the creation are faild.
        return NULL;
    }
    arrP->pElement = NULL;     // defualt defination
    arrP->sizeArr = 0;
    arrP->copyFun = copyFun;
    arrP->deleteFun = deleteFun;
    arrP->printFun = printFun;

    return arrP;
}

// The function frees the memory of the array and all its elements
void DeleteAdptArray(PAdptArray arrP){
    if(arrP == NULL || arrP->pElement == NULL)    // if the array or the elements are null we are not continue.
        return;
    for(int i = 0; i < arrP->sizeArr; i++){
        if(arrP->pElement[i] != NULL){        // we move element one by one and if he exist we delete the element.
            arrP->deleteFun(arrP->pElement[i]);
        }
    }
    free(arrP->pElement);    // we release the array's element
    free(arrP);           // then release the array is self.
}

// The function receives an index and an element and saves a copy of the element at this location.  
// The function frees the old member if one exists
Result SetAdptArray(PAdptArray arrP, int index, PElement element){
    if(arrP == NULL || index < 0) {  // First we will check if something is wrong
        return FAIL;
    }
    if(index >= arrP->sizeArr) {
        PElement newArrP =(PElement*)calloc((index + 1), sizeof(PElement)); // create new extended array
        if(newArrP == NULL)
            return FAIL;
        memcpy(newArrP, arrP->pElement, (arrP->sizeArr) * sizeof(PElement));  // a copy function to new array
        free(arrP->pElement);
        arrP->pElement = newArrP;
        arrP->sizeArr = index+1;
        // for(int i = 0; i < arrP->sizeArr; i++) {
        //     newArrP[i] = arrP->pElement[i];
        // }
    }
    arrP->pElement[index] = arrP->copyFun(element);
    if(arrP->pElement[index] != NULL)
        arrP->deleteFun(arrP->pElement[index]);
    
        // free(arrP->pElement);
        // free(arrP);
    arrP->pElement[index]=element;
    return SUCCESS;
    
    // arrP->pElement[index] = element;
    // return SUCCESS;
 }

// The function accepts an index and returns a copy of the member at that location if it exists
PElement GetAdptArrayAt(PAdptArray arrP, int index){
 if(arrP == NULL || index >= arrP->sizeArr || index < 0 ) // First we will check if something is wrong
    return NULL;
 
 if(arrP->pElement[index] == NULL)   // if there is not element in this index we return nothing-null.
    return NULL;

 return arrP->copyFun(arrP->pElement[index]);  // we use the exist copy function to return a COPY of this elemnt. 
 }

// The function returns the size of the array (or -1 if it was not initialized successfully)
int GetAdptArraySize(PAdptArray arrP){
    if(arrP == NULL || arrP->pElement == NULL) 
      return -1;
    
    return arrP->sizeArr;

}

// The function prints the elements of the array
void PrintDB(PAdptArray arrP){
    if(arrP == NULL)
        return;
    for (int i = 0; i < arrP->sizeArr; i++)
    {
        if(arrP->pElement[i] != NULL){          // if the element in this place is not null we'll print it
            arrP->printFun(arrP->pElement[i]);
      }
    
    }
}
