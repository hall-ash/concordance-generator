/*
file name: Node.h
author: Hall, Ashley
date: 2019-Nov-23
description: The implementation file for the ListNode class. Each ListNode contains the context, the 5 words before, the word itself, and the 5 words after the keyword, for a word in the corpus.
*/

#include "ListNode.h"

/** Constructor for the ListNode class that accepts a context array as its argument. Initializes the context to the context array given and its next pointer to nullptr.
 @param theContext the context array
 @pre theContext must be of type ListNode::contextArr
 */
ListNode::ListNode(const contextArr& theContext) : context(theContext), next(nullptr)
{
}

/** Constructor for the ListNode class that accepts a context array and a next node pointer as arguments. Initializes the context to the context array given and its next pointer to the pointer given.
@param theContext the context array
@param nextNode the pointer to the next node
@pre theContext and nextNode must be of type ListNode::contextArr and ListNode, respectively.
*/
ListNode::ListNode(const contextArr& theContext, ListNode* nextNode) :
   context(theContext), next(nextNode)
{
}

/**Sets the data member next to the ListNode pointer given.
@param nextNode The pointer that points to the next node.
@pre: The argument must a pointer to a ListNode.
@post next will store the memory address of the ListNode pointed to by nextNode.
 */
void ListNode::setNext(ListNode* nextNode)
{
   next = nextNode;
}

/**Returns the context of a ListNode
 @pre: none
 @post The context will be returned as a reference to a contextArr object. */
const ListNode::contextArr& ListNode::getContext() const
{
   return context;
}

/**Returns the next ListNode.
@pre: none
@post: The pointer to the next node will be returned.
@return The pointer to the next node. */
ListNode* ListNode::getNext() const
{
   return next;
}

/**Returns the context words before the keyword as a string of words separated by a space.
 @return Returns the context words before the keyword as a string.
 @pre none
 @post If there are no context words before the keyword an empty string will be returned. Otherwise, a string containing each context word before the keyword separated by a space will be returned.
 */
string ListNode::getPreKeyContext() const
{
   string preKey = "";
   //traverse the context array, stop before keyword (index = 5)
   for (int i = 0; i < 5; i++)
   {
      //don't add space if at end of array
      if ( i == 4 )
         preKey = preKey + context.at(i);
      //add context word with space in between
      else
         preKey = preKey + context.at(i) + " ";
   }
   return preKey;
}

/**Returns the context words after the keyword as a string of words separated by a space.
@return Returns the context words after the keyword as a string.
@pre none
@post If there are no context words after the keyword an empty string will be returned. Otherwise, a string containing each context word after the keyword separated by a space will be returned.
*/
string ListNode::getPostKeyContext() const
{
   string postKey = "";
   //traverse the context array after the keyword (index = 5)
   for (int i = 6; i < 11; i++)
   {
      if ( i == 10 )
         //don't add space if at end of array
         postKey = postKey + context.at(i);
      else
         //add context word with space in between
         postKey = postKey + context.at(i) + " ";
   }
   return postKey;
}

/**Returns the keyword as a string.
 @return Returns the keyword as a string.
 @pre none
 @post The keyword will be returned as a string.
 */
string ListNode::getKey() const
{
   return context.at(5);
}
