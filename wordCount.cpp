/* Author: Thomas Woeste
 * Email: tewo224@uky.edu
 * Date: 4/7/20
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

const int hashSize = 100;

struct wordCnt{
    string word;
    int count = 0;
};

//Calculates and returns a hashKey based on the passed in word
int findHashKey(string wordToHash){
    int hashKey = 0;
    for(unsigned int cnt = 0; cnt < wordToHash.length(); cnt++){
       char currChar = wordToHash[cnt];
       hashKey = hashKey + (int)currChar + cnt;
    }
    return (hashKey % hashSize);
} //findHashKey()

//Compares two strings and returns 0 if they are the same
int compareW(string compareWord, string otherCompareW){
    int compRet = compareWord.compare(otherCompareW);
    return compRet;
} //compareW()


//Swap the value at the first input with the second
void swap(wordCnt sortArray[], int lowIndex, int highIndex){
    wordCnt temp = sortArray[lowIndex];
    sortArray[lowIndex] = sortArray[highIndex];
    sortArray[highIndex] = temp;
} //Swap()

//Partions the the array using lomutos method
int lPartition(wordCnt sortArray[], int lowIndex, int highIndex){
    int pivotValue = sortArray[lowIndex].count;
    int divideIndex = lowIndex;
    for (int combIndex = lowIndex+1; combIndex <= highIndex; combIndex++){
        if(sortArray[combIndex].count > pivotValue){
            divideIndex += 1;
            swap(sortArray, divideIndex, combIndex);
        }
    }
    swap(sortArray, divideIndex, lowIndex);
    return divideIndex;
} //lPartition()

//Sorts the array numerically by the count using quick sort
void sortNumeric(wordCnt sortArray[], int lowIndex, int highIndex){
    if(highIndex - lowIndex <= 0)
        return;
    int midIndex = lPartition(sortArray, lowIndex, highIndex);
    sortNumeric(sortArray, lowIndex, midIndex-1);
    sortNumeric(sortArray, midIndex+1, highIndex);
} //sortNumeric()

//Partions the the array using lomutos method
int alphaPartition(wordCnt sortArray[], int lowIndex, int highIndex){
    string pivotValue = sortArray[lowIndex].word;
    int divideIndex = lowIndex;
    for (int combIndex = lowIndex+1; combIndex <= highIndex; combIndex++){
        if(sortArray[combIndex].word < pivotValue){
            divideIndex += 1;
            swap(sortArray, divideIndex, combIndex);
        }
    }
    swap(sortArray, divideIndex, lowIndex);
    return divideIndex;
} //alphaPartition()

//Sorts the array alphabetically using quick sort
void sortAlpha(wordCnt sortArray[], int lowIndex, int highIndex){
    if(highIndex - lowIndex <= 0)
        return;
    int midIndex = alphaPartition(sortArray, lowIndex, highIndex);
    sortAlpha(sortArray, lowIndex, midIndex-1);
    sortAlpha(sortArray, midIndex+1, highIndex);
} //sortAlphabetically



int main(){
    vector<wordCnt> hashArray[hashSize];
    string currWord;
    wordCnt currStruct;
    int hashKey = 0;
    int foundWord = 0;
    //Take in the first word from standard in
    while(!(cin >> currWord).eof()){
        hashKey = findHashKey(currWord);

        //check if currWord is already in the hash array
        if(hashArray[hashKey].empty() == false){
            //Iterate Through the vector at the hashKey
            for(auto i = hashArray[hashKey].begin(); i != hashArray[hashKey].end(); i++){
                int compRet = 0;
                //Check to see if the word matches
                compRet = compareW(currWord, i->word);
                //If it does match increase the count
                if(compRet == 0){
                    i->count++;
                    foundWord = 1;
                }
            }
            //If the word is never found add it to the vector
            if(foundWord  == 0){
                currStruct.count =  1;
                currStruct.word = currWord;
                hashArray[hashKey].push_back(currStruct);
            }
        }
        else{
            currStruct.count =  1;
            currStruct.word = currWord;
            hashArray[hashKey].push_back(currStruct);
        }
        //reset foundWord
        foundWord = 0;
    }
    
    //Convert the hash array to a vector with all the wordCnt structs
    vector<wordCnt> fullVectors;
    for(int j = 0; j < hashSize; j++){
        fullVectors.insert(fullVectors.end(), hashArray[j].begin(), hashArray[j].end());
    }
    
    //Convert that vector to an array to sort
    int arraySize = fullVectors.size();
    wordCnt* sortingArray = new wordCnt[arraySize]; //dynamically allocated an array
    int itr = 0;
    for(auto p = fullVectors.begin(); p != fullVectors.end(); p++){
        sortingArray[itr].word = p->word;
        sortingArray[itr].count = p->count;
        itr += 1;
    }
    
    //Sort alphabetically and then print
    sortAlpha(sortingArray, 0, arraySize-1);
    //Prints the array
    for(int j = 0; j < arraySize; j++ ){
        cout << sortingArray[j].word << " " << sortingArray[j].count << endl;
    }


    //Blank line
    cout << endl;
    
    //Sort Numerically and print
    sortNumeric(sortingArray, 0, arraySize-1);
    //Prints the array
    for(int j = 0; j < arraySize; j++ ){
        cout << sortingArray[j].word << " " << sortingArray[j].count << endl;
    }
    
    return 0;
} //main()




