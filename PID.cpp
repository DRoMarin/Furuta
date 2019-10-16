/* Recuerde iniciar antes todas las variables en cero */
float ek = 0; //error
volatile float ik = 0; //accion integral y de memoria
volatile float dk = 0; //accion integral y de memoria
float KP = 1;
float KI = 1;
float KD = 1;
float acc = 0;
float mk = 0;   //accion de control
float posicion = 0;
float posicion1 = 0;
int16 salidapwm =0; //para la salida de pwm
#define REFERENCE  0
#define MAXINTEGRAL    4.7 //antiwindup de 4.7V
float ikl = 0;
while (true) { //es un placeholder



	/* Determina el error e inicia el c�lculo del regulador PI _D */
	ek = REFERENCE - posicion;

	/* Porci�n integral, ikl es la integral atrasada un periodo */
	ik = KI * ek + ikl;

	/* Porci�n derivada, posicion1 es la salida atrasada un periodo */
	dk = KD * (posicion - posicion1);

	/* Acci�n total de control, el signo negativo es para realimentaci�n negativa */
	acc = KP * ek + ik - dk;

	/* Escribe en el buffer mk del PWM que ser� actualizado sincr�nicamente */
	mk = acc;

	/* Guarda la salida para la siguiente vez */
	posicion1 = posicion;
	ikl = ik;
	/* Satura el t�rmino integral y lo guarda para la pr�xima vez */
	if (ik > MAXINTEGRAL)
		ikl = MAXINTEGRAL;
	else
		if (ik < -MAXINTEGRAL) ikl = -MAXINTEGRAL;
}