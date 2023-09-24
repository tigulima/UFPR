program e09;
var  pa, pb, ta, tb, pmin, tmin, pmax, tmax, i, x: real;

begin
    read (pa, pb, ta, tb);
    i := 0;

    if (pa <= pb) and (ta > tb) then
    begin
        pmin := pa;
        tmin := ta;
        pmax := pb;
        tmax := tb;
        x := 1;
    end;

    if (pb <= pa) and (tb > ta) then
    begin
        pmin := pb;
        tmin := tb;
        pmax := pa;
        tmax := ta;
        x := 1;
    end;

    while (x = 1) And (pmin < pmax) do
    begin
        pmin := pmin + pmin * tmin;
        pmax := pmax + pmax * tmax;
        i := i + 1;
    end;
    writeln (i :0:0);
end.