import { Module } from "/findSetOfNumbers.js"
import { searchNumbersJs } from "/findSetOfNum.js"

Module.onRuntimeInitialized = function() { 

    let cppButton = document.getElementById("cpp_search");
    let jsButton = document.getElementById("js_search");

    let cppInput = document.getElementById("cpp_n");
    let jsInput = document.getElementById("js_n");
    
    const cppArray = [];
    let cppN, cppResult;
    cppButton.onclick = () =>{
        cppN = cppInput.value;
        console.log(cpp_n);
        cppResult = Module._searchNumbers(cppN);

        for (let v = 0; v < cppN; v++) {
            cppArray.push(Module.HEAP16[cppResult/Int16Array.BYTES_PER_ELEMENT+v])
        }

        console.log(cppArray);

        cppArray.length = 0;

    }

    let jsArray = [];
    let jsN;
    jsButton.onclick = () => {
        jsN = jsInput.value;
        console.log(jsN);
        jsArray = searchNumbersJs(jsN);
        
        console.log(jsArray);
    }

}
