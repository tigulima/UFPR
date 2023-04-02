program e109;

var num: longint;

begin
    read(num);

    if (num > -15) and (num < 30) then
        write(num * -1)
    else
        write(num);
end.