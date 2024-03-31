//Build
function getForm() {
    let form = document.createElement('form');
    
    let titleText = document.createElement('h3');
    let textBlock = document.createElement('p');
    let buttonBlock = document.createElement('p');

    let analysisButton = document.createElement('input');
    let resetButton = document.createElement('input');
    let textField = document.createElement('textarea');

    form.target = '_blank';
    form.action = 'utility.html';
    titleText.textContent = 'Word processing';

    analysisButton.type = 'submit';
    analysisButton.value = 'Analysis';
    resetButton.type = 'reset';
    resetButton.value = 'Clear';

    textField.placeholder = 'Put your story here...';
    textField.name = 'inputText';
    textField.cols = '60';
    textField.rows = '10';

    textBlock.appendChild(titleText);
    textBlock.appendChild(textField);
    form.appendChild(textBlock);

    buttonBlock.appendChild(analysisButton);
    buttonBlock.appendChild(resetButton);
    form.appendChild(buttonBlock);
    
    return form;
}
//...

//INPUT POINT
document.body.appendChild(getForm())
let toWordProcessing = document.querySelector('input');

toWordProcessing.addEventListener('click', () => {
    localStorage.setItem('myWordProcessing', ' ' + document.querySelector('textarea').value + ' ');
});
//...