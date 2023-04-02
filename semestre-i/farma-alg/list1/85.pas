program e85;

var radius: real;

begin
    read(radius);
    radius := radius / 2;
    write((((4 * 3.14) / 3) * (radius * radius * radius)):0:2);
end.