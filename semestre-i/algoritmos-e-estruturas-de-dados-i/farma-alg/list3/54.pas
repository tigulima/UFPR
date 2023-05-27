program e54;

var i, n, aux: longint;
    verif : boolean;

begin
    read (n);
    verif := true;
    aux := n;

    while (n <> 0) do
    begin
        if (aux <> n) then
            verif := false;

        aux := n;
        i := i + 1;
        read (n)
    end; 
    if (verif) and (i >= 3) then
        writeln('SIM')
    else
        writeln('NAO')
end.