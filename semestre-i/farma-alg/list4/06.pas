program e06;
var 
  x, i, o, a, m: longint;
  n: array[1..100] of integer;
  
begin
  read (x);
  m := 0;
  o := 1;
  i := 1;
  while (m < x) do
    begin
      o := 1;
      a := 0;
      while (o < i) do
        begin
          if (i mod o = 0) then
            a := a + o;
          o := o + 1;
        end;
      if (a = i) then
        begin
          n[m] := a;
          m := m + 1;
        end;
      i := i + 1;
    end;
  i := 0;
  while (i < m) do
    begin
      write(n[i], ' ');
      i := i + 1;
    end;
end.