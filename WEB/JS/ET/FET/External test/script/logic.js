let textAnalysis = localStorage.getItem('myWordProcessing');
let collection = [];
let toWord = '';

//Boolean
function isLetter(symbol) {
    return symbol.toLowerCase() != symbol.toUpperCase();
}
function isEntry(str, substr) {
    return str[0] == substr[0] && str.indexOf(substr) != -1;
}
collection.isExist = function(word) {
    for(let i = 0; i < this.length; ++i) {
        if(this[i].word == word) {
            ++this[i].count;
            return true;
        }
    }
    return false;
};
//...

//Some collection
collection.addElement = function(word, count) {
    this.push({ word, count });
};
collection.fill = function(text) {    
    let subStrLen = 0;
    let word = '';

    for(let i = 0; i < text.length; ++i) {
        if(isLetter(text[i])) {
            ++subStrLen;
        } else {
            if(subStrLen == 0) continue;
            word = text.substring(i - subStrLen, i).toLowerCase();
            if(!collection.isExist(word)) {
                collection.addElement(word, 1);
            }
            subStrLen = 0;
        }
    }
};
collection.setList = function(word) {
    let list = document.querySelector('.searchList');
    let temp = '';
    
    this.forEach( key => {
        if(isEntry(key.word, word)) {
            temp += key.word + '<br>';
        }
    });
    list.innerHTML = temp;
};
//...

//Build
getTable = function() {
    let table = document.createElement('table');
    table.style.border = '1px solid black';
    table.style.width = '95%';

    collection.forEach( key => {
        let trSection = document.createElement('tr');
        let tdWord = document.createElement('td');
        let tdCount = document.createElement('td');

        tdWord.style.border = '1px solid black';
        tdWord.style.width = '75%';
        tdWord.textContent = key.word;

        tdCount.style.border = '1px solid black';
        tdCount.style.width = '25%';
        tdCount.textContent = key.count;

        trSection.appendChild(tdWord);
        trSection.appendChild(tdCount);
        table.appendChild(trSection);
    });
    
    return table;
};
function getSearchBlock() {
    let searchBlock = document.createElement('div');
    let searchField = document.createElement('input');
    let searchButton = document.createElement('button');
    let searchList = document.createElement('div');

    searchField.type = 'text';
    searchField.style.color = 'orange';

    searchButton.textContent = 'Search';

    searchList.className = 'searchList';
    searchList.style.display = 'none';
    searchList.style.zIndex = '0';
    searchList.style.minWidth = '10%';
    searchList.style.position = 'absolute';
    searchList.style.backgroundColor = 'gray';

    searchBlock.appendChild(searchField);
    searchBlock.appendChild(searchButton);
    searchBlock.appendChild(searchList);

    return searchBlock;
}
function getWordProcessingBlock(text) {
    let wrapper = document.createElement('div');

    let tableSpace = document.createElement('div');
    let textSpace = document.createElement('div');
    let textBlock = document.createElement('p');

    textBlock.textContent = text;
    textBlock.className = 'textBlock';

    tableSpace.appendChild(getTable());
    textSpace.appendChild(getSearchBlock());
    textSpace.appendChild(textBlock);
    wrapper.appendChild(tableSpace);
    wrapper.appendChild(textSpace);

    wrapper.style.width = '100%';
    wrapper.style.display = 'grid';
    wrapper.style.gridTemplateColumns = '12.5% 87.5%';

    return wrapper;
}
//...

//Other
function showListBlock() {
    document.querySelector('.searchList').style.display = 'block';
    document.querySelector('.searchList').style.zIndex = '1';
} 
function hideListBlock() {
    document.querySelector('.searchList').style.display = 'none';
    document.querySelector('.searchList').style.zIndex = '0';
}
function changeBackgroundColorIn(str) {
    return "<span style='background: yellow'>" + str + "</span>";
}
//...

//Event
function eventfindWord(word, text, allEntry = false) {
    let temp = text[0];
    for(let i = 1; i < text.length; ++i) {
        if(text[i].toLowerCase() != word[0]) {
            temp += text[i];
        } else {
            let flag = true;
            let j = 1;
            while(j < word.length) {
                if(text[i + j] != word[j]) {
                    temp += text[i];
                    flag = false;
                    break;
                }
                ++j;
            }
            if(flag) {
                if(!allEntry) {
                    if(!isLetter(text[i - 1]) && !isLetter(text[i + j])) {
                        temp += changeBackgroundColorIn(text.substring(i, i + j));
                    } else {
                        temp += text.substring(i, i + j);
                    }
                } else {
                    temp += changeBackgroundColorIn(text.substring(i, i + j));
                }
                i += j - 1;
            }
        } 
    }
    let textBlock = document.querySelector('.textBlock');
    textBlock.innerHTML = temp;
}
function eventdetectWord(event) {
    if(event.key == 'Backspace') {
        if(toWord.length > 0) {
            toWord = toWord.substr(0, toWord.length - 1);
            if(toWord.length > 0) {
                collection.setList(toWord);
                showListBlock();
            } else {
                hideListBlock();
            }
        }
    } else if(event.key.length == 1 && isLetter(event.key)) {
        toWord += event.key.toLowerCase();
        collection.setList(toWord);
        showListBlock();
    }
}
//...

//INPUT POINT
collection.fill(textAnalysis);
document.body.appendChild(getWordProcessingBlock(textAnalysis));

let searchButton = document.querySelector('button');
let searchField = document.querySelector('input');

searchField.addEventListener('click', () => {
    if(toWord.length > 0) {
        showListBlock();
    }
});
searchButton.addEventListener('click', () => {
    hideListBlock();
    eventfindWord(toWord, textAnalysis);
});
searchField.addEventListener('keydown', eventdetectWord);
//...