
//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;

//
// sort:
//    Takes the vector of pairs by reference which stores the plates with their respective total fines 
//    and sorts the vector using the Bubble Sort algorithm
//   
void sort(vector< pair<string, int> > &platesFines){
     
     int i, j;
     
     //Get the size of the vector
     int n = platesFines.size();
   
     //For every pair in the vector minus 1
     for (i = 0; i < n-1; i++){
       //Go through the vector   
       for (j = 0; j < n-i-1; j++){
            
            //If first pair has a license plate that goes before the second, swap
            if (platesFines[j].first > platesFines[j+1].first){
               
               //Store addresses of first and second pair into local pointers  
               pair<string,int> *first = &platesFines[j];
               pair<string,int> *second = &platesFines[j+1];
               
               //Store pointer to first's pointer into a tmp and swap by storing second's pointer into first and lastly tmp into second
               pair<string,int> tmp = *first;
               *first = *second;
               *second = tmp;
            }
            
       }
     }
}

//
// outputFile:
//    Takes a vector of plates and amounts and outputs the data into .txt file
//
void outputFile(vector<string> plates, vector<int> amounts, string basename){
     
     //Vector of pairs that will store from plates and amounts vectors
     vector < pair<string, int> > platesFines;
     
     //Go through size of the plates vector 
     for (int i = 0; i < plates.size(); i++ ){
          
        //Make a pair of the plates and their respective amounts and push into vector of pairs
        pair<string, int> pair;
        pair.first = plates[i];
        pair.second = amounts[i];
        platesFines.push_back(pair);
     
     }

     //Sort the vector
     sort(platesFines);
     
     //Create the output file name
     string outputFileName = basename + "-output.txt";
     cout << "Writing '" << outputFileName << "'...\n"; 
     
     //Ofstream object that will handle the writing of the output file from the sorted vector of pairs
     ofstream outfile(outputFileName);
     for (int i = 0; i < platesFines.size(); i++ ){
        outfile << "\"" << platesFines[i].first << "\"" << " $" << platesFines[i].second << endl;
     }

}

//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid
    getline(infile, fine);
  }
}


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();
     
  //outputFile(plates, amounts);
  for (size_t i = 0; i < plates.size(); ++i)
  {
    //cout << plates[i] << ", " << amounts[i] << endl;
  }
  
  outputFile(plates,amounts,basename);
  //
  // done:
  //
  return 0;
}
