// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

// Define an array of strings (an array of char pointers, like argv)



int main(int argc, char *argv[] ) {
    srand(time(0));
    char guess[80];


    bool wordGuessed = false;
    int numTurns = 10;
    int numWords;
    char buffer[41];
    char** wordBank;


    //checking command line arguments
    if ( argc != 2){
        cout<<"\nUser did not provide enough command line arguments.\n";
        return 0;
    }


    //opening the fle
    fstream  file;
    file.open(argv[1], ios::out | ios::in );
    if ( !file.is_open() ){
        cout<<"\nFILE WAS NOT SUCCESSFULLY OPENED BY SCRAMBLE.CPP, PROGRAM SHUTTING DOWN\n";
        return 0;
    }


    // reading from the file
    string str;

    if(!(file >> numWords)) {
        cout << "\nNUMBER OF WORDS WAS NOT DETECTED BY SCRAMBLE.CPP, PROGRAM SHUTTING DOWN\n";
        return 0;
    }
    wordBank = new char*[numWords];


    for(int i = 0; i < numWords; i++) {
        file >> buffer;
        int wordLen = strlen(buffer);
        wordBank[i] = new char [wordLen+1];
        strcpy(wordBank[i],buffer);


    }




    // Pick a random word from the wordBank
    int target = rand() % numWords;
    int targetLen = strlen(wordBank[target]);

    // Make a dynamically-allocated copy of the word and scramble it
    char* word = new char[targetLen+1];
    strcpy(word, wordBank[target]);
    permute(word, targetLen);

    // An individual game continues until a word
    //  is guessed correctly or 10 turns have elapsed
    while (!wordGuessed && numTurns > 0) {
        cout << "Scrambled word: " << word << endl;
        cout << "What do you guess the original word is? ";
        cin >> guess;
        wordGuessed = (strcmp(guess, wordBank[target]) == 0);
        numTurns--;
    }
    if (wordGuessed) {
        cout << "You win!" << endl;
    }
    else {
        cout << "Too many turns...You lose!" << endl;
    }

    delete [] word;
    for(int i = 0; i < numWords; i++) {
        delete[] wordBank[i];


    }
    delete[] wordBank;

    return 0;
}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len) {
    for (int i = len-1; i > 0; --i) {
        int r = rand() % i;
        char temp = items[i];
        items[i] = items[r];
        items[r] = temp;
    }
}



