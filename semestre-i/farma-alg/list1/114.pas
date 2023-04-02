program e114;

var num: longint;

begin
    read(num);

    if (num mod 5 = 0) then
        write('SIM')
    else
        write('NAO');
end.