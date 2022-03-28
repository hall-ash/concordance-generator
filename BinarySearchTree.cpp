/*
file name: Node.h
author: Hall, Ashley
date: 2019-Nov-23
description: The implementation file for the BinarySearchTree class. The BinarySearchTree class represents a concordance. The tree is composed of TreeNodes representing each word and its list of contexts in the corpus and is indexed alphabetically by the words in the corpus. 
*/

#include "BinarySearchTree.h"

using namespace std;

/** The default constructor for the BinarySearchTree class.
Constructs an empty BinarySearchTree object.
The root is initialized to nullptr, maxPreKeyLen, maxKeyLen, maxPostKeyLen are initialized to 0, and stopWords is initialized to false. */
BinarySearchTree::BinarySearchTree() : root(nullptr), maxPreKeyLen(0), maxKeyLen(0), maxPostKeyLen(0), stopWords(false)
{
}

/**The copy constructor for the BinarySearchTree class.
Makes a deep copy of the binary search tree supplied as the argument.
@param tree The tree to be copied. */
BinarySearchTree::BinarySearchTree(const BinarySearchTree& tree)
{
   //calls private method on root pointer of tree to deep copy all nodes
   root = copyTree(tree.root);
   //set other data members
   maxPreKeyLen = tree.maxPreKeyLen;
   maxKeyLen = tree.maxKeyLen;
   maxPostKeyLen = tree.maxPostKeyLen;
   stopWords = tree.stopWords;
   stopWordVector = tree.stopWordVector;
}

/** The destructor for the BinarySearchTree class.
Destroys the BinarySearchTree object, freeing the memory allocated for the TreeNodes in the tree when its lifetime ends.*/
BinarySearchTree::~BinarySearchTree()
{
   //calls private method on root pointer to recursively delete nodes
   destroyTree(root);
}

/** Overloaded assignment operator for the BinarySearchTree class.
 @pre Objects on the left and right side of the operator must BinarySearchTree objects.
 @post The tree on the left side of the operator will be a deep copy of the tree on the right.
 @param rhs The tree on the right side of the assignment operator. */
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs)
{
   //make sure objects aren't the same by comparing addresses
   if ( this != &rhs )
   {
      //deallocate memory assigned to left hand tree
      destroyTree(root);
      
      //copy nodes from right hand tree to left hand tree
      root = copyTree(rhs.root);
      
      //copy the rest of the data members
      maxPreKeyLen = rhs.maxPreKeyLen;
      maxKeyLen = rhs.maxKeyLen;
      maxPostKeyLen = rhs.maxPostKeyLen;
      stopWords = rhs.stopWords;
      stopWordVector = rhs.stopWordVector;
   }
   
   //return copy of the right hand side tree
   return *this;
}

/** Creates a deep copy for each node in a binary search tree using a recursive preorder traversal.
 @param origTreePtr The TreeNode pointer to the root of the original tree.
 @return The TreeNode pointer to the root of the copied tree.
 @pre origTreePtr must be a pointer to a TreeNode
 @post All nodes in the original tree will be deep copied and the pointer to the root node of the copied tree will be returned.*/
TreeNode* BinarySearchTree::copyTree(const TreeNode* origTreePtr) const
{
   //original tree is empty, return nullptr
   TreeNode* copiedTreePtr = nullptr;
   if ( origTreePtr != nullptr )
   {
      //create a copy of the parent node in the original tree
      copiedTreePtr = new TreeNode(origTreePtr->getKey(), origTreePtr->getContextList());
      //recursively traverse the left subtree
      copiedTreePtr->setLeftChild(copyTree(origTreePtr->getLeftChild()));
      //recursively traverse the right subtree
      copiedTreePtr->setRightChild(copyTree(origTreePtr->getRightChild()));
   }
   //return the copied tree root node pointer
   return copiedTreePtr;
}

/** Deletes each node in the tree using a recursive postorder traversal.
 @param treePtr The pointer to the root of the tree or subtree.
 @pre treePtr must be a pointer to a TreeNode object.
 @post Each node in the tree or subtree will be deleted. */
