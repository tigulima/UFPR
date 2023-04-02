program e08;
var antigo, atual: real;

function percent (old, new :real) : real;
var res : real;
begin
    res := new;
    res := (res / old) - 1 ;
    percent := res;
end;

begin
    read (antigo, atual);
    while (antigo <> 0) or (atual <> 0) do
    begin
        writeln (percent (antigo, atual): 0: 2);
        read (antigo, atual);
    end;
end.