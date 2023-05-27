program e100;

var num, soma: longint;

begin
    read(num);
    soma := (num div 100) + (num mod 100);
    if ( soma * soma = num) then
    write('SIM')
    else
    write('NAO');
end.