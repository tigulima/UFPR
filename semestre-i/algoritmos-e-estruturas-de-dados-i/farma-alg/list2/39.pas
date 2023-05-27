program e39;

var soma, n, m, i: longint;

begin
    read(n);
    i := 0;
    m := 2;
    soma := 1;
    
    while (i < n) do
    begin
        soma := soma * m;
        m := m + 2;
        i := i + 1;
    end;

    write(soma);
end.