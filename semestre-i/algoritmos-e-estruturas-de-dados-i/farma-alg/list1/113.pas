program e113;

var salario, prestacao: longint;

begin
    read(salario, prestacao);

    if (prestacao <= salario * 30 div 100) then
        write('SIM')
    else
        write('NAO');
end.