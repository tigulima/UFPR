program e43;

var soma, n, m, i: longint;

begin
    read(n);
    i := 0;
    m := 1;
    soma := 0;
    
    while (i < n) do
    begin
        soma := soma + m;
        m := m + 2;
        i := i + 1;
    end;

    write(soma);
end.