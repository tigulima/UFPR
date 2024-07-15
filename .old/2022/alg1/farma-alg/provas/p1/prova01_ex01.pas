program prova01_ex01;

var n, maiores, menores, iguais, num_dir, num_esq: longint;

begin
    read (n);
    maiores := 0;
    menores := 0;
    iguais := 0;


    while (n <> 0) do
    begin
        while (n > 10) do
        begin
            num_dir := n mod 10;
            n := n div 10;
            num_esq := n mod 10;
            
            if (num_esq < num_dir) then
                maiores := maiores + 1
            else if (num_esq > num_dir) then
                menores := menores + 1
            else
                iguais := iguais + 1;
        end;
        writeln (maiores, ' ', menores, ' ', iguais);
        read (n);
    end;
end.