program e101;

var num: longint;

begin
    read(num);
    write(num mod 10, num div 10 mod 10, num div 100);
end.