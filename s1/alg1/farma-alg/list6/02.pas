program e02;
var x: real;
    bin: boolean;

function bin_tf (x:real): boolean;
var m, a : real;
    is_bin: boolean;
begin
    is_bin := true;
    m := 10;

    while (m < x * 10) do
        begin
        a := round(x / m) * m;
        a := round((x - a) / (m / 10));

        if (a <> 0) and (a <> 1) then
            is_bin := false;

        m := m * 10;
        end;

    bin_tf := is_bin;
end;

begin
    read (x);

    bin := bin_tf(x);

    if (bin) then
        writeln ('sim')
    else
        writeln ('nao');
end.