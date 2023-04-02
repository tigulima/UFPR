program e111;

var num: longint;

begin
    read(num);

    if (num mod 3 = 0) and (num mod 7 = 0) then
        write('SIM')
    else
        write('NAO');
end.