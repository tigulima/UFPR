program e03;
var a, b, i, dif: longint;

begin
  read (a);
  dif := 1;
  i := 0;

  while (a <> 0) do
    begin
      if (a <> b * b) and (i mod 2 <> 0) then
        dif := 0;

      b := a;
      i := i + 1;
      read (a);
    end;

  writeln (dif)
end.