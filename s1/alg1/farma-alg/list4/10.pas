program e10;
var n, i, soma, resultado: longint;

begin
    read (n);
    resultado := 0;
    i := 1;
    soma := i * (i + 1) * (i + 2);

    while (soma <= n) do
    begin
        if (soma - n = 0) then
            resultado := 1;
            // writeln (soma, ' = ', n);
        i := i + 1;
        soma := i * (i + 1) * (i + 2);
    end;
    writeln (resultado);
end.