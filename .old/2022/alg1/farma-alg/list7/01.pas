program e01;
type vetor = array [1..200] of real;

procedure soma_vetor(n: longint; var v: vetor; var nume, divi: real);
var i: longint;
begin
    i := 1;
    while (i <= n) do
    begin

        if (i mod 2 = 0) and (v[i] > 0) then
            nume := nume + v[i]
        else if (i mod 2 <> 0) and (v[i] < 0) then
            divi := divi + v[i];
        i := i + 1;
    end;
end;

procedure ler_vetor(n: longint; var v: vetor);
var i: longint;
    x: real;
begin
    i := 1;
    while (i <= n) do
    begin
        read (x);
        v[i] := x;
        i := i + 1;
    end;

end;

var numerador, dividendo: real;
    n: longint;
    v: vetor;
begin
    read (n);
    numerador := 0;
    dividendo := 0;

    ler_vetor(n, v);
    soma_vetor(n, v, numerador, dividendo);

    if (n = 0) then
        writeln('vetor vazio')
    else if (dividendo = 0) then
        writeln('divisao por zero')
    else
        writeln(numerador/dividendo:0:2);
end.