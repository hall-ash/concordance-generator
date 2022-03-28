/*
file name: Node.h
author: Hall, Ashley
date: 2019-Nov-23
description: The header file for the BinarySearchTree class. The BinarySearchTree class represents a concordance. The tree is composed of TreeNodes representing each word and its list of contexts in the corpus and is indexed alphabetically by the words in the corpus. 
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <vector>
#include <fstream>
#include <iostream>
#include "TreeNode.h"

class BinarySearchTree
{
   
public:
   
   /** The default constructor for the BinarySearchTree class.
   Constructs an empty BinarySearchTree object.
   The root is initialized to nullptr, maxPreKeyLen, maxKeyLen, maxPostKeyLen are initialized to 0, and stopWords is initialized to false. */
   BinarySearchTree();
  
   /**The copy constructor for the BinarySearchTree class.
   Makes a deep copy of the binary search tree supplied as the argument.
   @param tree The tree to be copied. */
   BinarySearchTree(const BinarySearchTree& tree);
   
   /** The destructor for the BinarySearchTree class.
   Destroys the BinarySearchTree object, freeing the memory allocated for the TreeNodes in the tree when its lifetime ends.*/
   virtual ~BinarySearchTree();
   
   /** Tests whether binary tree is empty.
   @return True if the binary tree is empty, false otherwise.
   @pre none
   @post Returns true if the binary tree is empty, false otherwise.*/
   bool isEmpty() const;
   
   /**Adds a new TreeNode containing the keyword and the context, or updates the context list with the new context if the TreeNode containing the keyword already exists.
   @param keyWord A keyword from the corpus.
   @param newContext New context to be added.
   @return True if the new TreeNode could be added to the binary search tree or the TreeNode containing the keyword already exists and the context list was updated. False otherwise
   @pre The keyword must be of type string and the context to be added must be of type ListNode::contextArr.
   @post If the addition was successful, a new TreeNode containing the keyword and the context given will be added to the tree. Or if a TreeNode containing the keyword already exists the context list will be updated with the new context. If the new context contains the longest pre-key context, post-key context, and/or keyword, the maximum lengths for these values will be updated.*/
   bool add(string& keyWord, const ListNode::contextArr& newContext);

   void clear();
   
   /** Overloaded assignment operator for the BinarySearchTree class.
   @pre Objects on the left and right side of the operator must BinarySearchTree objects.
   @post The tree on the left side of the operator will be a deep copy of the tree on the right.
   @param rhs The tree on the right side of the assignment operator. */
   BinarySearchTree& operator=(const BinarySearchTree& rhs);
   
   /** Performs a recursive inorder traversal of the binary search tree and prints a formatted context list after visiting each node. Public method.
    @pre None.
   @post The context list for each node in the binary search tree will be printed to cout in alphabetical order based on the key in each TreeNode. If the tree is empty, nothing will be printed to cout.*/
   void printConcordance() const;
   
   /**Builds a vector containing the stop words.
   @param stopWordFile The name of the file containing the stop words.
   @return True if the file exists, could be opened, and the vector was filled with at least one string. False if the file does not exist, could not be opened, or the file contained not strings.
   @pre The stopword file must be located in the same directory as the executable. The argument must be of type string.
   @post If the stopword file exists and could be read, the stopWordVector will be filled with the stop words in the file. If the file does not contain strings, the vector will remain empty and false will be returned. If the file does not exist or could not be opened, the vector will remain empty and false will be returned.
   */
   bool buildStopWordVector(const string& stopWordFile);
   
   /** Updates the maximum lengths of the pre-key context length, the key length, and the post-key context length.
   @param context The array of context words.
   @pre The context must be of type ListNode::contextArr
   @post If any of the lengths in the given array are greater than the current maximum lengths, the maximum length(s) will be updated with the appropriate length(s) in the given array. If no lengths in the array are greater, the maximum lengths will remain the same.
    */
   void setMaxLengths(const ListNode::contextArr& context);
   
   /**Sets the boolean value stopWords and fills the stopword vector with stopwords.
   @param stopWordFile The file to read the stop words from.
   @return True if the file exists, was read from, and populated the stopword vector with at least 1 string. False otherwise.
   @pre The stopWordFile must be of type string.
   @post If a stopword file exists, could be read from, and contains at least 1 string. The size of the stopword vector will be greater than 0, the vector will be filled with the string(s) in the stop word file, the boolean value stopWords will be set to true, and true will be returned. If the file does not exist, could not be read from, or does not contain at least 1 string, the stopword vector will have size 0, stopWords will be set to false, and false will be returned. */
   bool excludeStopWords(const string& stopWordFile);
   
   /** Checks if the given word is a word in the stopword vector.
   @param word The word to be checked.
   @return True if the word is a stopword, false otherwise.
   @pre The word must be of type string.
   @post True will be returned if the word found in the stopword vector, otherwise false will be returned.
   */
   bool isStopWord(string& word);
   
   /**Checks if a lone character in the corpus is a punctuation symbol.
   @param word The word to be checked.
   @return True will be returned if the word is a punctuation symbol. False otherwise.
   @pre The word must be of type string.
   @post True will be returned if the word is a punctuation symbol. False otherwise.
   */
   bool static isPunct(string& word);
   
   /**Fills the context array with words from the corpus starting at index 5.
   @param word The word to be inserted into the array.
   @param arr The context array to insert the word into.
   @param wordCount The number of words that have been iterated through in the corpus text.
   @pre The arguments for the word, array, and index must be of type  string, ListNode::contextArr, and int, respectively.
   @post The context array will be filled with the word given starting at index 5-9 when wordCount is 0-4. When wordCount is >=5 the array will be filled at index 10 with the given word.
   */
   void static fillContextArray(string& word, ListNode::contextArr& arr, int& wordCount);
   
   /**Shifts words in the context array 1 index to the left. After shifting, the element at array index 10 will contain an empty string.
   @param arr The context array.
   @pre The array must be of type ListNode::contextArr.
   @post Words in indices 1-10 will be shifted 1 index to the left. The element at index 10 will be an empty string.
    */
   void static shiftArray(ListNode::contextArr& arr);
   
   /**Strips a word of punctuation and makes it lowercase.
   @param word The word to be reformatted.
   @pre The word must be of type string.
   @post The word will be stripped of punctuation and be lowercase.
   */
   void static removePunctAndLower(string& word);
   
   
