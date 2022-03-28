/*
file name: Node.h
author: Hall, Ashley
date: 2019-Nov-23
description: The implementation file for the TreeNode class. Each TreeNode contains a word in the corpus and its list of contexts. The TreeNodes will serve as nodes in the BinarySearchTree class.
*/

#ifndef TREENODE_H
#define TREENODE_H

#include "ContextList.h"

class TreeNode
{
public:
   
   /**The default constructor for the TreeNode class.
   Initializes the leftChildPtr and rightChildPtr to nullptr.*/
   TreeNode();
   
   /**Constructor for the TreeNode class that accepts arguments for the keyWord and contextList.
   Initializes the keyWord and contextList to the given arguments. Initializes the leftChildPtr and rightChildPtr to nullptr.
   @param key A keyword in the corpus.
   @param list A list of contexts for the keyword.
   @pre key and list must be of type string and ContextList, respectively.
   */
   TreeNode(const string& key, const ContextList& list);
   
   /**Constructor for the TreeNode class that accepts arguments for the keyWord, contextList, leftChildPtr, and rightChildPtr.
   Initializes the keyWord, contextList, leftChildPtr, and rightChildPtr to the given arguments.
   @param key A keyword in the corpus.
   @param list A list of contexts for the keyword.
   @param leftChild A TreeNode pointer to the left chlld.
   @param rightChild A TreeNode pointer to the right child.
   @pre key and list must be of type string and ContextList, respectively. leftChild and rightChild must be pointers to TreeNodes
   */
   TreeNode(const string& key, const ContextList& list, TreeNode* leftChild, TreeNode* rightChild);
   
   /**Sets the keyWord for the TreeNode to the given string.
   @param key The string to set the keyWord to.
   @pre key must be of type string.
   @post The keyWord will be set to the given string.
   */
   void setKey(const string& key);
   
   /**Sets the ContextList for the TreeNode to the given list.
   @param list The list to set the ContextList to.
   @pre list must be of type ContextList.
   @post The ContextList will be set to the given list.
   */
   void setContextList(const ContextList& list);
   
   /**Sets the left child for the TreeNode to the given TreeNode pointer.
   @param leftChild The TreeNode pointer to set the left child to.
   @pre leftChild must be a pointer to a TreeNode.
   @post The left child will be set to the given TreeNode pointer.
   */
   void setLeftChild(TreeNode* leftChild);
   
   /**Sets the right child for the TreeNode to the given TreeNode pointer.
   @param rightChild The TreeNode pointer to set the left child to.
   @pre rightChild must be a pointer to a TreeNode.
   @post The right child will be set to the given TreeNode pointer.
   */
   void setRightChild(TreeNode* rightChild);
   
   /**Returns the keyWord of the TreeNode.
   @return Returns the keyWord.
   @pre none
   @post The keyWord will be returned as a string. */
   const string& getKey() const;
   
   /**Returns the keyWord of the TreeNode.
   @return Returns the keyWord.
   @pre none
   @post The keyWord will be returned as a string. */
   const ContextList& getContextList() const;
   
   /**Returns the pointer to the left child of the TreeNode.
   @return Returns the left child TreeNode pointer.
   @pre none
   @post The TreeNode pointer to the left child will be returned. */
   TreeNode* getLeftChild() const;
   
   /**Returns the pointer to the right child of the TreeNode.
   @return Returns the right child TreeNode pointer.
   @pre none
   @post The TreeNode pointer to the right child will be returned. */
   TreeNode* getRightChild() const;
   
   /**Adds a new context array to the context list stored in the TreeNode.
   @param context The context array to be added.
   @pre context must be of type ListNode::contextArr
   @post The context will be added to the end of the context list in the TreeNode. */
   void updateContextList(const ListNode::contextArr& context);
   
private:
   string keyWord; //word from corpus
   ContextList contextList; //list of contexts for word
   TreeNode* leftChildPtr; //pointer to left child TreeNode
   TreeNode* rightChildPtr; //pointer to right child TreeNode
};
#endif 