void BinarySearchTree::destroyTree(TreeNode* treePtr)
{
   //tree contains nodes to be deleted
   if ( treePtr != nullptr )
   {
      //recursively traverse and delete nodes the left subtree
      destroyTree(treePtr->getLeftChild());
      //recursively traverse and delete nodes the right subtree
      destroyTree(treePtr->getRightChild());
      //delete the parent node
      delete treePtr;
      //set pointer to nullptr
      treePtr = nullptr;
   }
}

/**Sets the boolean value stopWords and fills the stopword vector with stopwords.
 @param stopWordFile The file to read the stop words from.
 @return True if the file exists, was read from, and populated the stopword vector with at least 1 string. False otherwise.
 @pre The stopWordFile must be of type string.
 @post If a stopword file exists, could be read from, and contains at least 1 string. The size of the stopword vector will be greater than 0, the vector will be filled with the string(s) in the stop word file, the boolean value stopWords will be set to true, and true will be returned. If the file does not exist, could not be read from, or does not contain at least 1 string, the stopword vector will have size 0, stopWords will be set to false, and false will be returned. */
bool BinarySearchTree::excludeStopWords(const string& stopWordFile)
{
   //if stopwords file doesn't exist, couldn't be read from, or does not
   //contain strings, set boolean value stopWords to false
   stopWords = buildStopWordVector(stopWordFile);
   return stopWords;
}

/**Adds a new TreeNode containing the keyword and the context, or updates the context list with the new context if the TreeNode containing the keyword already exists.
 @param keyWord A keyword from the corpus.
 @param newContext New context to be added.
 @return True if the new TreeNode could be added to the binary search tree or the TreeNode containing the keyword already exists and the context list was updated. False otherwise
 @pre The keyword must be of type string and the context to be added must be of type ListNode::contextArr.
 @post If the addition was successful, a new TreeNode containing the keyword and the context given will be added to the tree. Or if a TreeNode containing the keyword already exists the context list will be updated with the new context. If the new context contains the longest pre-key context, post-key context, and/or keyword, the maximum lengths for these values will be updated.*/
bool BinarySearchTree::add(string& keyWord, const ListNode::contextArr& newContext)
{
   //before adding keyword to tree, strip it of punctuation and make lowercase
   removePunctAndLower(keyWord);
   
   //if no stop words are excluded, insert TreeNode into binary tree
   if ( !stopWords )
      root = insert(root, keyWord, newContext);
   
   //stop words are excluded so check if keyword is a stop word
   //if not a stopward, insert TreeNode into binary tree
   else if ( stopWords && !isStopWord(keyWord) )
      root = insert(root, keyWord, newContext);
   
   //updates max lengths for the pre-key context, key, and post-key context
   setMaxLengths(newContext);
   
   //TreeNode was successfully added or updated with new context
   return true;
}

/**Inserts a new TreeNode into the binary tree into the appropriate location based on the given keyword.
@param treePtr The TreeNode pointer pointing to the root node of the tree.
@param keyWord A keyword from the corpus.
@param context New context to be added.
@return Returns the root pointer to the binary search tree after the TreeNode has been added to the appropriate location.
@pre The keyword must be of type string and the context to be added must be of type ListNode::contextArr.
@post A new TreeNode containing the keyword will be added to the tree in the appropriate location based on the keyword, and a new ContextList object will be created for the given context. Or if a TreeNode containing the keyword already exists the new context will be added to the end of the context list stored in the TreeNode. After insertion, the pointer to the root node of the tree will be returned.*/
TreeNode* BinarySearchTree::insert(TreeNode* treePtr, const string& keyWord, const ListNode::contextArr& context)
{
   //tree is empty or subtree has no children
   if ( treePtr == nullptr )
   {
      //create a new context list and add the given context
      ContextList newList;
      newList.add(context);
      
      //create a new TreeNode with the given keyword and new context list created
      TreeNode* newNodePtr = new TreeNode(keyWord, newList, nullptr, nullptr);
      
      //set treePtr to the new node created
      treePtr = newNodePtr;
      
      //return the TreeNode's pointer
      return treePtr;
   }
   //keyword to be inserted is less than current TreeNode's keyword
   else if ( keyWord < treePtr->getKey() )
   {
      //insert new TreeNode into left subtree
      treePtr->setLeftChild( insert(treePtr->getLeftChild(), keyWord, context) );
   }
   //a TreeNode containing the keyword is already in the tree
   else if (keyWord == treePtr->getKey() )
   {
      //add the new context array to the context list
      treePtr->updateContextList(context);
   }
   //keyWord to be inserted is greater than current TreeNode's keyWord
   //insert into the right subtree
   else
      treePtr->setRightChild( insert(treePtr->getRightChild(), keyWord, context) );
   return treePtr;
   
}

