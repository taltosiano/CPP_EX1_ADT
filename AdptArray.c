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
            arrP->pElement[i] = NULL;
        }
    }
    free(arrP->pElement);    // free the array's data
    free(arrP);           // then free the array.
}

// The function receives an index and an element and saves a copy of the element at this location.  
// The function frees the old member if one exists
Result SetAdptArrayAt(PAdptArray arrP, int index, PElement element){
   if(arrP == NULL || index < 0) {  // First we will check if something is wrong
        return FAIL;
    }

    if(index >= arrP->sizeArr) {     // if the index bigger then the array size we should extend the array
        PElement* newArrP =(PElement*)calloc((index + 1), sizeof(PElement)); // create new extended array
        if(newArrP == NULL)
            return FAIL;

        memcpy(newArrP, arrP->pElement, (arrP->sizeArr) * sizeof(PElement));  // a copy function to new array
        free(arrP->pElement);     // realse the previous array
        arrP->pElement = newArrP;
        arrP->sizeArr = index+1;       // update the array size to be bigger
    }

    if(arrP->pElement[index] != NULL)    
        arrP->deleteFun(arrP->pElement[index]);   // delete the old element
   
    arrP->pElement[index] = arrP->copyFun(element);   // insert in the index location a copy of the new element
    return SUCCESS;
    
 }
 
// The function accepts an index and returns a copy of the member at that location if it exists
PElement GetAdptArrayAt(PAdptArray arrP, int index){
 if(arrP == NULL || index >= arrP->sizeArr || index < 0 ) // First we will check if something is wrong
    return NULL;
 
 if(arrP->pElement[index] == NULL)   // if there is not element in this index we return nothing-null.
    return NULL;

 return arrP->copyFun(arrP->pElement[index]);  // we use the copy function to return a COPY of this elemnt. 
 }

// The function returns the size of the array (or -1 if it was not initialized successfully)
int GetAdptArraySize(PAdptArray arrP){
    if(arrP == NULL || arrP->pElement == NULL)  // check if the pointer is null or the array elements
      return -1;
    
    return arrP->sizeArr;     // just return the array size

}

// The function prints the elements of the array
void PrintDB(PAdptArray arrP){
    if(arrP == NULL)    // if the pointer is null the func stop
        return;
    for (int i = 0; i < arrP->sizeArr; i++)
    {
        if(arrP->pElement[i] != NULL){          // only if the element in this place is not null we'll print it
            arrP->printFun(arrP->pElement[i]);
      }
    
    }
}

