program e07;
var c, l: longint ;

begin
    read (c, l);

    if ((c mod 2 = 0) and (l mod 2 = 0) or (c mod 2 <> 0) and (l mod 2 <> 0)) then
        writeln ('BRANCA')
    else
        writeln ('PRETA')
end.