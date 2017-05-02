#include "clock.h"
#include "lcd.h"
#include "evento.h"
typedef enum{CERRADO,ABIERTO,DENEGADO,CAMBIAR_HH,CAMBIAR_MM,CAMBIAR_SS,CAMBIAR_C} state;
state estadoActual;

#define CASO_NULO '~'

unsigned char is_num(unsigned char);
unsigned char construir_num(unsigned char,unsigned char);
void fCERRADO(void);
void fABIERTO(void);
void fDENEGADO(void);
void fCAMBIAR_HH(void);
void fCAMBIAR_MM(void);
void fCAMBIAR_SS(void);
void fCAMBIAR_C(void);


void (*MEF[])(void)={fCERRADO,fABIERTO,fDENEGADO,fCAMBIAR_HH,fCAMBIAR_MM,fCAMBIAR_SS,fCAMBIAR_C};
unsigned char key;

void init_MEF(void){
	key=CASO_NULO;
	estadoActual = CERRADO;
}

void update_MEF(void){
	(*MEF[estadoActual])();
}
unsigned char stringOut[16];
void fCERRADO(void){
	stringOut[0]='C';
	stringOut[1]='\0';
	if(cola_vacia()==0){
		key=pop_tecla();	
	}
	switch(key){
	case 'A':
		estadoActual=CAMBIAR_HH;
		break;
	case 'B':
		estadoActual=CAMBIAR_MM;
		break;
	case 'C':
		estadoActual=CAMBIAR_SS;
		break;
	case 'D':
		estadoActual=CAMBIAR_C;
		break;
	case '*':
		break;
	case '#':
		break;
	case CASO_NULO:
		break;
	default:
		// llamar a leer clave
		break;
	}
}
unsigned char is_num(unsigned char aux){
	return aux-'0' < 10 ? 1 : 0;
}

unsigned char construir_num(unsigned char pro, unsigned char sdo) {
	return (((pro-'0')*10)+(sdo-'0'));
}
void fABIERTO(void){
	
}
void fDENEGADO(void){
	
}
unsigned char i, pro, sdo;
void fCAMBIAR_HH(void){
	stringOut[0]='H';
	if(i<2){
		if(cola_vacia()==0){
			key = pop_tecla();
			if(is_num(key)==0)return;
				if(i==0)
					pro=key;
				else
					sdo=key;
			i++;
		}
		
	}
	if((i==2)&&(key!='A')){
		if(cola_vacia()==0){
			key = pop_tecla();
		}
	}
	if((i==2)&&(key=='A')){
		cambiar_hora(construir_num(pro,sdo), IGNORE_MM, IGNORE_SS);
		estadoActual=CERRADO;
		key=CASO_NULO;
		i=0;
	}
}

void fCAMBIAR_MM(void){
	stringOut[0]='M';
	if(i<2){
		if(cola_vacia()==0){
			key = pop_tecla();
			if(is_num(key)==0)return;
				if(i==0)
					pro=key;
				else
					sdo=key;
			i++;
		}
		
	}
	if((i==2)&&(key!='B')){
		if(cola_vacia()==0){
			key = pop_tecla();
		}
	}
	if((i==2)&&(key=='B')){
		cambiar_hora(IGNORE_HH, construir_num(pro,sdo), IGNORE_SS);
		estadoActual=CERRADO;
		key=CASO_NULO;
		i=0;
	}
}
void fCAMBIAR_SS(void){
	stringOut[0]='S';
	if(i<2){
		if(cola_vacia()==0){
			key = pop_tecla();
			if(is_num(key)==0)return;
				if(i==0)
					pro=key;
				else
					sdo=key;
			i++;
		}
		
	}
	if((i==2)&&(key!='C')){
		if(cola_vacia()==0){
			key = pop_tecla();
		}
	}
	if((i==2)&&(key=='C')){
		cambiar_hora(IGNORE_HH, IGNORE_MM, construir_num(pro,sdo));
		estadoActual=CERRADO;
		key=CASO_NULO;
		i=0;
	}	
}
void fCAMBIAR_C(void){
	
}
