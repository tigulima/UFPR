program e18;

var codigo, quant: real;

begin
    read(codigo, quant);

    if (codigo = 100) then
        write(quant * 1.2:0:2)
    else if (codigo = 101) then
        write(quant * 1.3:0:2)
    else if (codigo = 102) then
        write(quant * 1.5:0:2)
    else if (codigo = 103) then
        write(quant * 1.2:0:2)
    else if (codigo = 104) then
        write(quant * 1.3:0:2)
    else if (codigo = 105) then
        write(quant:0:2)
end.