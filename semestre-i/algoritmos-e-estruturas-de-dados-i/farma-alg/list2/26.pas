program e26;

var area: longint;

begin
    read(area);

    if (area <= 6) then
        write(100)
    else
        write(80 + (15 * (area - 3)))
end.