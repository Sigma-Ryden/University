let row = parseInt(window.prompt("Введіть кількість рядків двовимірного масиву"));
let col = parseInt(window.prompt("Введіть кількість стовпців двовимірного масиву"));

let C = [];
let D = new Array(row);

createMatrix(C, row, col);
fillMatrix(C, row, col);

document.write("Вхідний двовимірний масив С:<br>");
printMatrix(C);

toPositiveArray(D, C, row, col);

document.write("Вихідний одновимірний масив D:<br>");
printArray(D);


function toPositiveArray(arr, matrix, row, col){
    for(let i = 0; i < row; i++){
        arr[i] = 0;
        for(let j = 0; j < col; j++){
            if(matrix[i][j] > 0){
                arr[i] += matrix[i][j];
            }
        }
    }
    return arr;
}

function createMatrix(matrix, row, col){
    for(let i = 0; i < row; i++){
        matrix[i] = new Array(col);
    }
    return matrix;
}

function fillMatrix(matrix, row, col){
    for (let i = 0; i < row; i++) {
        for (let j = 0; j < col; j++) {
            matrix[i][j] = Math.round(Math.random() * 200 - 100);
        }
    }
    return matrix;
}

function printMatrix(matrix){
    document.write("<table>");
    for (let i = 0; i < matrix.length; i++) {
        document.write("<tr><td>" + matrix[i].join("</td><td>") + "</td></tr>");
    }
    document.write("</table><br>");
}

function printArray(arr){
    document.write("<table><tr><td>" + arr.join("</td><td>") + "</td></tr></table><br>");
}