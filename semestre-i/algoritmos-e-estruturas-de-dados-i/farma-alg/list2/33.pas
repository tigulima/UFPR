program e33;

var lados, medida: longint;

begin
    read(lados, medida);

    if (lados = 3) then
        write('TRIANGULO', ' ', lados * medida)
    else if (lados = 4) then
        write('QUADRADO', ' ', medida * medida)
    else if (lados = 5) then
        write('PENTAGONO')
    else
        write('ERRO')
end.