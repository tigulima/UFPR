program prob1;

var a, b : Integer;

begin
	read (a, b);
  while (a <> 0) and (b <> 0) do
  begin
    if (a > b) then
			a := a mod b
		else
			b := b mod a;
  end;

	if (a = 0) and (b = 1) then
		write('Sao primos entre si')
	else
		write('nao sao primos...');
end.