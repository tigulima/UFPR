program e11;
var a, i, x: longint;

begin
  read (a);
  i := a - 1;
  x := 0;

  while (i > 1) Do
    begin
      if (a mod i = 0) then
        x := 1;

      i := i - 1;
    end;

  if (x = 1) or (a = 0) then
    writeln ('NAO');
  if (x = 0) and (a <> 0) then
    writeln ('SIM');
end.