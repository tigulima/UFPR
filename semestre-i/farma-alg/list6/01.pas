program e01;
var n,m: longint;

function contrario (n, m :longint) : boolean;
var res : boolean;
    m_aux, m_contrario: longint;
begin
    res := true;
    m_contrario := 0;

    while (m > 0) do
    begin
        m_aux := m mod 10;
        m_contrario := m_contrario * 10 + m_aux;
        m := m div 10;
    end;

    if n <> m_contrario then
    begin
        res := false;
    end;

    contrario := res;
end;

begin
    read (n,m);
    if contrario (n,m) then
        writeln (n,' eh o contrario de ',m)
    else
        writeln (n,' nao eh o contrario de ',m);
end.