program e03;
var a, b, i, x, y, sum: real;

begin
    i := 1;
    x := 1;
    y := 1;
    sum := 0;

    while (i < 5) do
    begin
        a := x;
        b := y;

        x := a + b;
        y := b + x;
  
        sum := (x / y) + sum;
        i := i + 1;
    end;

    writeln (sum + 1 :0:2);
end.