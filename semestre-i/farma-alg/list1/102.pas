program e102;

var num, centena, decimal, unitario, soma: longint;

begin
    read(num);
    centena := num div 100;
    decimal := num div 10 mod 10;
    unitario := num mod 10;
    soma := (centena + (3 * decimal) + (5 * unitario)) mod 7;
    num := num * 10 + soma;
    write(num);
end.