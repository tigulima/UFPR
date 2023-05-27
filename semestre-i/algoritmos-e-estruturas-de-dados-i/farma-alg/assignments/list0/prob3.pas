program prob3;

var a, count, aux : LongInt;

begin
	write ('Digitem um numero: ');
	read (a);

	while (a <= 0) do
	begin
		write ('O numero deve ser maior que 0: ');
		read (a);
	end;

	aux := a mod 10;
	while (a > 0) do
	begin
		if (a mod 10 = aux) then
			count := count + 1; 
		a := a div 10;
	end;
	writeln(count);
end.