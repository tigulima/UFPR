program e07;
var n: longint;

function sum (n :longint) : longint;
begin
    n := n + 1;
    sum := n;
end;

begin
    n := 1;
    while n <= 10 Do
    begin
        writeln (n);
        n := sum (n);
    end;
end.