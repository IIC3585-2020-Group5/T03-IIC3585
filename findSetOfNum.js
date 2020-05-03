const insertNumber = (number, mySet) => {
    if (!mySet.has(number)) {
        mySet.add(number);
        return true;
    }
    return false;
}


const solver = (n, numberArray, index, setArray, currentNumber) => {
    // console.log(`Solver params: ${n}, ${numberArray}, ${index}, ${setArray}, ${currentNumber}`)
    let tempIndex = index;
    let accepted = false;
    let insertAccepted = false;
    let qtyAccepted = 1;
    let generatedNumbers = [];
    let multResult;
    let sumResult;
    const numberSet = new Set();
    while (tempIndex) {
        setArray[tempIndex-1].forEach(numberSet.add, numberSet);
        tempIndex--;
    }
    
    while (index < n) {
        numberArray[index] = currentNumber;
        accepted = true;
        for (let i = 0; i < qtyAccepted; i++) {
            sumResult = currentNumber + numberArray[i];
            multResult = currentNumber * numberArray[i];
            insertAccepted = insertNumber(sumResult, numberSet);

            if (!insertAccepted) {
                accepted = false;
                break;
            } else {
                generatedNumbers.push(sumResult);
                insertAccepted = insertNumber(multResult, numberSet);
                
                if (!insertAccepted) {
                    accepted = false;
                    break;
                } else {
                    generatedNumbers.push(multResult);
                }
            }
        }

        if (accepted) {
            setArray[index] = new Set(generatedNumbers);
            index++;
            qtyAccepted++;
        } else {
            generatedNumbers.forEach(k => {
                numberSet.delete(k)
            });
        }

        generatedNumbers = [];
        currentNumber++;
    }
    return [numberArray, setArray];
}



const searchNumbersJs = (n, iters) => {
    let MAX_ITER = iters;
    let numberArray, setArray;
    let result = solver(n, new Array(n), 0, new Array(n), 1);
    numberArray = result[0];
    setArray = result[1];

    
    let currentIndex = n-2;
    let upperBound = numberArray[n-1];
    let tempNumber, tempIndex, tempNumberArray, tempSetArray, bestNumberArray;
    tempNumber = numberArray[currentIndex] + 1;
    let tempIndexChanged = false;
    let outerIndex = n-2;
    
    bestNumberArray = [...numberArray];
    // console.log(bestNumberArray);

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

                if (setArray[tempIndex-1].has(tempNumber)) {
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

            result = solver(n, [...numberArray], currentIndex, [...setArray], tempNumber);
            tempNumberArray = result[0];
            tempSetArray = result[1];

            if (tempNumberArray[n-1] < numberArray[n-1]) {
                upperBound = tempNumberArray[n-1];
                numberArray = [...tempNumberArray];
                setArray = [...tempSetArray];
                bestNumberArray = [...tempNumberArray];
            }
            tempNumber = tempNumberArray[currentIndex] + 1;

        }
        outerIndex--;
        currentIndex = n-2;
        tempNumber = numberArray[currentIndex];
    }
    // console.log(bestNumberArray);
    return bestNumberArray;
}

export { searchNumbersJs };