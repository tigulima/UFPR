program e02;
type matriz = array [1..100, 1..100] of longint;

// Elementos Nulos

procedure ver_nulos_coluna(m, n: longint; var mat: matriz);
var i, j, colunas, verificador: longint;
begin
    verificador := 0;
    colunas := 0;
    i := 1;
    j := 1;
    while (j <= m) do
    begin
        while (i <= n) and (mat[i, j] = 0) do
        begin
            verificador := verificador + 1;
            i := i + 1;
        end;

        if (verificador = n) then
            colunas := colunas + 1;

        verificador := 0;
        j := j + 1;
        i := 1;
    end;
    writeln('colunas: ', colunas);
end;

procedure ver_nulos_linha(m, n: longint; var mat: matriz);
var i, j, linhas, verificador: longint;
begin
    verificador := 0;
    linhas := 0;
    i := 1;
    j := 1;
    while (i <= n) do
    begin
        while (j <= m) and (mat[i, j] = 0) do
        begin
            verificador := verificador + 1;
            j := j + 1;
        end;

        if (verificador = m) then
            linhas := linhas + 1;

        verificador := 0;
        i := i + 1;
        j := 1;
    end;
    writeln('linhas: ', linhas);
end;

procedure ler_matriz(m, n: longint; var mat: matriz);
var i, j, x: longint;
begin
    i := 1;
    j := 1;
    while (i <= n) do
    begin
        while (j <= m) do
        begin
            read (x);
            mat[i, j] := x;
            j := j + 1;
        end;
        j := 1;
        i := i + 1;
    end;
end;

var m, n: longint;
    mat: matriz;
begin
    read (m, n);

    ler_matriz(m, n, mat);
    ver_nulos_linha(m, n, mat);
    ver_nulos_coluna(m, n, mat);
end.