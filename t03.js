import { Module } from "./findSetOfNumbers.js"
import { searchNumbersJs } from "./findSetOfNum.js"

const cppRunner = (n, iter) => {
    let cppResult;
    const cppArray = [];
    cppResult = Module._searchNumbers(n, iter);

    for (let v = 0; v < n; v++) {
        cppArray.push(Module.HEAP16[cppResult/Int16Array.BYTES_PER_ELEMENT+v])
    }
    return cppArray;
}


const tableUpdater = (n, iter, jsTime, cppTime, maxNum, numArray) => {
    $('#result-table > tbody:last-child').append(`<tr>
    <th scope="row">${$('#result-table tr').length}</th>
    <td>${iter}</td>
    <td>${n}</td>
    <td>${jsTime.toFixed(2)} ms</td>
    <td>${cppTime.toFixed(2)} ms</td>
    <td><a href="#" data-toggle="popover" title="Result Array" data-content="${numArray}">${maxNum}</a></td>
    </tr>`);
    $('[data-toggle="popover"]').popover()
}


Module.onRuntimeInitialized = function() { 
    let compareButton = document.getElementById("exec-comparison");
    let iterAmount = document.getElementById("iter-amount");
    let iterAmountPow = document.getElementById("iter-amount-pow");
    let arrayLengthElem = document.getElementById("array-length");
    let iterNum;
    iterAmount.oninput = () => {
        let power = iterAmount.value;
        let result = Math.pow(10, +power);
        iterAmountPow.value = result;
    }

    compareButton.onclick = () => {
        let cppResult, jsResult;
        let n, iter;
        n = arrayLengthElem.value;
        iter = iterAmountPow.value;
        let cppStartTime = performance.now();
        
        cppResult = cppRunner(n, iter);
        let cppEndTime = performance.now();
        let totalCppTime = cppEndTime - cppStartTime;
        let promise1 = $('#modal-bar').attr('aria-valuenow', '50').promise();
        let promise2 = $('#modal-bar').css('width', '50%').promise();
        let jsStartTime = performance.now();
        jsResult = searchNumbersJs(n, iter);
        let jsEndTime = performance.now();
        let totalJSTime = jsEndTime - jsStartTime;
        console.log(totalCppTime);
        console.log(totalJSTime);
        tableUpdater(n, iter, totalJSTime, totalCppTime, jsResult.slice(-1)[0], jsResult.join(', '));
    }
}


