program probSet1;
var i, n: integer;

begin
    n := 0;
    i := 1;
    while i <= 9 do
    begin
        writeln(i);
        i := i + 1;
    end;

    i := 1;
    while i <= 9 do
    begin
        writeln(i * 11);
        i := i + 1;
    end;

    i := 1;
    while i <= 9 do
    begin
        while n < 10 do
        begin
            writeln(i*100+n*10+i);
            n := n + 1;
        end;
        n := 0;
        i := i + 1;
    end;
end.