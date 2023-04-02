program e01;
var a, b, i, x, sum, par, parb: real;

begin
  read (x);
  i := 0;
  sum := 0;
  par := 0;
  parb := 0;

  while (i < x) do
    begin
      a := 1000 - (i * 3);
      b := i + 1;

      if (par = 1) and (parb = 1) then
        begin
          sum := sum - (a / b);
          par := 0;
        end;
      if (par = 0) and (parb = 0) then
        begin
          sum := sum + (a / b);
          par := 1;
        end;

      parb := par;
      i := i + 1;
    end;

  writeln (sum :0:2);
end.