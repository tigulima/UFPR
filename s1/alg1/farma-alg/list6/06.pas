program e06;
var dia1, mes1, ano1, dia2, mes2, ano2: longint;

function data (dia1, mes1, ano1, dia2, mes2, ano2 :longint) : boolean;
var data1, data2 : longint;
    tf : boolean;
begin
    tf := false;

    data1 := dia1 + (mes1 * 30) + (ano1 * 360);
    data2 := dia2 + (mes2 * 30) + (ano2 * 360);

    if (data1 < data2) then
        tf := true;

    data := tf;
end;

begin
    Read (dia1, mes1, ano1, dia2, mes2, ano2);

    if data (dia1, mes1, ano1, dia2, mes2, ano2) then
        writeln ('a primeira data eh anterior')
    else
        writeln ('a primeira data nao eh anterior');
end.