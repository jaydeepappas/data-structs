#include "btNode.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void SeedRand();
int BoundedRandomInt(int lowerBound, int upperBound);
bool contains(const int array[], int used, int key);
void InsertSortedNonDec(int array[], int& used, int newValue) ;
bool match(const int a1[], const int a2[], int size);
void ShowArray(const int a[], int size);
bool remOne(int dataOriSorted[], int& used, int remInt);

int main()
{
   int testCasesToDo = 990000,
       testCasesDone = 0,
       loOriSize = 1,
       hiOriSize = 30,
       oriSize,
       loRemTriesToDo = 1,
       hiRemTriesToDo,
       remTriesToDo,
       loValue = -9,
       hiValue = 9;
   int oriCount,
       sampCount,
       remTriesDone,
       remCountArr,
       remCountBST,
       used,
       numNodes,
       newInt,
       remInt;
   int *dataOriSorted = 0,
       *dumpOri = 0,
       *dumpPostRem = 0,
       *dataRemRandom = 0,
       *dataRemSorted = 0;
   btNode* bst_root = 0;

   // SeedRand(); // disabled for reproducible result

   do
   {
      ++testCasesDone;
      oriSize = BoundedRandomInt(loOriSize, hiOriSize);
      hiRemTriesToDo = oriSize;
      remTriesToDo = BoundedRandomInt(loRemTriesToDo, hiRemTriesToDo);
      dataOriSorted = new int [oriSize];
      dumpOri = new int [oriSize];
      dataRemRandom = new int [remTriesToDo];
      dataRemSorted = new int [remTriesToDo];

      oriCount = 0;
      sampCount = 0;
      while (sampCount < oriSize)
      {
         newInt = BoundedRandomInt(loValue, hiValue);
         if ( ! contains(dataOriSorted, oriCount, newInt) )
            InsertSortedNonDec(dataOriSorted, oriCount, newInt);
            // NOTE: oriCount incremented by InsertSortedNonDec
         bst_insert(bst_root, newInt);
         ++sampCount;
      }
      numNodes = bst_size(bst_root);
      if (numNodes != oriCount)
      {
         cout << "Insert error ... bad post-insertion node count" << endl;
         cout << "expected: " << oriCount << endl;
         cout << "got this: " << numNodes << endl;
         exit(EXIT_FAILURE);
      }
      dumpToArrayInOrder(bst_root, dumpOri);
      if (! match(dataOriSorted, dumpOri, oriCount) )
      {
         cout << "Insert error ... bad in-order traversal output" << endl;
         cout << "expected: ";
         ShowArray(dataOriSorted, oriSize);
         cout << "got this: ";
         ShowArray(dumpOri, oriSize);
         exit(EXIT_FAILURE);
      }

      remTriesDone = 0;
      remCountArr = 0;
      remCountBST = 0;
      used = oriCount;
      while (remTriesDone < remTriesToDo)
      {
         remInt = BoundedRandomInt(loValue, hiValue);
         dataRemRandom[remTriesDone] = remInt;
         InsertSortedNonDec(dataRemSorted, remTriesDone, remInt);
         // NOTE: remTriesDone incremented by InsertSortedNonDec
         if ( remOne(dataOriSorted, used, remInt) )
            ++remCountArr;
         if ( bst_remove(bst_root, remInt) )
            ++remCountBST;
      }
      numNodes = bst_size(bst_root);
      if (remCountArr != remCountBST || numNodes != used)
      {
         cout << "Remove error ... post-removal count checks failed" << endl;
         cout << "expected: " << remCountArr << " removed, "
              << used << " remained" << endl;
         cout << "got this: " << remCountBST << " removed, "
              << numNodes << " remained" << endl;
         cout << "was attempting to remove " << remTriesToDo
              << " values below:" << endl;
         cout << "   (sequential order) ";
         ShowArray(dataRemRandom, remTriesToDo);
         cout << "   (value-sort order) ";
         ShowArray(dataRemSorted, remTriesToDo);
         cout << "from " << oriSize
              << " values below:" << endl;
         cout << "   ";
         ShowArray(dumpOri, oriSize);
         exit(EXIT_FAILURE);
      }
      else
      {
         dumpPostRem = new int [used];
         dumpToArrayInOrder(bst_root, dumpPostRem);
         if (! match(dataOriSorted, dumpPostRem, used) )
         {
            cout << "Remove error ... bad in-order traversal output" << endl;
            cout << "expected: ";
            ShowArray(dataOriSorted, used);
            cout << "got this: ";
            ShowArray(dumpPostRem, used);
            exit(EXIT_FAILURE);
         }
      }

      if (testCasesDone <= 5 || testCasesDone % 66000 == 0)
      {
         clog << "testing case " << testCasesDone
              << " of " << testCasesToDo << endl;
         cout << "==============================" << endl;
         cout << "test case " << testCasesDone
              << " of " << testCasesToDo << endl;
         cout << "attempt to remove " << remTriesToDo
              << " values below:" << endl;
         cout << "   (sequential order) ";
         ShowArray(dataRemRandom, remTriesToDo);
         cout << "   (value-sort order) ";
         ShowArray(dataRemSorted, remTriesToDo);
         cout << "from " << oriCount
              << " values below:" << endl;
         cout << "   ";
         ShowArray(dumpOri, oriCount);
         cout << "gives (with " << remCountBST
              << " values successfully removed)" << endl;
         cout << "   ";
         ShowArray(dumpPostRem, used);
      }

      tree_clear(bst_root);
      delete [] dataOriSorted;
      delete [] dumpOri;
      delete [] dataRemRandom;
      delete [] dumpPostRem;
      dataOriSorted = dumpOri = dataRemRandom = dumpPostRem = 0;
   }
   while (testCasesDone < testCasesToDo);
   cout << "==============================" << endl;
   cout << "test program terminated normally" << endl;
   cout << "==============================" << endl;

   return EXIT_SUCCESS;
}

