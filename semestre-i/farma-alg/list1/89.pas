program e89;

var custoFab, distribuidor, impostos: longint;

begin
    read(custoFab);
    distribuidor := custoFab * 28 div 100;
    impostos := custoFab * 45 div 100;
    write(custoFab + distribuidor + impostos);
end.