private:
   TreeNode* root; //pointer to root node
   int maxPreKeyLen; //length of longest string of context words before keyword in the tree
   int maxKeyLen; //length of longest keyword in the tree
   int maxPostKeyLen; //length of longest string of context words after keyword in the tree
   bool stopWords; //true if excluding stopwords
   vector<string> stopWordVector; //vector to contain the stopwords
   
   /**Inserts a new TreeNode into the binary tree into the appropriate location based on the given keyword.
   @param treePtr The TreeNode pointer pointing to the root node of the tree.
   @param keyWord A keyword from the corpus.
   @param context New context to be added.
   @return Returns the root pointer to the binary search tree after the TreeNode has been added to the appropriate location.
   @pre The keyword must be of type string and the context to be added must be of type ListNode::contextArr.
   @post A new TreeNode containing the keyword will be added to the tree in the appropriate location based on the keyword, and a new ContextList object will be created for the given context. Or if a TreeNode containing the keyword already exists the new context will be added to the end of the context list stored in the TreeNode. After insertion, the pointer to the root node of the tree will be returned.*/
   TreeNode* insert(TreeNode* treePtr, const string& keyWord, const ListNode::contextArr& context);
   
   /** Creates a deep copy for each node in a binary search tree using a recursive preorder traversal.
   @param origTreePtr The TreeNode pointer to the root of the original tree.
   @return The TreeNode pointer to the root of the copied tree.
   @pre origTreePtr must be a pointer to a TreeNode
   @post All nodes in the original tree will be deep copied and the pointer to the root node of the copied tree will be returned.*/
   TreeNode* copyTree(const TreeNode* origTreePtr) const;
   
   /** Deletes each node in the tree using a recursive postorder traversal.
   @param treePtr The pointer to the root of the tree or subtree.
   @pre treePtr must be a pointer to a TreeNode object.
   @post Each node in the tree or subtree will be deleted. */
   void destroyTree(TreeNode* treePtr);
   
   /** Performs a recursive inorder traversal of the binary search tree and prints a formatted context list after visiting each node. Private method.
   @param treePtr The TreeNode pointer pointing to the root node of the tree or subtree.
   @pre treePtr must be a pointer to a TreeNode object.
   @post The context list for each node in the binary search tree will be printed to cout in alphabetical order based on the key in each TreeNode. If the tree is empty, nothing will be printed to cout.*/
   void inorder(TreeNode* treePtr) const;
   
};

#endif
