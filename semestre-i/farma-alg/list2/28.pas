program e28;

var fahrenheit, celsius: real;

begin
    read(fahrenheit);
    celsius := (5*fahrenheit - 160) / 9;

    writeln(celsius:0:2);

    if (celsius <= 0) then
        write('solido')
        else if (celsius >= 100) then
            write('gasoso')
        else
            write('liquido');
end.