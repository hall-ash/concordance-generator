/*
file name: main.cpp
author: Hall, Ashley
date: 2019-Nov-23
Problem Statement:
 Description:
 A Keyword-in-Context (KWIC) concordance is a list of keywords in body of text surrounded by its context, the series of words in which each keyword is embedded. In KWIC the concordance is displayed in a tabular form consisting of three columns. The first, second, and third columns show the context preceding the keyword, the keyword, and the context succeeding the keyword, respectively. Rows in the concordance display each instance of the keyword in context and are sorted first by alphabetizing the keywords then by the order of each keyword’s appearance in the corpus. The set of keywords of a corpus may contain all the words in the text or it may exclude certain predetermined stop words such as “a”, “the”, etc.
 Purpose:
 The program will generate a concordance from a corpus by reading from the command line a text file containing the corpus. From the file, the program will create a binary search tree of key, value pairs to collect the concordance information. Each word in the corpus, with the exclusion of stop words, will serve as a key. The context of each key will serve as the value. For this program, the context will have a length no greater than ten words (the series of 0-5 words that immediately precede the key and the series of 0-5 words that immediately succeed the key). The binary search tree will be indexed by each word (excluding stop words) in the corpus, and each tree node will contain a singly linked list holding the context information for each instance of its key’s appearance in the corpus. If available, a list of stop words will be read from a text file in the same directory in which the program is located. If no stop text file exists, the program will exclude no words from the concordance. The program will output the concordance in the KWIC format described above to cout.
 Input Data:
 The program will read a text file containing the corpus as its sole command line argument. It is assumed the program will read the corpus file from the current directory.
 Stop words may be read from a file titled “stopwords.txt” located in the same directory as the program. This file will contain one stop word per line. If no stop word file exists, the concordance generated by the program will include all words from the corpus. No stop word file will be included in the program.
 Words in the input stream will be defined using the following definitions:
 words are bounded by white space, if not the first or last word in the file
 the first word will start at the beginning of the input and end at the first white space
 the last word will start after white space and end when eof() is true
 punctuation characters will not be considered words
 words are not case-sensitive (e.g., “key” and “Key” will be considered the same word)
 In addition, words will be cleaned of leading and trailing punctuation.
 Output Data:
 The concordance will be output in a KWIC format to cout. Each row in the concordance will display an instance of each keyword surrounded by its context. Rows will be sorted first by alphabetizing the keywords then by the order of each keyword’s appearance in the corpus. Keywords in each row will be formatted such that they will be aligned vertically in a column.
 Error Handling:
 The program will report an error message if no corpus file is supplied as a command line argument, the corpus file does not exist, or the corpus file could not be opened.
 Implementation Plan:
 The program consists of the BinarySearchTree class representing a binary search tree composed of nodes from the BSTNode class. The context for each key word in the corpus will be represented by a singly linked list, the ContextList class, which is composed of ListNodes. Each ListNode contains an array, 11 elements in length, of strings (indices 0-4 will contain the 5 context words before the key, index 5 will contain the key, indices 6-10 will contain the 5 context words after the key) and a pointer to the next ListNode. Each BSTNode object holds a string, representing a key word in the corpus, a ContextList object, representing all the contexts in which the key word is found, and pointers to the left and right children in the tree. As the corpus is traversed, new key words and their context will be added as a BSTNode in the binary search tree. When a duplicate key is found, the context list will be updated by adding a new ListNode object to the ContextList in the BSTNode that contains the matching key. The concordance will be displayed using an in order traversal that prints each string array in the ContextList for each BSTNode. 

*/
#include <iostream>
#include <fstream>
#include "BinarySearchTree.h"

using namespace std;

//abbreviate class name
typedef BinarySearchTree bst;

int main(int argc, const char * argv[])
{
   //2 args needed: program name and filename
   if ( argc != 2 )
   {
      cerr << "Missing command line argument for corpus file." << endl;
      exit ( EXIT_FAILURE );
   }
   else
   {
      //number of words that have been read from the corpus text
      int wordCount = 0;
      
      //name of the stopword file
      const string STOP_WORD_FILE = "stopwords.txt";
      
      //the concordance to add words and their contexts to
      bst concordance;
      
      //array of context words, including keyword at index 5
      ListNode::contextArr theContext;
      
      //the word to read from the corpus file
      string word;
         
      //if stopwords.txt is found, exclude stop words from concordance
      concordance.excludeStopWords(STOP_WORD_FILE);
      
      //open the corpus file entered as second command line argument
      ifstream fileReader( argv[1] );

      //if fileReader has not successfully opened the file
      if ( !fileReader.is_open() )
      {
         cerr << "Corpus file could not be opened." << endl;
         exit( EXIT_FAILURE );
      }
      
      while ( !fileReader.eof() )
      {
         //read each string in the file
         if  ( fileReader >> word)
         {
            //checks if word is a lone punctuation symbol
            if ( bst::isPunct(word) )
               continue;
            else
            {
               //fill the context array at index = (wordCount + 5) with the current word
               bst::fillContextArray( word, theContext, wordCount );
               
               //increment wordCount until 6 words have been added to context array
               if ( wordCount < 6 )
               {
                  wordCount++;
               }
            }
         }
         
         //once context array has been filled with 6 words
         if ( wordCount >= 6 )
         {
            //word at index 5 will be the key
            string key = (theContext.at(5));
            
            //add key and current context array to binary search tree
            concordance.add( key, theContext );
            
            //shift words 1 to left so new word can be added at last array index
            bst::shiftArray(theContext);
         }
      }
      
      fileReader.close();
         
      //get last 5 words or first 1-5 words in corpus if words in text file <= 5
      for (string key = (theContext.at(5)); key != ""; bst::shiftArray(theContext), key = (theContext.at(5)))
      {
         concordance.add( key, theContext );
      }
      
      
      if ( concordance.isEmpty() )
         cout << "No words found in corpus file!" << endl;
      else
         concordance.printConcordance();
         
   }
   
   return 0;

}


