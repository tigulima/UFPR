program e29;

var i: longint;
    a, b, c, max, med, min, first, last: real;

begin
    read(i, a, b, c);
    max := a;
    med := b;
    min := c;

    if (a > b) and (a > c) then
    begin
        first := b;
        last := c;

        if (b > c) then
        begin
            med := b;
            min := c;
        end
        else if (c > b) then
        begin
            med := c;
            min := b;
        end;
    end
    else if (b > a) then
    begin

        first := a;
        last := c;

        max := b;
        if (a > c) then
        begin
            med := a;
            min := c;
        end
        else if (c > a) then
        begin
            med := c;
            min := a;
        end;
    end;

    if (c > a) then
    begin

        first := a;
        last := b;

        max := c;
        if (a > b) then
        begin
            med := a;
            min := b;
        end
        else if (b > a) then
        begin
            med := b;
            min := a;
        end;
    end;

    if (i = 1) then
        write(min:0:0, ' ', med:0:0, ' ', max:0:0)
    else if (i = 2) then
        write(max:0:0, ' ', med:0:0, ' ', min:0:0)
    else if (i = 3) then
        write(first:0:0, ' ', max:0:0, ' ', last:0:0);

end.