// Function to seed the random number generator
// PRE:  none
// POST: The random number generator has been seeded.
void SeedRand()
{
   srand( (unsigned) time(NULL) );
}

// Function to generate a random integer between
// lowerBound and upperBound (inclusive)
// PRE:  lowerBound is a positive integer.
//       upperBound is a positive integer.
//       upperBound is larger than lowerBound
//       The random number generator has been seeded.
// POST: A random integer between lowerBound and upperBound
//       has been returned.
int BoundedRandomInt(int lowerBound, int upperBound)
{
   return ( rand() % (upperBound - lowerBound + 1) ) + lowerBound;
}

// Pre:  (1) used >= 0
//       (2) array's existing values (from array[0] through array[used - 1])
//           are in non-decreasing order
// Post: True is returned if there is a key-matching item in the array,
//       otherwise false is returned
bool contains(const int array[], int used, int key)
{
   for (int i = 0; i < used; ++i)
      if (array[i] == key) return true;
      else if (array[i] > key) return false;
   return false;
}

// Pre:  (1) used >= 0
//       (2) "size of array" > used
//       (3) array's existing values (from array[0] through array[used - 1])
//           are in non-decreasing order
// Post: (1) used has been incremented by 1
//       (2) newValue has been inserted into array, keeping all its values
//           (from array[0] through array[used - 1]) in non-decreasing order
void InsertSortedNonDec(int array[], int& used, int newValue)
{
   int probeIndex = used;
   while (probeIndex > 0 && array[probeIndex - 1] > newValue)
   {
      array[probeIndex] = array[probeIndex - 1];
      --probeIndex;
   }
   array[probeIndex] = newValue;
   ++used;
}

bool match(const int a1[], const int a2[], int size)
{
   for (int i = 0; i < size; ++i)
      if (a1[i] != a2[i]) return false;
   return true;
}

void ShowArray(const int a[], int size)
{
   for (int i = 0; i < size; ++i)
      cout << a[i] << ' ';
   cout << endl;
}

bool remOne(int dataOriSorted[], int& used, int remInt)
{
   for (int i = 0; i < used; ++i)
      if (dataOriSorted[i] == remInt)
      {
         int j = i + 1;
         while (j < used)
            dataOriSorted[i++] = dataOriSorted[j++];
         --used;
         return true;
      }
      else if (dataOriSorted[i] > remInt)
         break;
   return false;
}
