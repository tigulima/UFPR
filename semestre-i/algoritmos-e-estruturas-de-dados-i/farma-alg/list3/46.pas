program e46;

var i, n, p, media: real;

begin
    read (n, p);
    i := 0;
    while (n <> 0) and (p <> 0) do
    begin
        media := media + (n * p);
        i := i + p;
        read (n, p);
    end;
    writeln (media / i:0:2);
end.