program e04;
var a, b, i, x, y, sum, par, parb: real;

begin
    i := 1;
    a := 1;
    b := 2;
    sum := 0;
    par := 0;
    parb := 0;

    while (i < 10) do
    begin
        If (par = 1) and (parb = 1) then
        begin
            y := b + 1;
            x := y + 1;
            par := 0;
        end;
        if (par = 0) and (parb = 0) then
        begin
            x := b + 1;
            y := x + 1;
            par := 1;
        end;

        sum := sum + y / x;

        a := a + 2;
        b := b + 2;
        parb := par;
        i := i + 1;
    end;

    writeln (sum + 1/2 :0:2);
end.