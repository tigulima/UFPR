program e19;

var num1, num2, num3, falta: real;

begin
    read(num1, num2, num3, falta);

    if (falta >= 10) then
        write('NAO')
    else
    begin
        if ((num1 + num2 + num3) / 3 < 4) then
            write('NAO')
        else if ((num1 + num2 + num3) / 3 >= 7) then
            write('SIM')
        else 
            write('TALVEZ');
    end
end.