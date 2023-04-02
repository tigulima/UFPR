program e25;

var dia, mes, ano, idade: longint;

begin
    read(dia, mes, ano);

    idade := 2020 - ano;

    if (mes < 4) then
        idade := idade + 1;
    if (mes = 4) then
    begin
        if (dia <= 29) then
            idade := idade + 1;
    end;

    write(idade);
end.