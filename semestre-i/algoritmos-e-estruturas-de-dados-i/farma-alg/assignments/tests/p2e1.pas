program p2e1;
type matriz = array [1..1024, 1..1024] of longint;

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

procedure escreve_matriz(n: longint; var m: matriz);
var i, j: longint;
begin
    i := 1;
    j := 1;
    while (i <= n) do
    begin
        while (j <= n) do
        begin
            write(m[i, j], ' ');
            j := j + 1;
        end;
        writeln('');
        j := 1;
        i := i + 1;
    end;
end;

procedure max_pooling(n: longint; var m: matriz);
var i, j, x, y, maior: longint;
    m_nova: matriz;
begin
    i := 1;
    j := 1;
    x := 1;
    y := 1;
    while (i <= n) do
    begin
        while (j <= n) do
        begin
            maior := m[i, j];

            if (maior < m[i, j + 1]) then
                maior := m[i, j + 1];
            if (maior < m[i + 1, j]) then
                maior := m[i + 1, j];
            if (maior < m[i + 1, j + 1]) then
                maior := m[i + 1, j + 1];

            m_nova[x, y] := maior;
            if (y < n div 2) then
                y := y + 1
            else
            begin
                y := 1;
                x := x + 1
            end;
            j := j + 2;
        end;
        j := 1;
        i := i + 2;
    end;
    escreve_matriz(n div 2, m_nova);
end;

procedure avg_pooling(n: longint; var m: matriz);
var i, j, x, y, media: longint;
    m_nova: matriz;
begin
    i := 1;
    j := 1;
    x := 1;
    y := 1;
    while (i <= n) do
    begin
        while (j <= n) do
        begin
            media := (m[i, j] + m[i, j + 1] + m[i + 1, j] + m[i + 1, j + 1]) div 4;

            m_nova[x, y] := media;
            if (y < n div 2) then
                y := y + 1
            else
            begin
                y := 1;
                x := x + 1
            end;
            j := j + 2;
        end;
        j := 1;
        i := i + 2;
    end;
    escreve_matriz(n div 2, m_nova);
end;

var n, operacao: longint;
    m: matriz;
begin
    read(n, operacao);

    ler_matriz(n, m);

    if (operacao = 1) then
        max_pooling(n, m)
    else
        avg_pooling(n, m);
end.