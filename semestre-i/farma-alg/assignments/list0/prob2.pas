program prob2;
// const MAX = 100;
var count, a, b, a_aux, b_aux : Integer;

begin
	a := 2;
	b := 2;
	count := 0;

	// Testando todo A
	while (a <= 100) do
	begin
		// Testando todo B
		while (b <= 100) do
		begin
			// Testando se são primos entre si
			a_aux := a;
			b_aux := b;
			while (a_aux <> 0) and (b_aux <> 0) do
			begin
				if (a_aux > b_aux) then
					a_aux := a_aux mod b_aux
				else
					b_aux := b_aux mod a_aux;
			end;

			if (a_aux = 0) and (b_aux = 1) then
			begin
				count := count + 1;
				writeln(a, ' ', b);
			end;

			b := b + 1;
		end;
		a := a + 1;
		b := 2;
	end;

	writeln('Existem ', count,' pares de primos entre si neste intervalo');
end.