program e112;

var num: longint;

begin
    read(num);

    if (num mod 2 = 0) then
        write('PAR')
    else
        write('IMPAR');
end.