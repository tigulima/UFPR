program e110;

var num1, num2: longint;

begin
    read(num1, num2);

    if (num1 mod num2 = 0) then
        write('SIM')
    else
        write('NAO');
end.