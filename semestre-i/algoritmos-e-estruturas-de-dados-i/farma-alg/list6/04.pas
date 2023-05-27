program e04;
var i : longint;

function primo (x:longint) : boolean;
var i : longint;
    isPrimo : boolean;

begin
    i := 2;
    isPrimo := true;

    while (i < x) do
    begin
        if (x mod i = 0) then
        isPrimo := false;

        i := i + 1;
    end;

    primo := isPrimo;
end;

begin
    for i:= 1 to 10000 do
    if primo(i) then
        writeln (i);
end.