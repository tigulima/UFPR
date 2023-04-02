program e48;

var a, b, mult : longint;

begin
    read (a, b);
    mult := a;

    while (a < b) do
    begin
        a := a + 2;
        mult := mult * a;
    end;
    writeln(mult);
end.