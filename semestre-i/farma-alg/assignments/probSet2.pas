program probSet2;
type matriz = array [1..100, 1..100] of longint;

procedure verifica_quadrados(n: longint; var m: matriz);
var i, j, j_aux, soma, soma_ant, maior, maior_index: longint;
begin
    maior := 0;
    maior_index := 1;
    j_aux := 2;
    soma := 0;
    i := 1;
    j := 2;
    while (n > 2) do
    begin
        while (j <= n) do
        begin
            soma := soma + m[i, j];
            j := j + 1;
        end;
        j := j_aux;
        while (j <= n) do
        begin
            soma := soma + m[j, n];
            j := j + 1;
        end;
        j := j_aux;
        while (j <= n) do
        begin
            soma := soma + m[n, n - (j - i)];
            j := j + 1;
        end;
        j := j_aux;

        while (j <= n) do
        begin
            soma := soma + m[n - (j - i), i];
            j := j + 1;
        end;
        j_aux := j_aux + 1;
        j := j_aux;

        if (maior < soma) then
        begin
            maior := soma;
            maior_index := i;
        end;

        writeln('soma do quadrado ', i, ' :', soma);

        soma := 0;
        n := n - 1;
        i := i + 1;
    end;
    writeln('maior quadrado: ', maior_index);
end;

procedure ler_matriz(n: longint; var m: matriz);
var i, j: longint;
begin
    i := 1;
    j := 1;
    while (i <= n) do
    begin
        while (j <= n) do
        begin
            read (m[i, j]);
            j := j + 1;
        end;
        j := 1;
        i := i + 1;
    end;
end;

var n: longint;
    m: matriz;
begin
    read (n);

    ler_matriz(n, m);
    verifica_quadrados(n, m);
end.