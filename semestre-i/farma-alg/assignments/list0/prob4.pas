program prob4;

var a, aux, count : LongInt;

begin
	read (a);
	aux := 0;

	while (a <> 0) do
	begin
		if (aux <> a) then
			count := count + 1;
		aux := a;
		read (a);
	end;
	writeln(count);
end.