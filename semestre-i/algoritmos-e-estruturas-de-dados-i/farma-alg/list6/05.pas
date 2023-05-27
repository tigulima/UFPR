program e06;
var angulo: real;

(* coloque aqui o codigo da sua funcao que calcula o seno *)
function calcula_seno(params):integer;
begin
    
end;
(* coloque aqui o codigo da sua funcao que calcula o cosseno *)
function calcula_cosseno(params):integer;
begin
    
end;
(* coloque aqui o codigo da sua funcao que calcula a tangente *)
function existe_tangente(angulo, tg):boolean;
begin
    
end;

begin
    read (angulo);
    if existe_tangente(angulo, tg) then
        writeln (tg:0:5)
    else
        writeln ('nao existe tangente de ',angulo:0:5);
end.