program e103;

var coss, dist, hip: real;

begin
    read(coss, dist);
    hip:= dist / coss;
    write(sqrt((hip * hip) - (dist * dist)):0:3);
end.