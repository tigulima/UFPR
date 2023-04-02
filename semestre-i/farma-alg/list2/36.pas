program e36;

var tipo, area: real;

begin
    read(tipo, area);

    if (tipo = 1) then
        write(round(area / 2 + 0.4), ' caixas')
    else if (tipo = 2) then
        write(round(area / 3 + 0.4), ' caixas')
    else if (tipo = 3) then
        write(round(area / 4 + 0.4), ' caixas')
end.