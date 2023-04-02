program e41;

var i, n, ultimo, penultimo, soma, fib: longint;

begin
    read(n);
    i := 1;
    fib := 0;
    soma := 0;
    ultimo := 0;
    penultimo := 0;
    
    while (i < n) do
    begin
        if ( penultimo = 0) then
        begin
            fib := 1;
            penultimo := ultimo;
            ultimo := fib;
        end
        else
        begin
            fib := penultimo + ultimo;
            penultimo := ultimo;
            ultimo := fib;
        end;
        soma := soma + fib;
        i := i + 1;
    end;
    write(soma);
end.