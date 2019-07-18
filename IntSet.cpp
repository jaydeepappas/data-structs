// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     compile-time array whose size is IntSet::MAX_SIZE;
//     the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[IntSet::MAX_SIZE - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

IntSet::IntSet() //complete
{
    used = 0;
}

int IntSet::size() const //complete
{
   return used;
}

bool IntSet::isEmpty() const //complete
{
    bool check = false;
    if (used == 0){
        check = true; //no elements in array
    }
   return check;
}

bool IntSet::contains(int anInt) const //complete
{
    bool check = false;
    for (int i = 0; i < used; i++){
        if (data[i] == anInt){
            check = true;
        }
    }
    
    return check;
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const //complete
{
    if (used == 0){
        return true;
    }
    
    bool myBool = true;
    if (used == otherIntSet.size()){
        for (int i = 0; i < used; i++){
            if (!contains(otherIntSet.data[i])){
                myBool = false;
                break;
            }
        }
    }
    return myBool;
}

void IntSet::DumpData(ostream& out) const //complete
{  // already implemented ... DON'T change anything
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const //complete
{
    IntSet newSet;
    if (size() + (otherIntSet.subtract(*this)).size() <= MAX_SIZE){
        for (int i = 0; i < used; i++){
            newSet.data[i] = data[i];
        }
        
        int temp = used;
        int j = 0;
        while (temp < used*2){
            newSet.data[temp] = otherIntSet.data[j];
            temp++;
            j++;
        }
    }
    return newSet;
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const //complete
{
    IntSet newSet;
    for (int i = 0; i < used; i++){
        newSet.data[i] = data[i];
    }
    
    for (int i = 0; i < used; i++){
        for (int j = 0; j < used; j++){
            if (newSet.data[i] == data[j]){
                int temp = newSet.data[used];
                newSet.data[i] = temp;
                newSet.data[used] = 0;
            }
        }
    }
    return newSet;
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const //complete
{
    IntSet mySet = *this;
    for (int i = 0; i < otherIntSet.size(); i++){
        if (otherIntSet.contains(mySet.data[i])){
            mySet.remove(mySet.data[i]);
        }
    }

    return mySet;
}

void IntSet::reset()
{
    for (int i = 0; i < used; i++){
        data[i] = 0;
    }
    used = 0;
}

bool IntSet::add(int anInt) //complete
{
    if (contains(anInt) ? size() <= MAX_SIZE : size() < MAX_SIZE){
        data[used] = anInt; // used will be 1 more than array index by nature
        used++;
        return true;
    }
    else
        return false;
}

bool IntSet::remove(int anInt) //complete
{
    bool myBool = false;
        if (contains(anInt) == true){
            int temp;
            temp = data[used-1];
            int index = 0;
            while (data[index] != anInt){ //find index of anInt
                index++;
            }
            data[index] = temp;
            data[used-1] = 0;
            used--;
            myBool = true;
        }
    return myBool;
}

bool equal(const IntSet& is1, const IntSet& is2)
{
    bool myBool = false;
    if (is1.isSubsetOf(is2) && is2.isSubsetOf(is1)){
        myBool = true;
    }
    
    return myBool;
}
