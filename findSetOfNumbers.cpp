#include <iostream>
#include <list>
#include <set>
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

    cout << "init: " << initSize << " after: " << mySet -> size() << endl;
    cout << "Result: " << number << endl;
    if (mySet -> size() == initSize) {
        accept = false;
    }

    return accept;
}


int main(int argc, char const *argv[])
{

    int n = 47;
    int index = 0;
    bool accepted;
    int numberArray[n];
    bool insertAccepted;
    int qtyAccepted = 1;
    int currentNumber = 1;

    set<int> numberSet;
    list<int>::iterator sumIt;
    list<int>::iterator multIt;
    list<int> generatedNumbers;
    list<int> currentAcceptedNumbers;

    list<set<int> > options;


    while (index < n) {
    // while (currentNumber < 10) {

        cout << "Current: " << currentNumber << endl;
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
                cout << "Breaking" << endl;
                break;
                
            } else {
                currentAcceptedNumbers.push_back(sumResult);

                insertAccepted = insertNumber(multResult, &numberSet);



                if (!insertAccepted) {
                    accepted = false;
                    cout << "Breaking" << endl;
                    cout << "Size: " << numberSet.size() << endl;
                    // printSet(numberSet);
                    cout << endl;
                    break;
                } else {
                    currentAcceptedNumbers.push_back(multResult);

                    cout << "Size: " << numberSet.size() << endl;
                    // printSet(numberSet);
                    cout << endl;
                }
            }

            cout << "Continuing" << endl;
        }
        

        if (accepted) {
            cout << "Number: " << currentNumber << " ACCEPTED" << endl;
            cout << endl;
            index++;
            qtyAccepted++;
        } else {
            for (int k : currentAcceptedNumbers) {
                numberSet.erase(k);
            }
        }

        currentAcceptedNumbers.clear();
        currentNumber++;
    }



    for (int i = 0; i < n; i++)
    {
        cout << numberArray[i] << " ";
    }
    cout << endl;

    
    return 0;
}
