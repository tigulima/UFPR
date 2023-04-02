program prob5;

var i, x, fat, sinal, termoA, termoB, resultado : real;
		a : LongInt;

begin
	read (x);
	a := 5;
	fat := 2 * 1;

	termoA := (a * x) / fat;

	sinal := 1;
	i := 0;
	while (abs(termoA - termoB) >= 0.0000001) and (i < 100) do
	begin
		if (a mod 2 <> 0) then
			a := a + 1
		else
			a := a + 5;
			
		x := x * x;
		fat := fat * (i + 3);

		termoB := termoA;
		termoA := (a * x) / fat;

		resultado := termoB + (termoA * sinal);

		sinal := sinal * -1;
		i := i + 1;
	end;
	writeln (resultado:0:20);
end.