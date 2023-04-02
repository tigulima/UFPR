program e53;

var x, n, fat: longint;

begin
    read (x);
    fat := 1;
    n := 1;

    while (fat <= x) do
    begin
        fat := fat * n;
        n := n + 1;
    end;
    writeln (n - 1);
end.