let flex = prompt('Enter your number');
load(flex);

function type_card(N){
    let length = Math.floor(Math.log10(N) + 1);
    let type;
    if(length == 13 || length == 16){
        type = Math.floor( N / Math.pow(10, length - 1));
        if(type == 4){
            return "VISA";
        }
        else if(type == 5 && length == 16){
            type = Math.floor(N / Math.pow(10, length - 2));
            if(type >= 51 && type <= 55){
                return "MACTERCARD";
            }
        }
    }
    if(length == 15){
    type = Math.floor( N / Math.pow(10, length - 2));
        if(type == 34 || 37){
            return "AMEX";
        }
    }

    return "INVALID";
}

function check_card(N){
    let sum = 0;
    let temp;
    let res;

    for(let i = 0; N > 0; i++){
        if(i % 2 != 0){
            temp = N % 10;
            res = temp * 2;
            if(res > 9){
                res = res % 10 + Math.floor(res / 10);
            }
            sum += res;
        }else{
            temp = N % 10;
            sum += temp;
        }
        N /= 10;
        N = Math.floor(N);
    }

    if(sum % 10 == 0){
        return "EXIST";
    }else{
        return "INVALID";
    }
}

function load(C){
    document.write("Вхідні дані: " + C + "<br>Результат: ");
    if(check_card(C)!=='INVALID'){
        document.write(type_card(C));
    }else{
        document.write('INVALID');
    }
}