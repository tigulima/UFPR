program prova01_ex02;

var n, i, sinal, num, divd, aux_divd: longint;
    x, soma: longint;

begin
    read (n, x);
    i := 0;
    sinal := -1;
    soma := 0;
    divd := 1;

    while (i < n) do
    begin
        num := (x * ((i mod 2) + 1));

        aux_divd := (i mod 2) + 1;
        if (i mod 4 = 0) then
            aux_divd := aux_divd + 2;
        while (aux_divd > 1) do
        begin
            divd := (aux_divd - 1) * divd;
            aux_divd := aux_divd - 1;
        end;

        sinal := sinal * -1;
        soma := soma + ((num div divd) * sinal);
        writeln (soma, ' ', x, ' * ', ((i mod 2) + 1), ' / ', divd, ' ', sinal);
        i := i + 1;
    end;
    writeln (soma);
end.