program e55;

var n, m, i : longint;

begin
    read (n, m);
    i := 0;

    while (m > 0) do
    begin
        if (m mod 10 = n) then
            i := i + 1;
        m := m div 10;
    end;
    if (i = 0) then
        writeln ('NAO')
    else
        writeln (i);
end.