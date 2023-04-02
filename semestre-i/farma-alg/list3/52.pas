program e52;

var i, m, n, media : longint;

begin
    read (m);
    i := 0;
    media := 0;

    while (i < m) do
    begin
        read (n);

        media := media + n;
        i := i + 1;
    end;
    writeln (media div m);
end.