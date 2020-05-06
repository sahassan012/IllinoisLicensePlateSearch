//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.  Implementation in associated .cpp
// file.
//

#pragma once
#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;

class ILplates
{
private:
  hashtable<string, int>& HT;  // reference to underlying hashtable:

public:
  ILplates(hashtable<string, int>& ht)
    : HT(ht)
  { }

  int  Hash(string plate);
  int  Search(string plate);
  void Insert(string plate, int newValue);
};
