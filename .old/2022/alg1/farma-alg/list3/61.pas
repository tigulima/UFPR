program e61;

var i, num : longint;

begin
    read (num);
    i := 1;

    while (i < num) do
    begin
        writeln (i, ' ', num - i);
        i := i + 1;
    end;
end.