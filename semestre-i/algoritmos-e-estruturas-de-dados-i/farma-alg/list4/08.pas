program e08;
var i, n, n_ant, soma: real;

begin
    read (n_ant, n);
    i := 2;
    soma := n_ant;

    while ((n * 2) <> n_ant) and ((n / 2) <> n_ant) do
    begin
        soma := soma + n;
        i := i + 1;
        n_ant := n;
        read (n);
    end;
    writeln(i:0:0, ' ', soma + n:0:0, ' ', n_ant:0:0, ' ', n:0:0);
end.