program e22;

var x, y, quadrante: longint;

begin
    read(x, y);

    if (x = 0) and (y = 0) then
        write('O')
    else if (x = 0) then
        write('Y')
    else if (y = 0) then
        write('X')
    else if (x > 0) and (y > 0) then
        write(1)
    else if (x < 0) and (y > 0) then
        write(2)
    else if (x < 0) and (y < 0) then
        write(3)
    else if (x > 0) and (y < 0) then
        write(4);
end.