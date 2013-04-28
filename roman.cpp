/*////////////////////////////////
Caesar Cipher by Won You:

This program implements one of
the oldest encryption schemes
known to man.  It was invented
by Caesar to encode his messages.
All the letters in the message
is shifted a user-specified "x" amount 

*/////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string roman_encrypt(const string&, int);  /*Implements the conversion*/
void encryptFile(char*, char*, const int&); /*Calls the previous function and writes out
                                              to the specified files*/
void printPrompt() { cout << ">"; }


int main(){

  string text;
  char filename[20];
  char outputfile[20];
  string encoded_msg;
  int shift_key=0;
  int choice=1;

  cout << "\n------------------------------" << endl;
  cout << "    Welcome to Roman Cypher " << endl;
  cout << "\n------------------------------" << endl;

  while( choice != 3 ){ 
    cout << "\nChoose from the following options: " << endl;
    cout << "1) Encrypt or Decrypt File" << endl;
    cout << "2) Encrypt or Decrypt Text"  << endl;
    cout << "3) Quit" << endl;	
    printPrompt();
    cin >> choice;

    switch( choice ){
 
       case 1: 
               do{
	         cout << "Please enter the name of the input file: ";
                 cin >> filename;
	         cout << "Enter the name of the output file: ";
                 cin >> outputfile;

                 if (*outputfile == *filename)
                    cout << "\nError: The filenames cannot be the same!" << endl;

               } while (*outputfile == *filename);

	       cout << "\nHow much would like to shift by: ";
	       cin >> shift_key;

               encryptFile(filename, outputfile, shift_key);
               cout << "\nSuccess!" << endl;
               break;

       case 2: cout << "Please enter a piece of text: " << endl;
	       printPrompt();
	       cin >> text;
               cout << "\nHow much would like to shift by: ";
               cin >> shift_key;
               encoded_msg =  roman_encrypt(text, shift_key);
               cout << "\nThe encrypted message is: " << endl;
               cout << ">" << encoded_msg << endl;
	       break;

       case 3: cout << "\nHave a nice day:)" << endl;
               break;

       default: cout << "That was an invalid choice!" << endl;
                break;
    }

  }

  return 0;
}

string roman_encrypt(const string& msg, int shift_num ){

  string decoded;
  int a = (int)'a';
  int z = (int)'z';
  int A = (int)'A';
  int Z = (int)'Z';
  int diff;

  shift_num %= 26;  //the shift key should always be less than 26

  //do nothing if the shift is 0
  if (shift_num == 0) return msg;

  for (int i=0; i<msg.size(); i++){
    int temp;
    int m = (int)msg[i];

    temp = m + shift_num;

    /*This piece of code tries to encode the message
      when it reaches the extremites, i.e. a's and z's
      These letters wrap around in a circular fashion.
    */

    if (m >= A && m <= Z){ 
        if (temp <= Z && temp >= A) 
	  {decoded += (char)temp; continue;}
        else if (temp > Z && shift_num > 0)
	  temp -= 26;	
	else if (temp < A && shift_num < 0){
	  temp += 26;
	}
    }
    else if (m >= a && m <= z){ 
       if (temp <= z && temp >= a) 
	 {decoded += (char)temp; continue;}
        else if (temp > z && shift_num > 0)
	  temp -= 26;
	else if (temp < a && shift_num < 0){
	  temp += 26;
	}
    }
    
    else  //for non-alphabets
      temp = m;    

    decoded += (char)temp; 
  }

  if (decoded.size() > 0)
    return decoded;
  else{
    cout << "Failure: Nothing was decoded" << endl;
    return msg;
  }
}


//Read in the file names and write out the results to them.
void encryptFile(char* inputFile, char* outputFile, const int& cipherKey){

  ifstream inFile;
  ofstream outFile;
  char c;

  inFile.open(inputFile);
  outFile.open(outputFile);

  if (!inFile || !outFile){
    cout << "Error: Failed to open the file(s)!" << endl;
    return;
  }

   while (inFile.get(c)){
          string letter="";
	  letter+=c;
          letter = roman_encrypt(letter, cipherKey);
          outFile << letter;
   }

   inFile.close();
   outFile.close();
   inFile.clear();
   outFile.clear();
   return;
}
