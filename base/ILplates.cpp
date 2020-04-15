/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//

#include <iostream>
#include <string>
#include "ILplates.h"

using namespace std;

//
// isCorrectFormat:
//
// Given the plate in a string, returns whether or not the plate is a valid plate, 
//  also return whether it is a personalized or vanity plate which is stored asa string into the address of a string that is passed in
//
//
bool isCorrectFormat(string plate, string &licenseType, string &firstLetters, string &secondNumbers){

  //Local variable that will store the position of the space in the license plate   
  int spaceAtPos = -1;
  
  //Empty string was passed, invalid plate 
  if (plate.length() == 0){
      return false;
  }
  
  //Loop through each character in string
  for (unsigned int i = 0; i < plate.length(); i++){
    
    //Get ASCII - 'A'
    int ascii = plate[i] - 'A';
    
    //If the char is not an alphabet, invalid plate
    if (ascii > 25) {
        return false;
    }
    //If the char is not a space and is anything other than a number, invalid plate
    else if (ascii < -17 && ascii != -33){
        return false;
    }
    //If the char is a character other than numbers or letters, invalid plate
    else if (ascii > -8 && ascii < 0){
        return false;
    }
 
    //If a space is found, store its position into variable
    if (plate[i] == ' ' && spaceAtPos == -1){
        spaceAtPos = i;
    }  
    //If a second space is found, then the input is wrong as there should not be two spaces
    else if (spaceAtPos != -1 && plate[i] == ' '){
        return false;
    }
  }
  
  //If a space exists in the license plate, it is a personalized plate
  if (spaceAtPos != -1){
     
      //Set the licenseType string to personalized
      licenseType = "Personalized";
      
      //Get the letters before space and store into string
      string t = plate.substr(0, spaceAtPos);
      firstLetters = t;

      //Get the letters after space and store into string
      string s = plate.substr(spaceAtPos + 1, plate.length() - spaceAtPos + 1);
      secondNumbers = s;

      //Go through each character of letters and make sure they are alphabets
      for (char c : t){
          
          //Get ascii difference
          int ascii = c - 'A';
          
          //Return false if ascii value is found of non-alphabetic character
          if ( ascii > 25 || ascii < 0){
             return false;
          }
          
      }
      
      //Store letters after space into integer and check if the length is same after conversion
      int number = atoi(s.c_str());
      
      //Return false if it isn't 
      if(to_string(number).length() != s.length()){
          return false;
      }
      
      //If the space is in the wrong place or the number is of a wrong length, invalid plate
      if(number == 0 || spaceAtPos == 0 || spaceAtPos > 6 || s.length() > 2 || s.length() == 0 || (spaceAtPos == 6 && s.length() > 1)){  
          return false;
      }
  }
  //If there is no space in the license plate number, it is a vanity plate
  else{
    
    //Set the licenseType string to personalized
    licenseType = "Vanity";
      
    //Get ascii difference
    int ascii = plate[0] - 'A';
    
    //If the first character is an alphabet
    if (ascii <= 25 && ascii >= 0){

        //If the number of letters are more than 7, invalid plate
        if (plate.length() > 7 || plate.length() == 0){
            return false;
        }
        
        //Check if all are alphabets
        for (char c : plate){
            
            int ascii2 = c - 'A'; //Get ascii value
            
            //If any of the characters are any character but an alphabet, invalid plate
            if ( ascii2 > 25 || ascii2 < 0){
                return false;
            }
            
        }    
        
        //Store that all characters of the license plate are alphabets
        firstLetters = "Letters";

    } 
    //If first character is a number, make sure they are all numbers
    else if ((ascii > -18) && (ascii < -7)){
        
        //If the number of characters are more than 3, 0, or if '0' exists at the first place, invalid plate
        if (plate.length() > 3 || plate.length() == 0){
            return false;
        }
        
        //Check if all characters are numbers
        for (char c : plate){
            
            int ascii2 = c - 'A'; //Get ascii value
            
            //If any of the characters are any character but a number, invalid plate
            if ( ascii2 < -17 || ascii2 > -8){
                 return false;
            }
            
        }//Loop end
         
        //Store that all characters of the license plate are numbers
        firstLetters = "Nums"; 
    }
  }//end of else
    
  //return true, if all conditions above are unmet, plate is valid
  return true;
}

//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//

int ILplates::Hash(string plate)
{
    //Declare strings to store substrings of license plate
    string licenseType;
    string firstLetters;
    string secondNumbers;

    int index = -1;

    //If the License Plate is incorrect, return -1 
    if ( !isCorrectFormat(plate, licenseType, firstLetters, secondNumbers) ){
        return -1;
    }
     
    //If the license type is Personalized 
    if ( licenseType == "Personalized" ){
        
        //Go through each character and multiply the total with ASCII difference
        int total = 1;
        for (char c : plate){
            total = total * (c - 'a');
        }
        
        //Calculate index
        index = (total + stoi(secondNumbers) * 663);
          
    }
    //If the license type is Vanity 
    else if (licenseType == "Vanity"){
         
        //Go through each character and multiply the total with ASCII difference
        int total = -1;
        if (firstLetters == "Nums") {
            
            //Calculate index
            index = stoi(plate) * 662 * 10;
        
        }
        else if (firstLetters == "Letters") {
            
            //Go through each character and multiply the total with ASCII difference
            for (char c : plate){
                total = total * (c - 'a' - 'A');
            }
             
            //Calculate index
            index = total * 997;
             
        }
    }   
  return abs( (index * 199) % HT.Size());
}

//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
     
  //Get index from hash function and store into local variables
  int index = ILplates::Hash(plate);
  int index2 = index;
  
  //Declare local instances of variables that can be passed with Get function
  bool empty;
  string key;
  int value;
  
  //Get what is stored at the index
  HT.Get(index, empty, key, value);
  
  //If what is at index is empty, return -1
  if (empty == true){
      return -1;
  }
  //If the place is non-empty
  else{
      
      //Loop and lock for where key matches the plate, return value where it does
      while(empty == false){
          
          //If there is a match, return the value
          if (key == plate){
              return value;
          }
          
          //Increment index
          index++;
          
          //Wrap around if it reaches the end of the data structure
          if (index >= HT.Size()){
              index = 0;
          }
           
          //If the entire structure was searched once, break
          if (index == index2){
              break;
          }
          
          //Get what is at that position
          HT.Get(index, empty, key, value);
          
      }//end of loop
            
   //If it gets here a match was not found, return -1
   return -1;
  }

}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
  //Declare local instances of variables that can be passed with Get function
  bool empty;
  string key;
  int value;
    
  //Get index from Hash function
  int index = ILplates::Hash(plate);
  
  //If the plate was invalid, there's nothing to insert
  if (index == -1){
      return;
  }
    
  //Store the index returned by the hash into another local variable
  int origIndex = index;
  
     
  //Call the get function using the index
  HT.Get(index, empty, key, value);
     
    //Loop through until:
    //   Empty val is found
    //    OR 
    //   A match is found for the plate numbers
    //    OR
    //   The index exceeded the size AND came back around to the original index
    while(empty != true){
        
        //If there is a match store the new value and return
        if (key == plate){
            HT.Set(index, plate, newValue);
            return;
        }
        
        //Increment index
        index++;
        
        //If index reaches size of hashtable, reset index to 0
        if (index >= HT.Size()){
            index = 0;
        }
        
        //If index wraps around hashtable and comes back, return
        if(index == origIndex){
            return;
        }
         
        HT.Get(index, empty, key, value);
    }
    
    //If a space is found, store the key + value
    HT.Set(index, plate, newValue);
    
}
