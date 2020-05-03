#include <iostream>
#include <list>
#include <unordered_set>
#include <iostream>
#include <cstdint>
#include <cstring>
using namespace std;




void printSet(unordered_set<int> mySet) {
    for (int l : mySet) {
        cout << l << " ";
    }
    cout << endl;
}

bool insertNumber(int number, unordered_set<int> *mySet) {
    std::pair<std::unordered_set<int>::iterator,bool> ret;
    ret = mySet -> insert(number);
    return ret.second;
}


void solver(int n, int* numberArray, int index, unordered_set<int>* setArray, int currentNumber) {

    int tempIndex = index;
    bool accepted;
    bool insertAccepted;
    int qtyAccepted = 1;

    unordered_set<int> numberSet;
    list<int> generatedNumbers;
    int multResult, sumResult;
    while (tempIndex) {
        for (int num : setArray[tempIndex-1]) {
            numberSet.insert(num);
        } 
        tempIndex--;
    }

    while (index < n) {
        numberArray[index] = currentNumber;
        accepted = true;
        for (int i = 0; i < qtyAccepted; i++)
        {
            sumResult = currentNumber + numberArray[i];
            multResult = currentNumber * numberArray[i];
            insertAccepted = insertNumber(sumResult, &numberSet);

            if (!insertAccepted) {
                accepted = false;
                break;
                
            } else {
                generatedNumbers.push_back(sumResult);
                insertAccepted = insertNumber(multResult, &numberSet);
                if (!insertAccepted) {
                    accepted = false;
                    break;
                } else {
                    generatedNumbers.push_back(multResult);
                }
            }
            // cout << "Continuing" << endl;
        }
        
        if (accepted) {
            // cout << "Number: " << currentNumber << " ACCEPTED" << endl;
            // cout << endl;
            // int gNsize = generatedNumbers.size();
            unordered_set<int> s(begin(generatedNumbers), end(generatedNumbers));
            setArray[index] = s;
            index++;
            qtyAccepted++;
        } else {
            for (auto k : generatedNumbers) {
                numberSet.erase(k);
            }
        }
        generatedNumbers.clear();
        currentNumber++;
    }

}

extern "C" {
    int16_t* searchNumbers(int n, int iter) {
        int MAX_ITER = iter;
        int numberArray[n];
        unordered_set<int> setArray[n];
        solver(n, numberArray, 0, setArray, 1);
        
        int currentIndex = n-2;
        int upperBound = numberArray[n-1];
        int tempNumber, tempIndex;
        int tempNumberArray[n];
        unordered_set<int> tempSetArray[n];
        int bestNumberArray[n];
        tempNumber = numberArray[currentIndex] + 1;
        bool tempIndexChanged = false;
        int outerIndex = n-2;

        copy(numberArray, numberArray + n, bestNumberArray);

        while (outerIndex >= 0 ) {
            if (!MAX_ITER) {
                break;
            } 
            while (currentIndex >= outerIndex) {
                if (MAX_ITER) {
                    MAX_ITER--;
                } else {
                    break;
                }

                tempIndex = currentIndex;
                while (tempIndex > 0 && tempNumber < upperBound) {
                    unordered_set<int>::iterator it = setArray[tempIndex-1].find(tempNumber);
                    if (it != setArray[tempIndex-1].end()) {
                        tempNumber++;
                    }
                    tempIndex--;
                }

                if (tempNumber >= upperBound) {
                    currentIndex--;
                    tempNumber = numberArray[currentIndex];
                    tempIndexChanged = true;
                    continue;
                }

                copy(numberArray, numberArray + n, tempNumberArray);
                copy(setArray, setArray + n, tempSetArray);
                solver(n, tempNumberArray, currentIndex, tempSetArray, tempNumber);


                if (tempNumberArray[n-1] < numberArray[n-1]) {
                    upperBound = tempNumberArray[n-1];

                    copy(tempNumberArray, tempNumberArray + n, numberArray);
                    copy(tempSetArray, tempSetArray + n, setArray);
                    copy(tempNumberArray, tempNumberArray + n, bestNumberArray);
                }
                tempNumber = tempNumberArray[currentIndex] + 1;

            }
            outerIndex--;
            currentIndex = n-2;
            tempNumber = numberArray[currentIndex];
        }

        int16_t numbers[n];
        for (int i = 0; i < n; i++) {
            // cout << bestNumberArray[i] << " ";
            numbers[i] = bestNumberArray[i];
        }
        // cout << endl;

        int16_t* ptr = &numbers[0];
        return ptr;
    }
}

