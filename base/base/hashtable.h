//
// Provides Get and Set functions for hashtable
// for accessing the underlying array.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
//

#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename TKey, typename TValue>
class hashtable
{
private:
  struct KeyValuePair
  {
    bool   Empty;
    TKey   Key;
    TValue Value;

    KeyValuePair()
    {
      Empty = true;
      Key   = {};   // default initializer
      Value = {};   // default initializer
    }
  };

  int            N;
  KeyValuePair*  Hashtable;  // array of (key, value) pairs

  int _Probes;
  int _Stores;

public:
  hashtable(int size)
  {
    N = size;
    Hashtable = new KeyValuePair[N];

    _Probes = 0;
    _Stores = 0;
  }

  virtual ~hashtable()
  {
    //
    // count the # of elements in the hash table:
    //
    int elements = 0;

    for (int i = 0; i < N; ++i)
    {
      if (!Hashtable[i].Empty)
        elements++;
    }

    //
    // output stats:
    //
    cout << endl;
    cout << "**Hashing Stats**" << endl;
    cout << "Probes: " << _Probes << endl;
    cout << "Stores: " << _Stores << endl;
    cout << "Elements: " << elements << endl;
    cout << endl;

    //
    // now we can free the memory:
    //
    delete[] Hashtable;
  }

  //
  // size
  //
  // Returns the size N of the hash table.
  //
  int Size()
  {
    return N;
  }

  //
  // Get
  //
  // Gets the data from the given index of the hash table: the Empty
  // status (T/F), the key, and the value.  If Empty is true, the key
  // and value will be the default values in C++ for their types.  If
  // the index is outside the bounds of the hashtable, the behavior 
  // of this function is undefined.
  //
  void Get(int index, bool& empty, TKey& key, TValue& value)
  {
    _Probes++;

    empty = Hashtable[index].Empty;
    key = Hashtable[index].Key;
    value = Hashtable[index].Value;
  }

  //
  // Sets
  //
  // Sets the location of the hash table to contain the given key and
  // value; the "Empty" status is set to false since this location now
  // contains data.  Any existing data at this location is overwritten.
  // If the index is outside the bounds of the hashtable, the behavior 
  // of this function is undefined.
  //
  void Set(int index, TKey key, TValue value)
  {
    _Stores++;

    Hashtable[index].Empty = false;
    Hashtable[index].Key = key;
    Hashtable[index].Value = value;
  }

  //
  // Keys
  //
  // Returns the keys in the hashtable, in order from 0..N-1.  Only
  // returns those keys where Empty is false.
  //
  vector<TKey> Keys()
  {
    vector<TKey>  V;

    for (int i = 0; i < N; ++i)
    {
      if (!Hashtable[i].Empty)
        V.push_back(Hashtable[i].Key);
    }

    return V;
  }

  //
  // Values
  //
  // Returns the va.ues in the hashtable, in order from 0..N-1.  Only
  // returns those values where Empty is false.
  //
  vector<TValue> Values()
  {
    vector<TValue>  V;

    for (int i = 0; i < N; ++i)
    {
      if (!Hashtable[i].Empty)
        V.push_back(Hashtable[i].Value);
    }

    return V;
  }

  //
  // Stats
  //
  // Returns some statistics about how the hashtable was used: # of
  // probes, # of stores, and # of elements currently in the table.
  //
  void Stats(int& probes, int& stores, int& elements)
  {
    probes = _Probes;
    stores = _Stores;

    elements = 0;

    for (int i = 0; i < N; ++i)
    {
      if (!Hashtable[i].Empty)
        elements++;
    }
  }

};
