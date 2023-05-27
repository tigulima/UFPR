program e03;
type matriz = array [1..100, 1..100] of longint;

function varredura(m, n, i, j, x: LongInt; var mat: matriz): Boolean;
begin
    varredura := true;
    if (i <> n) and (j <> m) then
    begin
        if (j = m) then
        begin
            i := i + 1;
            j := 1;
        end
        else
            j := j + 1;

        while (i <= n) do
        begin
            while (j <= m) do
            begin
                writeln ('casa: ', i, ', ', j, ' | ', mat[i, j], ' = ', x);
                if (mat[i, j] = x) then
                begin
                    varredura := false;
                    i := n;
                    j := m;
                end;
                j := j + 1;
            end;
            j := 1;
            i := i + 1;
        end;
    end;
end;

function procura_valor(m, n: longint; var mat: matriz): Boolean;
var i, j: LongInt;
begin
    procura_valor := true;
    i := 1;
    j := 1;
    while (i <= n) do
    begin
        while (j <= m) do
        begin
            if (not varredura(n, m, i, j, mat[i, j], mat)) then
            begin
                procura_valor := false;
                i := n;
                j := m;
            end;
            j := j + 1;
        end;
        j := 1;
        i := i + 1;
    end;
end;

procedure ler_matriz(m, n: longint; var mat: matriz);
var i, j: LongInt;
begin
    i := 1;
    j := 1;
    while (i <= n) do
    begin
        while (j <= m) do
        begin
            read(mat[i, j]);
            j := j + 1;
        end;
        j := 1;
        i := i + 1;
    end;
end;

var m, n: LongInt;
    mat: matriz;
begin
    read (m, n);

    ler_matriz(m, n, mat);

    if (procura_valor(m, n, mat)) then
        writeln('nao')
    else 
        writeln('sim');
end.