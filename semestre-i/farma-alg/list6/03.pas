program e03;
var bin, conv: real;

function bin_dec (bin:real): real;
var bin_aux, res, soma : real;
begin
    soma := 0;
    res := 1;

    while (bin > 0) do
    begin
        bin_aux := bin;
        bin := round(bin / 10);
        bin_aux := bin_aux - (bin * 10);

        if (bin_aux = 1) then
            soma := soma + res;

        res := res * 2;
    end;
    bin_dec := soma;
end;

begin
    read (bin);
    conv := bin_dec(bin);
    writeln (conv:0:0);
end.