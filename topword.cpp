#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm> 

using namespace std;

struct fileNames {
    string inputFileName;
    string outputFileName;
};

void parseParameters(fileNames *parameters, string fileNames);
void retrieveWordsFromInputFile(vector<string> *words, ifstream *input);
map<string, int> countWordsOccurrences(vector<string> words);
int getHighestWordFrequency(map<string, int> wordCounterMap);
vector<string> getMostRepeatedWords(map<string, int> wordCounterMap, int highestWordFrequency);
void createOutputFile(string outputFileName, vector<string> getMostRepeatedWords, int highestWordFrequency);
bool compareStrings(string a, string b);

//Loops were used to process the data. A hashmap works as a counter of the words frequency
int main(int argc, char* argv[]) {
    
    fileNames parameters;
    parseParameters(&parameters, argv[1]);

    //Openning input file
    ifstream input;
    input.open(parameters.inputFileName);

    ///If file was not able to open show following error message
    if(!input.is_open()) {
        cout << "\nERROR: The parameters were not supported. Expected the following format: \"input=f.txt;output=out.txt\"; but got: \"" << argv[1] << "\"\n\n";
    }

    //Vector of strings to save all present words on the input file
    vector<string> words;
    retrieveWordsFromInputFile(&words, &input);

    //Closing file
    input.close();

    //Map to hold words and their frequency
    map<string, int> wordCounterMap = countWordsOccurrences(words);

    //Stores the max word frequency
    int highestWordFrequency = getHighestWordFrequency(wordCounterMap);
    
    //Stores all words that repeat the max word frequency
    vector<string> mostRepeatedWords = getMostRepeatedWords(wordCounterMap, highestWordFrequency);

    //Sort most repeated words alphabetically
    sort(mostRepeatedWords.begin(), mostRepeatedWords.end(), compareStrings);

    //Write words to output file
    createOutputFile(parameters.outputFileName, mostRepeatedWords, highestWordFrequency);
    
    return 0;
}

//Parsing parameters. Expecting following format "input=f.txt;output=out.txt"
void parseParameters(fileNames *parameters, string fileNames) {
    stringstream fileNamesStringStream(fileNames);
    
    getline(fileNamesStringStream, parameters->inputFileName, '=');
    getline(fileNamesStringStream, parameters->inputFileName, ';');
    getline(fileNamesStringStream, parameters->outputFileName, '=');
    getline(fileNamesStringStream, parameters->outputFileName, '=');
};

//Retreives every word. Ignores all words containing numbers
void retrieveWordsFromInputFile(vector<string> *words, ifstream *input) {
    char character; //Char variable to save each character evaluated on the file
    string word = ""; //String to track the word that will be saved on the words vector
    bool hasDigit; //Boolean that tracks whether the current words has a digit(determines if word is to be ignored)

    //Reading input file by character
    while (input->good()) {
        input->get(character); //get character

        if(isalpha(character) && input->tellg() != -1) {
            //if the character is part of the alphabet and it is not the last character, then add char to the word
            word += tolower(character);
        } else if(isdigit(character)) {
            //if character is a digit, change hasDigit state variable to indicate that the word has a digit in it
            hasDigit = true;
        } else {
            //Otherwise, if the word has no digits save the word on the vector. Set has digit back to false and reset the word variable to an empty string
            if (!hasDigit) {
                words->push_back(word);
            }
            hasDigit = false;
            word = "";
        }
    }
};

//Returns a map that contains the word as the key and the frequency of the word as the value <string, int>
map<string, int> countWordsOccurrences(vector<string> words) {
    map<string, int> wordCounterMap;
    for(int i = 0; i < words.size(); i++) {
        //if the word is not an empty string
        if(words[i].size() > 0) {
            wordCounterMap[words[i]]++;
        }
   }

   return wordCounterMap;
}

int getHighestWordFrequency(map<string, int> wordCounterMap) {
    int highestWordFrequency = 0;
    for(auto &word : wordCounterMap) {
        if(word.second > highestWordFrequency) {
            highestWordFrequency = word.second;
        }
    }
    return highestWordFrequency;
}

vector<string> getMostRepeatedWords(map<string, int> wordCounterMap, int highestWordFrequency) {
    vector<string> mostRepeatedWords;
    for(auto &word : wordCounterMap) {
        if(word.second == highestWordFrequency) {
            mostRepeatedWords.push_back(word.first);
        }
    }
    return mostRepeatedWords;
}

void createOutputFile(string outputFileName, vector<string> mostRepeatedWords, int highestWordFrequency) {
    ofstream outputFile;
    outputFile.open(outputFileName);
    for (int i = 0; i < mostRepeatedWords.size(); i++) {
        outputFile << mostRepeatedWords[i] << " " << highestWordFrequency << "\n";
    }
    outputFile.close();
}

bool compareStrings(string a, string b) {
    return a<b;
}