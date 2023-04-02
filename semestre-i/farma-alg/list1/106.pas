program e106;

var num: longint;

begin
    read(num);

    if (num >= 0) then
        write(num * num * num)
    else
        write(num * num);
end.