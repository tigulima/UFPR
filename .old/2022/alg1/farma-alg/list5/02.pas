program e02;
var a, b, i, x, sum: real;

begin
  read (x);
  i := 1;

  while (i < x) do
    begin
      a := i;
      b := x - i;

      sum := (a / b) + sum;
      i := i + 1;
    end;

  writeln (sum :0:2);
end.