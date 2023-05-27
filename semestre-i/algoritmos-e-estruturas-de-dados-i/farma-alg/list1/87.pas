program e87;

var largura, altura, potencia: longint;

begin
    read(largura, altura);
    potencia := largura * altura * 18;
    write(largura * altura, ' ', potencia);
end.