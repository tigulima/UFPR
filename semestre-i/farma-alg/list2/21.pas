program e21;

var num, condition: longint;

begin
    read(num);

    condition := 0;

    if (num mod 7 = 0) then
        condition := 1;
    if (num mod 11 = 0) then
        condition := 2;
    if (num mod 7 = 0) and (num mod 11 = 0) then 
        condition := 3;

    if (condition = 0) then
        write('Nao e multiplo nem de 7 nem de 11.');
    if (condition = 1) then
        write('Multiplo exclusivamente de 7.');
    if (condition = 2) then
        write('Multiplo exclusivamente de 11.');
    if (condition = 3) then
        write('Multiplo de 7 e de 11.');
end.