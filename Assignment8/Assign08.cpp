#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

void MakeAllLowerCase(char* word);

int main()
{
   HashTable hTab;
   cout << "capacity initially: " << hTab.cap() << endl;
   cout << "used initially:     " << hTab.size() << endl;
   char dictOption;
   cout << "select dictionary (s = small, others = big): ";
   cin >> dictOption;
   cin.ignore(9999, '\n');
   ifstream fin;
   if (dictOption == 's' || dictOption == 'S')
      fin.open("dict0.txt", ios::in);
   else
      fin.open("dict1.txt", ios::in);
   if ( fin.fail() )
   {
      cerr << "Failed to open dictionary file dict.txt..."
           << endl;
      exit(EXIT_FAILURE);
   }
   clock_t begLoad;   // for timing hashtable load
   clock_t endLoad;   // for timing hashtable load
   char oneWord[101]; // holder for word (up to 100 chars)
   cout << "loading dictionary . . ." << endl;
   begLoad = clock();
   fin >> ws;
   while ( ! fin.eof() )
   {
      fin >> oneWord;
      if ( ! hTab.exists(oneWord) ) hTab.insert(oneWord);
      fin >> ws;
   }
   fin.close();
   endLoad = clock() - begLoad;
   cout << "dictionary loaded in "
        << (double)endLoad / ((double)CLOCKS_PER_SEC)
        << " seconds . . ." << endl;
   cout << "capacity post-load: " << hTab.cap() << endl;
   cout << "used post-load:     " << hTab.size() << endl;
   cout << "load-factor:        " << hTab.load_factor() << endl;
   hTab.grading_helper_print(cout);
   hTab.scat_plot(cout);

   char response;
   do
   {
      cout << "Enter word to spell check (up to 100 characters long): ";
      cin >> oneWord;
      cin.ignore(9999, '\n'); // clear the cin buffer
      cout << endl;
      MakeAllLowerCase(oneWord);
      if ( hTab.search(oneWord) )
         cout << oneWord << " matches a word in dictionary ~ o ~" << endl;
      else
      {
         char altWord[101];
         bool suggLabPrinted = false;
         for(HashTable::size_type x = 0; x < strlen(oneWord); ++x)
         {
            strcpy(altWord, oneWord);
            for(char c = 'a'; c <= 'z'; ++c)
            {
               altWord[x] = c;
               if( hTab.search(altWord) )
               {
                  if( ! suggLabPrinted)
                  {
                     cout << oneWord << " not found in dictionary . . .\n"
                          << "   near match(es): ";
                     suggLabPrinted = true;
                  }
                  cout << altWord << "  ";
               }
               strcpy(altWord, oneWord);
            }
         }
         if(suggLabPrinted)
            cout << endl;
         else
            cout << oneWord << " not found in dictionary . . .\n"
                 << "   no near match(es) to suggest :-( \n";
      }
      cout << "\nMore word to spell check? (y/n): ";
      cin >> response;
      cin.ignore(9999, '\n'); // clear the cin buffer
   }
   while(response == 'y' || response == 'Y');

   cout << "******* bye *******\n";

   return EXIT_SUCCESS;
}

void MakeAllLowerCase(char* word)
{
   HashTable::size_type i = 0;
   while (word[i] != '\0')
   {
      word[i] = word[i] | 32;
      ++i;
   }
}
