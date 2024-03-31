var phoneBook = []; // Тут ви зберігаєте записи як хочете

/*
   Функція додавання запису в телефонну книгу.
*/
phoneBook.add = function (name, phone, email) {
  phoneBook.push({ name, phone, email });
};

/*
   Функція пошуку записів в телефонній книзі.
   Пошук ведеться по всім полям.
*/
phoneBook.find = function (query) {
  phoneBook.forEach(item => {
    for(let key in item) {
      if(item[key].indexOf(query) !== -1) {
        document.write(item.name + ", " + item.phone + ", " + item.email + "<br>");
      }
    }
  });
};

/*
   Функція видалення запису в телефонній книзі.
*/
phoneBook.remove = function (query) {
  let count = 0;
  phoneBook.forEach(item => {
    for(let key in item) {
      if(item[key].indexOf(query) !== -1) {
        phoneBook.pop();
        ++count;
      }
    }
  });
  document.write("Вилучено " + count + " контакт<br>");
};

/*
   Функція виведення всіх телефонів.
*/
phoneBook.showTable = function () {
  let table = document.createElement('table');

  let headRow = document.createElement('tr');
  for(const key in phoneBook[0]) {
    let headCell = document.createElement('th');
    headCell.textContent = key;
    headRow.appendChild(headCell);
  }
  table.appendChild(headRow);

  phoneBook.forEach(item => {
    let row = document.createElement('tr');
    for(const key in item) {
      let cell = document.createElement('td');
      cell.textContent = item[key];
      row.appendChild(cell);
    }
    table.appendChild(row); 
  });

  document.body.appendChild(table);
}