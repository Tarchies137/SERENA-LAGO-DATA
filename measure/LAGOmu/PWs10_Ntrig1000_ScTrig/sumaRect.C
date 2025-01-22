/*
Obtiene el área usndo método de rectángulos para un evento.

Se debe cargar con 

root[] .L sumaRect.C


*/


Float_t sumaRect(Float_t *tt, Float_t *vv)
{
	Float_t sR=0;
	Float_t dt = (tt[1023]-tt[0])/1023;
	for(int k=0; k<=1023;k++)
		{ sR += vv[k];// equivale a sR = sR+vv[k];
	}
sR = sR*dt;
return sR; //return(sR)
} 