/** Performs a recursive inorder traversal of the binary search tree and prints a formatted context list after visiting each node. Private method.
@param treePtr The TreeNode pointer pointing to the root node of the tree or subtree.
@pre treePtr must be a pointer to a TreeNode object.
@post The context list for each node in the binary search tree will be printed to cout in alphabetical order based on the key in each TreeNode. If the tree is empty, nothing will be printed to cout.*/
void BinarySearchTree::inorder(TreeNode* treePtr) const
{
   //if tree is not empty
   if ( treePtr != nullptr )
   {
      //recursively traverse the left subtree
      inorder(treePtr->getLeftChild());
      
      //print the context list of the tree's root
      ( treePtr->getContextList() ).printFormatted(maxPreKeyLen, maxKeyLen, maxPostKeyLen);
      
      //recursively traverse the right subtree
      inorder(treePtr->getRightChild());
   }
}

/** Performs a recursive inorder traversal of the binary search tree and prints a formatted context list after visiting each node. Public method.
 @pre None.
@post The context list for each node in the binary search tree will be printed to cout in alphabetical order based on the key in each TreeNode. If the tree is empty, nothing will be printed to cout.*/
void BinarySearchTree::printConcordance() const
{
   inorder(root);
}


/** Tests whether binary tree is empty.
@return True if the binary tree is empty, false otherwise.
@pre none
@post Returns true if the binary tree is empty, false otherwise.*/
bool BinarySearchTree::isEmpty() const
{
   return root == nullptr;
}

/** Updates the maximum lengths of the pre-key context length, the key length, and the post-key context length.
@param context The array of context words.
@pre The context must be of type ListNode::contextArr
@post If any of the lengths in the given array are greater than the current maximum lengths, the maximum length(s) will be updated with the appropriate length(s) in the given array. If no lengths in the array are greater, the maximum lengths will remain the same.
 */
void BinarySearchTree::setMaxLengths(const ListNode::contextArr& context)
{
   int preKeyLen = 0;
   int keyLen = (int)context.at(5).length();
   int postKeyLen = 0;
   
   //pre-key context words are in index 0-4
   //finds total length of all pre-key context words in given array
   for (int i = 0; i < 5; i++)
      preKeyLen += (int)context.at(i).length();
   
   //post-key context words are in index 6-10
   //finds the total length of all post-key context words in the given array
   for (int i = 6; i < 11; i++)
      postKeyLen += (int)(context.at(i).length());
   
   //if any of the lengths in the given array are greater than the current max lengths
   //update max lengths
   maxPreKeyLen = preKeyLen > maxPreKeyLen ? preKeyLen : maxPreKeyLen;
   maxKeyLen = keyLen > maxKeyLen ? keyLen : maxKeyLen;
   maxPostKeyLen = postKeyLen > maxPostKeyLen ? postKeyLen : maxPostKeyLen;
   
}

/**Builds a vector containing the stop words.
 @param stopWordFile The name of the file containing the stop words.
 @return True if the file exists, could be opened, and the vector was filled with at least one string. False if the file does not exist, could not be opened, or the file contained not strings.
 @pre The stopword file must be located in the same directory as the executable. The argument must be of type string.
 @post If the stopword file exists and could be read, the stopWordVector will be filled with the stop words in the file. If the file does not contain strings, the vector will remain empty and false will be returned. If the file does not exist or could not be opened, the vector will remain empty and false will be returned.
 */
