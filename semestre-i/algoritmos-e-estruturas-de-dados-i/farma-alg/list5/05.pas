program e05;
var a, b, i, x, y, sum : real;

begin
    i := 0;
    sum := 0;
    x := 1;
    y := 3;

    while (i < 10) do
    begin
        a := y * 2;
        b := x * 2;

        x := a;
        y := b;

        sum := sum + x / y;

        i := i + 1;
    end;

    writeln (sum :0:2);
end.