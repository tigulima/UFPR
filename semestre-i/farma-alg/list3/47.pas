program e47;

const max = 50;
var i, soma : longint;

begin
    i := 1;
    soma := 0;
    while (i <= max) do
    begin
        soma := soma + i * i;
        i := i + 1;
    end;
    writeln(soma);
end.