bool BinarySearchTree::buildStopWordVector(const string& stopWordFile)
{
   ifstream fileReader(stopWordFile);
   
   //cannot open file
   if ( !fileReader.is_open() )
   {
      return false;
   }
   //the stopword to be read from the file
   string stopWord;
   
   //continue reading until end of file
   while ( !fileReader.eof() )
   {
      //read each stopword in the file
      if ( fileReader >> stopWord )
      {
         //strip stopword of punctuation and make lowercase
         removePunctAndLower(stopWord);
         
         //add stopword to vector
         stopWordVector.push_back(stopWord);
      }
   }
   
   //the vector is empty, no strings in the stopword file
   if ( stopWordVector.size() == 0 )
      return false;
   else
      return true;
}

/**Strips a word of punctuation and makes it lowercase.
 @param word The word to be reformatted.
 @pre The word must be of type string.
 @post The word will be stripped of punctuation and be lowercase.
 */
void BinarySearchTree::removePunctAndLower(string& word)
{
   int length = (int)word.length();
   //iterate through the word
   for ( int i = 0; i < length; i++ )
   {
      //if a character in the word is a punctuation symbol
      if ( ispunct(word[i]) )
         //erase punct from the word, decrement i
         word.erase(i--, 1);
   }
   //set the word to lowercase
   transform(word.begin(), word.end(), word.begin(), ::tolower);
}

/**Shifts words in the context array 1 index to the left. After shifting, the element at array index 10 will contain an empty string.
@param arr The context array.
@pre The array must be of type ListNode::contextArr.
@post Words in indices 1-10 will be shifted 1 index to the left. The element at index 10 will be an empty string.
 */
void BinarySearchTree::shiftArray(ListNode::contextArr& arr)
{
   //iterate through the context array
   for (int i = 1; i < 11; i++)
      //shift elements 1 to the left
      arr.at(i - 1) = arr.at(i);
   //set element at index 10 to an empty string
   arr.at(10) = "";
}

/**Fills the context array with words from the corpus starting at index 5.
 @param word The word to be inserted into the array.
 @param arr The context array to insert the word into.
 @param wordCount The number of words that have been iterated through in the corpus text.
 @pre The arguments for the word, array, and index must be of type  string, ListNode::contextArr, and int, respectively.
 @post The context array will be filled with the word given starting at index 5-9 when wordCount is 0-4. When wordCount is >=5 the array will be filled at index 10 with the given word.
 */
void BinarySearchTree::fillContextArray(string& word, ListNode::contextArr& arr, int& wordCount)
{
   //do not allow negative integers for wordCount
   if ( wordCount < 0)
      return;
   //for the first 5 words
   else if (wordCount < 5 )
   {
      //start filling at indices 5-9
      arr.at( wordCount + 5 ) = word;
   }
   //for subsequent words, fill only index 10
   else
      arr.at(10) = word;
}

/**Checks if a lone character in the corpus is a punctuation symbol.
 @param word The word to be checked.
 @return True will be returned if the word is a punctuation symbol. False otherwise.
 @pre The word must be of type string.
 @post True will be returned if the word is a punctuation symbol. False otherwise.
 */
bool BinarySearchTree::isPunct(string& word)
{
   return (word.length() == 1 && ispunct(word[0]));
}


/** Checks if the given word is a word in the stopword vector.
 @param word The word to be checked.
 @return True if the word is a stopword, false otherwise.
 @pre The word must be of type string.
 @post True will be returned if the word found in the stopword vector, otherwise false will be returned.
 */
bool BinarySearchTree::isStopWord(string& word)
{
   //initialize iterators to the start and end of the stopword vector
   vector<string>::iterator itr = stopWordVector.begin();
   vector<string>::iterator end = stopWordVector.end();
   
   bool isStop = false;
   
   //iterate through vector
   while ( itr != end )
   {
      //if word given equals a word in the vector, set
      //isStop to true
      if ( word == *(itr++) )
         isStop = true;
   }
   return isStop;
}
