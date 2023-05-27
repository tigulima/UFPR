program e30;

var cod, quant: longint;

begin
    read(cod, quant);

    if (cod = 1001) then
        write(quant * 5.32:0:2)
    else if (cod = 1324) then
        write(quant * 6.45:0:2)
    else if (cod = 6548) then
        write(quant * 2.37:0:2)
    else if (cod = 987) then
        write(quant * 5.32:0:2)
    else if (cod = 7623) then
        write(quant * 6.45:0:2)
    else
        write('ERRO');
end.