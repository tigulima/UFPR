program e40;

var n, max, min: longint;

begin
    read(n);
    max := n;
    min := n;

    while (n <> 0) do
    begin
        if (n > max) then
            max := n
        else if (n < min) then
            min := n;

        read(n);
    end;
    write(max, ' ', min);
end.