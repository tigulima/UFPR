program e17;

var n, invert, aux: longint;

begin
    read(n);
    aux := n;

    while (aux <> 0) do
    begin
        invert := (aux mod 10 + invert * 10);
        aux := (aux div 10);
    end;

    if (n = invert) then
        write('SIM')
    else
        write('NAO');
end.