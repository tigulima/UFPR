program e01;
type matriz = array [1..100, 1..100] of longint;

// Matriz Triangular

function verifica_inf(n: longint; var m: matriz): boolean;
var i, j: longint;
begin
    verifica_inf := true;
    i := 1;
    j := 2;
    while (i < n) do
    begin
        while (j < n) do
        begin
            if (m[i, j] <> 0) then
            begin
                verifica_inf := false;
                i := n;
                j := n;
            end;
            j := j + 1;
        end;
        i := i + 1;
        j := i + 1;
    end;
end;

function verifica_sup(n: longint; var m: matriz): boolean;
var i, j: longint;
begin
    verifica_sup := true;
    i := 2;
    j := 1;
    while (i < n) do
    begin
        while (j < i) do
        begin
            if (m[i, j] <> 0) then
            begin
                verifica_sup := false;
                i := n;
                j := n;
            end;
            j := j + 1;
        end;
        i := i + 1;
        j := 1;
    end;
end;

procedure ler_matriz(n: longint; var m: matriz);
var i, j, x: longint;
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

    if (verifica_inf(n, m)) then
        write('sim')
    else if (verifica_sup(n, m)) then
        write('sim')
    else
        write('nao');
end.