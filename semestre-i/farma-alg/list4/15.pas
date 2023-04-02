program e15;
var a, b, m, x, sum: longint;

begin
  read (a);
  b := a;
  x := a * 37;
  m := 10;

  while (m <= x * 10) do
    begin
      a := (x div m) * m;
      a := x - a;
      a := a div (m div 10);
      m := m * 10;

      sum := sum + a
    end;

  if (sum = b) then
    writeln ('SIM');
  if (sum <> b) then
    writeln ('NAO');
end.