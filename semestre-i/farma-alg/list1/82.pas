program e82;

var segundos, minutos, horas: longint;

begin
    horas := 0;
    minutos := 0;
    read(segundos);

    if (segundos >= 3600) then
    horas := segundos div 3600;

    minutos := (segundos mod 3600) div 60;
    segundos := (segundos mod 3600) mod 60;

    write(horas, ':', minutos, ':', segundos);
end.