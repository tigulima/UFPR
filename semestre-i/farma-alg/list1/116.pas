program e116;

var num: longint;

begin
    read(num);

    if ((num mod 2 <> 0) and (num < -20)) or ((num mod 2 = 0) and (num > 7)) then
        write('SIM')
    else
        write('NAO');
end.