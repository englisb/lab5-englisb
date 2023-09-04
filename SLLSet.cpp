/*
 * SLLSet.cpp
 *
 *  Created on: Nov. 17, 2021
 *      Author: moham
 */


#include "SLLSet.h"
#include <iostream>

SLLSet::SLLSet()
{
	size = 0;
	head = NULL;


}
SLLSet::SLLSet(int sortedArray[], int arrSize)
{
	int i;
	SLLNode *currentNode = head = new SLLNode();
	size = arrSize;

	for (i = 0 ; i < arrSize ; i++){
		currentNode->value = sortedArray[i];
		if(i == arrSize - 1){
			break;
		}
		currentNode->next = new SLLNode();
		currentNode = currentNode->next;
	}
	
	currentNode = NULL;

}
int SLLSet::getSize()
{
	return size;
}
SLLSet SLLSet::copy()
{
	SLLSet* copySet = new SLLSet();

	if(this->head == NULL){
		return *copySet;
	}
	else{
		int i;
		SLLNode* thisCurrentNode = head;
		SLLNode* copyCurrentNode = copySet->head = new SLLNode();

		for (i = 0 ; i < size - 1; i++){
			copyCurrentNode = copyCurrentNode->next = new SLLNode();
		}

		copyCurrentNode = copySet->head;

		for(i = 0; i < size; i++){
			copyCurrentNode->value = thisCurrentNode->value;
			thisCurrentNode = thisCurrentNode->next;
			copyCurrentNode = copyCurrentNode->next;
		}

		copySet->size = size;

	}
	
	return *copySet;
}
bool SLLSet::isIn(int v)
{
	SLLNode* current = head;

	for(int i = 0; i < size; i++){
		if(v == current->value){				//watch for bugs near the end of the set, might be checking the value of NULL
			return true;
		}
		current = current->next;
	}

	return false;
}
void SLLSet::add(int v)
{
	if(this->head == NULL){
		SLLNode* newNode = new SLLNode(v, NULL);
		head = newNode;
		size++;
		return;
	}

	SLLNode* currentNode = head;

	for(int i = 0; i < size; i++){
		if(v == currentNode->value){
			return;
		}
		currentNode = currentNode->next;
	}

    SLLNode* newNode = new SLLNode();
    newNode->value = v;
    currentNode = head;
    size++;

    while(currentNode->next != NULL){
    	if(v < head->value){
    		newNode->next = head;
    		head = newNode;
    		return;
    	}
    	else if(v > currentNode->value && v < currentNode->next->value){
    	    newNode->next = currentNode->next;
    	    currentNode->next = newNode;
    	    return;
    	}
    	else{
    		currentNode = currentNode->next;
    	}
    }

    currentNode->next = newNode;



    /*stuff below is if list is empty
    if(current == NULL){
    	this->head = newNode;
    }
    else{
    	while(current->next != NULL){
    		current = current->next;
    	}
    }
    */
    
}
void SLLSet::remove(int v)
{
	SLLNode* current = head;
	SLLNode* temp;

	if(v == current->value){
		temp = current->next;
		delete head;
		head = temp;
		size--;
		return;
	}

	for(int i = 0; i < size - 1; i++){
		if(v == current->next->value){
			temp = current->next->next;
			delete current->next;
			current->next = temp;
			size--;
			return;
		}

		current = current->next;
	}


}
SLLSet SLLSet::setUnion(SLLSet s)
{
	SLLSet newSet = s.copy();

	if(newSet.head == NULL){
		return *this;
	}

    int i;
    SLLNode* current = head;

    for(i = 0; i < size; i++){
   		if(!(newSet.isIn(current->value))){
   			newSet.add(current->value);
       	}

   		current = current->next;
    }

    return newSet;
}

SLLSet SLLSet::intersection(SLLSet s)
{

	 int i;

	 SLLNode* current = head;
	 SLLSet newSet;


	 for(i = 0; i < size; i++){
		 if(s.isIn(current->value)){
			 newSet.add(current->value);
		 }
	   	current = current->next;
	 }

	 return newSet;
}
SLLSet SLLSet::difference(SLLSet s)
{
	if(s.head == NULL){
		return *this;
	}

	int i;
	SLLSet newSet = this->copy();
	 SLLNode* current = s.head;


	 for(i = 0; i < s.size; i++){
		 if(newSet.isIn(current->value)){
			 newSet.remove(current->value);
		 }
		 current = current->next;
	 }

	return newSet;
}

SLLSet SLLSet::setUnion(SLLSet sArray[],int size)
{

	int i;

    SLLSet newSet = sArray->copy();
    SLLNode* currentNode;


    for(i = 1; i < size; i++){
    	currentNode = sArray[i].head;
    	while(currentNode != NULL){
    		if(!(newSet.isIn(currentNode->value))){
   				newSet.add(currentNode->value);
   			}

   			currentNode = currentNode->next;
    	}
   	}

	return newSet;
}
string SLLSet::toString()
{
	int i;
   string output = "";
   SLLNode* currentNode = head;

   for(i = 0; i < size; i++){
	   if(i == size - 1){
		   output += to_string(currentNode->value);
	   }
	   else{
		   output += to_string(currentNode->value) + ", ";
	   }
	   currentNode = currentNode->next;
   }

   currentNode = NULL;

   output += "\0";

   return output;
}

