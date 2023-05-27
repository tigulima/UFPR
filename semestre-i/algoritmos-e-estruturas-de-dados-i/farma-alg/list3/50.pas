program e50;

var a, b, i : longint;

begin
    read (a, b);
    i := 0;

    while (a mod b = 0) do
    begin
        a := a div b;
        i := i + 1;
    end;
    writeln (i);
end.