program e13;
var a, b, c: longint;

begin
  read (a, b, c);

  if (b mod a = 0) and (c mod b = 0) then
    writeln (a + b + c)
  else if (b = a + 1) and (c = b + 1) then
         writeln (c, ' ', b, ' ', a)
  else
    writeln ((a+b+c) div 3);
end.