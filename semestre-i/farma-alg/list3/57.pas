program e57;

var num, maior: longint;

begin
    read (num);
    maior := 0;

    while (num <> 0) do
    begin
        if (num mod 7 = 0) and (num > maior) then
            maior := num;
        read (num);
    end;
    writeln(maior);
end.