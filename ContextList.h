/*
file name: Node.h
author: Hall, Ashley
date: 2019-Nov-23
description: The header file for the ContextList class. A ContextList is a singly linked list composed of ListNode objects containing each instance of a word's context in the corpus. The ContextList will contain all the contexts for each word in the corpus in the order of the occurrence of the word in the corpus. 
*/

#ifndef CONTEXTLIST_H
#define CONTEXTLIST_H

#include <iostream>
#include <iomanip>
#include "ListNode.h"

using namespace std;


class ContextList
{
public:
   
   /** The default constructor for the ContextList class.
   Constructs an empty ContextList object.
   The head and tail pointers are initialized to nullptr.
    */
   ContextList();
   
   /**The copy constructor for the ContextList class.
   Makes a deep copy of the list supplied as the argument.
   @param aList The list to be copied.
    */
   ContextList(const ContextList& aList);
   
   /**Overloaded assignment operator for the ContextList class.
   @pre Objects on the left and right side of the operator must be the same data type.
   @post The list on the left side of the operator will contain a deep copy of the list on the right side.
   @param rhs The list on the right side of the assignment operator.
   */
   ContextList& operator=(const ContextList& rhs);
   
   /** The destructor for the ContextList class.
   Destroys the ContextList object, freeing memory allocated for the nodes in the list when its lifetime ends.
    */
   virtual ~ContextList();
   
   /** Adds a new ListNode to the end of the ContextList object.
   @param context The context to be added to the ContextList.
   @pre context must be of type ListNode::contextArr.
   @post The new ListNode will be added to the end of the ContextList object. The tail pointer will point to the new node added.*/
   void add(const ListNode::contextArr& context);
   
   /** Deletes all the nodes in the ContextList.
   @pre None.
   @post The ContextList will be empty, memory for the nodes has been deallocated. */
   void clear();
   
   /**Prints each context in the list as a string to cout. Each context will be on one line forming three columns. The first column will contain the words before the keyword and will be right justified. The second column will contain the keyword and will be centered. The thrid column will contain the words after the keyword and will be left justified.
   @param preKeyLen The total length of the words before the keyword.
   @param keyLen The length of the keyword.
   @param postKeyLen The total length of the words after the keyword.
   @pre All arguments supplied must be of type int.
   @post The context for each ListNode in the ContextList will be displayed to cout. */
   void printFormatted(int preKeyLen,int keyLen, int postKeyLen) const;
  
private:
   /**Copies a chain of ListNode objects.
   @pre origHead must be a pointer to a ListNode object or nullptr.
   @post Returns the deep copy of a ListNode pointer to the first node in a chain of copied nodes.
   @param origHead The pointer to the first node in the chain to be copied.
   @return The  head pointer to the copied chain of nodes.
    */
   ListNode* copyNodes(const ListNode* origHead);
   
   ListNode* head; //pointer to first ListNode
   ListNode* tail; //pointer to last ListNode

   
};
#endif
