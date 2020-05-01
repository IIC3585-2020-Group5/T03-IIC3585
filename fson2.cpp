#include <iostream>
#include <list>
#include <set>
#include <cstdlib>
#include <ctime>
using namespace std;

void printSet(set<int> mySet) {
    for (int l : mySet) {
        cout << l << " ";
    }
    cout << endl;
}

bool insertNumber(int number, set<int> *mySet) {
    bool accept = true;
    int initSize = mySet -> size();
    mySet -> insert(number);

    // cout << "init: " << initSize << " after: " << mySet -> size() << endl;
    // cout << "Result: " << number << endl;
    if (mySet -> size() == initSize) {
        accept = false;
    }

    return accept;
}


int main(int argc, char const *argv[])
{
    
    srand(time(NULL));
    int n = 47;
    int index;
    int ran;
    bool accepted;
    int numberArray[n];
    int numberArray2[n];
    bool insertAccepted;
    int qtyAccepted;
    int currentNumber;


    set<int> numberSet;
    list<int>::iterator sumIt;
    list<int>::iterator multIt;
    list<int> generatedNumbers;
    list<int> currentAcceptedNumbers;



    int numberOfOptions = 100;
    int currentOption = 0;


    while (currentOption < numberOfOptions) {

        index = 0;
        qtyAccepted = 1;
        currentNumber = currentOption%10;

    
        while (index < n) {
        // while (currentNumber < 10) {

            // cout << "Current: " << currentNumber << endl;
            numberArray[index] = currentNumber;
            accepted = true;

            int multResult, sumResult;
            for (int i = 0; i < qtyAccepted; i++)
            {
                sumResult = currentNumber + numberArray[i];
                multResult = currentNumber * numberArray[i];

                insertAccepted = insertNumber(sumResult, &numberSet);

                if (!insertAccepted) {
                    accepted = false;
                    // cout << "Breaking" << endl;
                    break;
                    
                } else {
                    currentAcceptedNumbers.push_back(sumResult);

                    insertAccepted = insertNumber(multResult, &numberSet);



                    if (!insertAccepted) {
                        accepted = false;
                        // cout << "Breaking" << endl;
                        // cout << "Size: " << numberSet.size() << endl;
                        // printSet(numberSet);
                        // cout << endl;
                        break;
                    } else {
                        currentAcceptedNumbers.push_back(multResult);

                        // cout << "Size: " << numberSet.size() << endl;
                        // printSet(numberSet);
                        // cout << endl;
                    }
                }

                // cout << "Continuing" << endl;
            }
            

            if (accepted) {
                ran = rand()%10;
                // cout << "RANDOM: " << ran << endl;

                if (ran <= 7){
                    // cout << "Number: " << currentNumber << " ACCEPTED" << endl;
                    // cout << endl;
                    index++;
                    qtyAccepted++;
                } else {
                    for (int k : currentAcceptedNumbers) {
                        numberSet.erase(k);
                    }
                }


            } else {
                for (int k : currentAcceptedNumbers) {
                    numberSet.erase(k);
                }
            }

            currentAcceptedNumbers.clear();
            currentNumber++;
        }


        
        if (currentOption >= 1) {
            if (numberArray[n-1] < numberArray2[n-1]) {
                for (int j = 0; j < n; j++)
                {
                    numberArray2[j] = numberArray[j]; 
                }
            }
        } else {
            for (int j = 0; j < n; j++)
            {
                numberArray2[j] = numberArray[j]; 
            }
        }

        currentOption++;


    }

        
    for (int i = 0; i < n; i++)
    {
        cout << numberArray2[i] << " ";
    }
    cout << endl;


    
    return 0;
}