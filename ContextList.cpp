/*
file name: Node.h
author: Hall, Ashley
date: 2019-Nov-23
description: The implementation file for the ContextList class. A ContextList is a singly linked list composed of ListNode objects containing each instance of a word's context in the corpus. The ContextList will contain all the contexts for each word in the corpus in the order of the occurrence of the word in the corpus. 
*/

#include "ContextList.h"


/** The default constructor for the ContextList class.
Constructs an empty ContextList object.
The head and tail pointers are initialized to nullptr.
 */
ContextList::ContextList() : head(nullptr), tail(nullptr)
{
}

/**The copy constructor for the ContextList class.
Makes a deep copy of the list supplied as the argument.
@param aList The list to be copied.
 */
ContextList::ContextList(const ContextList& aList)
{
   //make deep copies of the nodes and set to this-list's head pointer
   head = copyNodes(aList.head);
   
   //iterate through list until last node is found
   ListNode* curr = head;
   while (curr->getNext() != nullptr)
   {
      curr = curr->getNext();
   }
   //set last node to tail
   tail = curr;
}

/**Overloaded assignment operator for the ContextList class.
@pre Objects on the left and right side of the operator must be the same data type.
@post The list on the left side of the operator will contain a deep copy of the list on the right side.
@param rhs The list on the right side of the assignment operator.
*/
ContextList& ContextList::operator=(const ContextList& rhs)
{
   //compare addresses of left-hand and right-hand lists to ensure they aren't the same object
   if (this != &rhs)
   {
      //deallocate memory assigned to left-hand side list
      clear();
      
      //copy nodes from right-hand side to left list
      head = copyNodes(rhs.head);
      
      //find last node in list and set to tail
      ListNode* curr = head;
      while (curr->getNext() != nullptr)
      {
         curr = curr->getNext();
      }
      tail = curr;
   }
   
   //return copy of right-hand side list
   return *this;
}
  
/** The destructor for the ContextList class.
Destroys the ContextList object, freeing memory allocated for the nodes in the list when its lifetime ends.
 */
ContextList::~ContextList()
{
   clear();
}

/**Copies a chain of ListNode objects.
@pre origHead must be a pointer to a ListNode object or nullptr.
@post Returns the deep copy of a ListNode pointer to the first node in a chain of copied nodes.
@param origHead The pointer to the first node in the chain to be copied.
@return The  head pointer to the copied chain of nodes.
 */
ListNode* ContextList::copyNodes(const ListNode* origHead)
{
   //list is empty
   ListNode* copiedHead = nullptr;
   
   //list isn't empty
   if ( origHead != nullptr )
   {
      //create a new ListNode that is a copy of the original
      copiedHead = new ListNode(origHead->getContext(), origHead->getNext());
      
      //set the next node's in the copied list to the next node's in the original list
      copiedHead->setNext( copyNodes( origHead->getNext() ) );
   }
   
   //return the head pointer of the copied list
   return copiedHead;
}

/** Adds a new ListNode to the end of the ContextList object.
 @param context The context to be added to the ContextList.
 @pre context must be of type ListNode::contextArr.
 @post The new ListNode will be added to the end of the ContextList object. The tail pointer will point to the new node added.*/
void ContextList::add(const ListNode::contextArr& context)
{
   //allocate memory for a new ListNode containing the given context
   ListNode* newNode = new ListNode(context);
   
   //if list is empty, set head and tail to point to new ListNode
   if (head == nullptr)
   {
      head = newNode;
      tail = newNode;
   }
   //list is not empty
   else
   {
      //add ListNode to end of ContextList
      tail->setNext(newNode);
      //set tail to ListNode just added
      tail = newNode;
   }
}

/** Deletes all the nodes in the ContextList.
 @pre None.
 @post The ContextList will be empty, memory for the nodes has been deallocated. */
void ContextList::clear()
{
   //keep deleting nodes until list is empty
   while(head != nullptr)
   {
      //start deleting nodes from the beginning of the list
      ListNode* nodeToDelete = head;
      //set head to next node
      head = head->getNext();
      //deallocate memory for node
      delete nodeToDelete;
      //set pointer to nullptr
      nodeToDelete = nullptr;
   }
}

/**Prints each context in the list as a string to cout. Each context will be on one line forming three columns. The first column will contain the words before the keyword and will be right justified. The second column will contain the keyword and will be centered. The thrid column will contain the words after the keyword and will be left justified.
 @param preKeyLen The total length of the words before the keyword.
 @param keyLen The length of the keyword.
 @param postKeyLen The total length of the words after the keyword.
 @pre All arguments supplied must be of type int.
 @post The context for each ListNode in the ContextList will be displayed to cout. */
void ContextList::printFormatted(int preKeyLen, int keyLen, int postKeyLen) const
{
   ListNode* currNode = head;
   while (currNode != nullptr)
   {
      
      string keyWord = currNode->getKey();
      
      int preKeyColWidth = preKeyLen + 40;
      int keyColWidth = keyLen + 10;
      int postKeyColWidth = postKeyLen + 40;

      int currKeyLen = (int)keyWord.length();
      int padAfter = (keyColWidth - currKeyLen) / 2;
      int padBefore = keyColWidth - padAfter - currKeyLen;

      keyWord.append(padAfter, ' ');
      keyWord.insert(keyWord.begin(), padBefore, ' ');
      
      cout << setw(preKeyColWidth) << right << currNode->getPreKeyContext();
      cout << setw(keyColWidth) << keyWord;
      cout << setw(postKeyColWidth) << left << currNode->getPostKeyContext();
      
      currNode = currNode->getNext();
      cout << endl;
   }
}
