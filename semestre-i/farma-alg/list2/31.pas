program e31;

var saldo_medio: real;

begin
    read(saldo_medio);

    if (saldo_medio <= 200) then
        write(saldo_medio:0:0, ^M^J, 0)
    else if (saldo_medio <= 400) then 
        write(saldo_medio:0:0, ^M^J,'20%')
    else if (saldo_medio <= 600) then
        write(saldo_medio:0:0, ^M^J,'30%')
    else
        write(saldo_medio:0:0, ^M^J,'40%');
end.