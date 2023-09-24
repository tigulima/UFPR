program e32;

var salario, codigo: real;

begin
    read(salario, codigo);

    if (codigo = 101) then
        write(salario:0:2, ^M^J, salario * 1.1:0:2, ^M^J, salario * 0.1:0:2)
    else if (codigo = 102) then
        write(salario:0:2, ^M^J, salario * 1.2:0:2, ^M^J, salario * 0.2:0:2)
    else if (codigo = 103) then
        write(salario:0:2, ^M^J, salario * 1.3:0:2, ^M^J, salario * 0.3:0:2)
    else
        write(salario:0:2, ^M^J, salario * 1.4:0:2, ^M^J, salario * 0.4:0:2);

end.