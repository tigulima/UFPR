program e35;

var salario: real;

begin
    read(salario);

    if (salario < 540) then
        write('NAO')
    else if (salario <= 1424) then
        write('1 ',salario * 0:0:2)
    else if (salario <= 2150) then
        write('2 ', salario * 0.075:0:2)
    else if (salario <= 2866) then
        write('3 ', salario * 0.15:0:2)
    else if (salario <= 3580) then
        write('4 ', salario * 0.225:0:2)
    else
        write('5 ', salario * 0.275:0:2);
end.