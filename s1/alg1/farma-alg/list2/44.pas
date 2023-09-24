program e44;

var n, m ,p, soma: longint;

begin
    read(n, m, p);
    soma := 0;

    while (n <= m) do
    begin
        soma := n + soma;
        n := n + p;
    end;

    write(soma)
end.