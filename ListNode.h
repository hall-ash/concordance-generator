/*
file name: Node.h
author: Hall, Ashley
date: 2019-Nov-23
description: The header file for the ListNode class. Each ListNode contains the context, the 5 words before, the word itself, and the 5 words after the keyword, for a word in the corpus. 
*/

#ifndef LISTNODE_H
#define LISTNODE_H

#include <string>
#include <array>

using namespace std;

class ListNode
{
   
   
public:
   static const int NUM_WORDS = 11; //10 context words + 1 keyword
   
   typedef array<string, NUM_WORDS> contextArr; //create alias type
   
   /** Constructor for the ListNode class that accepts a context array as its argument. Initializes the context to the context array given and its next pointer to nullptr.
   @param theContext the context array
   @pre theContext must be of type ListNode::contextArr
   */
   ListNode(const contextArr& theContext);
   
   /** Constructor for the ListNode class that accepts a context array and a next node pointer as arguments. Initializes the context to the context array given and its next pointer to the pointer given.
   @param theContext the context array
   @param nextNode the pointer to the next node
   @pre theContext and nextNode must be of type ListNode::contextArr and ListNode, respectively.
   */
   ListNode(const contextArr& theContext, ListNode* nextNode);
   
   /**Sets the data member next to the ListNode pointer given.
   @param nextNode The pointer that points to the next node.
   @pre: The argument must a pointer to a ListNode.
   @post next will store the memory address of the ListNode pointed to by nextNode.
    */
   void setNext(ListNode* nextNode);
   
   /**Returns the next ListNode.
   @pre: none
   @post: The pointer to the next node will be returned.
   @return The pointer to the next node. */
   ListNode* getNext() const;
 
   /**Returns the context of a ListNode
   @pre: none
   @post The context will be returned as a reference to a contextArr object. */
   const contextArr& getContext() const;
   
   /**Returns the context words before the keyword as a string of words separated by a space.
   @return Returns the context words before the keyword as a string.
   @pre none
   @post If there are no context words before the keyword an empty string will be returned. Otherwise, a string containing each context word before the keyword separated by a space will be returned.
   */
   string getPreKeyContext() const;
   
   /**Returns the context words after the keyword as a string of words separated by a space.
   @return Returns the context words after the keyword as a string.
   @pre none
   @post If there are no context words after the keyword an empty string will be returned. Otherwise, a string containing each context word after the keyword separated by a space will be returned.
   */
   string getPostKeyContext() const;
   
   /**Returns the keyword as a string.
   @return Returns the keyword as a string.
   @pre none
   @post The keyword will be returned as a string.
   */
   string getKey() const;
   
private:
   contextArr context; //the context for a word in the corpus
   
   ListNode* next; //pointer to next ListNode

};

#endif
