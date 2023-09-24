program e49;

const SAL_MINIMO = 450;
var i, gpA, gpB, gpC, gpD, salario : real;

begin
    read (salario);
    i := 0;
    gpA := 0;
    gpB := 0;
    gpC := 0;
    gpD := 0;

    while (salario <> 0) do
    begin
        if (salario <= 3 * SAL_MINIMO) then
          gpA := gpA + 1
        else if (salario <= 9 * SAL_MINIMO) then
          gpB := gpB + 1
        else if (salario <= 20  * SAL_MINIMO) then
          gpC := gpC + 1
        else
          gpD := gpD + 1;
        i := i + 1;
        read (salario);
    end;
    writeln ((gpA / i)*100:0:2);
    writeln ((gpB / i)*100:0:2);
    writeln ((gpC / i)*100:0:2);
    writeln ((gpD / i)*100:0:2);
end.
