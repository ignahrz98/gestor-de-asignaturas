/*
1. Unidades Curriculares.
    1.1. Ingresar unidad curricular. <<<
    1.2. Modicar unidad curricular. <<<
    1.3  Eliminar Unidad curricular. <<<
    1.4 Ver todas las unidades curriculares. <<<
    1.5 Buscar Asignatura  <<<
2. Asistencias del estudiante/profesor.
3. Diario de asignaturas.
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>

char V[] = "1.1"; //Version del programa.

FILE *archivo,*temp,*archid;

void gotoxy(int x,int y);
void unidades_curriculares();
void ingresar_asignatura();
void ver_todo();
void busca_asigna();
void modificar();
void borrar();
void registrar_dia();
void ver_registro();
void saliendo();
void eventos();
void registrar_evento();
void entrando();
void ver_eventos();
void editar_evento();
void eliminar_evento();

typedef struct { //Estructura para almacenar datos de la asignatura.
	char nombre[50]; //Nombre de la unidad curricular.
	char profe[50]; //Nombre del profesor o profesora.
	char telefono[15]; //Numero de telefono del profesor o profesora.
	char correo[50]; //Correo Electronico del profesor o profesora.
	int uc; //Unidades de credito de la Asignatura.
	int nota; //Nota final de la asignatura.
	int clases_dadas; //Numeros de clases dadas.
	int clase_asisten; //Numero de asistencias en la asignatura;
	int test; //Numero de evaluaciones realizadas.
	int inasprof; //Inasistencia del profesor.
}curricular;

typedef struct { //Estructura para almacenar datos de registro diarios.
	char fecha[12]; //Arreglo para almacenar fecha
	char nombre[50]; //nombre de la asignatura.
	int tipo; //clase normal o evalucion.
}diario;

typedef struct { //Estructura para almacenar eventos y notas.
	char fecha[12]; //Fecha pautada para el evento.
	int prioridad; //0- Baja, 1-Media, 2-Alta.
	char resumen[100]; //Describir rapidamente el evento.
	int codigo; //Codigo unico para cada evento.
}evento;

curricular materia;
diario dia;
evento eventodata;

int main(){
	system("title Gestor de Asignaturas 1.1");
	entrando(); //Llamar a funcion para animacion de entrada.
	int m;
	do {
		system("color 70");
		system("cls");
		do {
		//Mostrar menu principal del programa.
	    gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	    gotoxy(25,1);printf("Gestor De Asignaturas %s", V);
	    gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	    gotoxy(10,4);printf("(1) Unidades Curriculares.");
	    gotoxy(40,4);printf("(2) Registrar Dia.");
	    gotoxy(10,6);printf("(3) Registro Diario.");
	    gotoxy(40,6);printf("(4) Eventos.");
	    gotoxy(65,23);printf("(5) Salir.");
	    gotoxy(40,9);printf("------");
	    gotoxy(40,10);printf("|    | <- Ingrese aqui su opcion.");
	    gotoxy(40,11);printf("------");
	    gotoxy(42,10);scanf("%i", &m);
	    if(m<1 || m>5) {
		    gotoxy(20,15);printf("<<--La opcion ingresada es invalida-->>");
		    getch();
	    }
	    system("cls");
	    } while (m<1 || m>5);
	
    	switch(m) {
		    case 1:
		    	system("color 4f");
		    	unidades_curriculares(); //llamar funcion de menu para unidades curriculares.
	    	break;
		    case 2:
		    	system("color 2f");
		    	registrar_dia(); //Llamar funcion para registrar dia.
	    	break;
	    	case 3:
	    		system("color 02");
	    		ver_registro(); //Llamar funcion para ver registro diario.
		    break;
		    case 4:
		    	system("color 9f");
		    	eventos(); //Llamar a funcion para menu eventos.
		    break;
	    }
	   
	} while( m>=1 && m<5);
	system("cls");
	saliendo();
    return 0;	
}

void entrando() { //Funcion para animacion de entrada.
	int i, x=2, tam=0;
	system("color 31");
	//Animacion marco.
	for(i=0;i<25;i++) {
		gotoxy(0,i);printf("*");
		Sleep(x);
	}
	for(i=0;i<78;i++) {
		gotoxy(i,24);printf("*");
		Sleep(x);
	}
	for(i=24;i>=0;i--) {
		gotoxy(78,i);printf("*");
		Sleep(x);
	}
	for(i=78;i>=0;i--) {
		gotoxy(i,0);printf("*");
		Sleep(x);
	}
	//Mensaje bienvenido.
	i=2;
	gotoxy(2,i);printf("######  ### ####### #     # #     # ####### #     # ### ######  ####### "); i++;
    gotoxy(2,i);printf("#     #  #  #       ##    # #     # #       ##    #  #  #     # #     #"); i++;
    gotoxy(2,i);printf("#     #  #  #       # #   # #     # #       # #   #  #  #     # #     # "); i++;
    gotoxy(2,i);printf("######   #  #####   #  #  # #     # #####   #  #  #  #  #     # #     #"); i++;
    gotoxy(2,i);printf("#     #  #  #       #   # #  #   #  #       #   # #  #  #     # #     #"); i++;
    gotoxy(2,i);printf("#     #  #  #       #    ##   # #   #       #    ##  #  #     # #     #"); i++;
    gotoxy(2,i);printf("######  ### ####### #     #    #    ####### #     # ### ######  #######"); 
    
    gotoxy(5,20);printf("Gestor De Asignaturas %s", V);
    gotoxy(40,18);printf("Desarrollado por:");
    gotoxy(50,20);printf("Ignacio Hernandez");
    Sleep(3000);
    archivo = fopen("eventos.bin","rb");
    if(archivo!=NULL) {
    	system("cls");
    	x=0;
    	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	    gotoxy(30,1);printf("Actividades Importantes.");
	    gotoxy(0,2);printf("--------------------------------------------------------------------------------");
    	gotoxy(0,4);printf("---------------------------------Prioridad Alta---------------------------------");
    	gotoxy(2,6);printf("Codigo");
	    gotoxy(10,6);printf("Fecha");
	    gotoxy(40,6);printf("Resumen De Evento");
	    while(!feof(archivo)) {
	    	fread(&eventodata,sizeof(evento),1,archivo);
	    	x++;
		}
		rewind(archivo);
		x--; i=8;
		while(tam<x) {
			fread(&eventodata,sizeof(evento),1,archivo);
			if(eventodata.prioridad==2) {
				gotoxy(2,i);printf("%i",eventodata.codigo);
		        gotoxy(10,i);printf("%s",eventodata.fecha);
		        gotoxy(22,i);printf("%s",eventodata.resumen);
		        i++;
			}
			tam++;
		}
    	Sleep(5000);
	}
    fclose(archivo);
}

void saliendo() { //Funcion para animacion de salida.
    int y=2; system("color 3a");
    gotoxy(5,y);printf(" #####  ####### ######  ######     #    #     # ######  ####### ");y++;
    gotoxy(5,y);printf("#     # #       #     # #     #   # #   ##    # #     # #     # ");y++;
    gotoxy(5,y);printf("#       #       #     # #     #  #   #  # #   # #     # #     # ");y++;
    gotoxy(5,y);printf("#       #####   ######  ######  #     # #  #  # #     # #     #"); y++;
    gotoxy(5,y);printf("#       #       #   #   #   #   ####### #   # # #     # #     # ");y++;
    gotoxy(5,y);printf("#     # #       #    #  #    #  #     # #    ## #     # #     #"); y++;
    gotoxy(5,y);printf(" #####  ####### #     # #     # #     # #     # ######  ####### "); 
    Sleep(2000);
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }
 
 void unidades_curriculares() { //Funcion para menu de la opcion unidades curriculares.
    int op;
    do {
    	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	    gotoxy(30,1);printf("Unidades Curriculares");
	    gotoxy(0,2);printf("--------------------------------------------------------------------------------");
         gotoxy(10,4);printf("(1) Ingresar Asignatura.");
         gotoxy(40,4);printf("(2) Editar Asignatura.");
         gotoxy(10,6);printf("(3) Eliminar Asignatura.");
         gotoxy(40,6);printf("(4) Ver Todas Las Asignaturas.");
         gotoxy(10,8);printf("(5) Buscar Asignatura.");
         gotoxy(49,23);printf("(6) Regresar Al Menu Principal.");
         gotoxy(40,11);printf("------");
	    gotoxy(40,12);printf("|    | <- Ingrese aqui su opcion.");
	    gotoxy(40,13);printf("------");
	    gotoxy(42,12);scanf("%i", &op);
	    if(op<1 || op>6) {
		    gotoxy(20,16);printf("<<--La opcion ingresada es invalida-->>");
		    getch();
	    }
	    system("cls");
	} while(op<1 || op>6);

    switch(op) {
    	case 1:
    		ingresar_asignatura(); //LLamar funcion para ingresar Asignatura.
    	break;
    	case 2:
    		modificar();
    	break;
    	case 3:
    		borrar();
    	break;
    	case 4:
    	     ver_todo(); //Llamar a funcion para mostrar todas las asignaturas guardadas.	
    	break;
    	case 5:
    		busca_asigna(); //LLamar para buscar una asignatura guardada.
    	break;
	}
 }
 
 void ingresar_asignatura() { //Funcion para ingresar asignatura.
    int revisa_nombre = 0; //Variable para verificar si existe una asignatura del mismo nombre.
    //curricular temporal; //Estructura temporal para leer archivo.
    
    do {
    	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	    gotoxy(30,1);printf("Ingresar Asignatura");
	    gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	    gotoxy(20,4);printf("Ingrese Nombre De La Asignatura A Ingresar.");
	    gotoxy(20,6);printf("---------------------------------");
	    gotoxy(20,7);printf("|                               |");
	    gotoxy(20,8);printf("---------------------------------");
	    fflush(stdin);
	    gotoxy(22,7);gets(materia.nombre); //Pedir nombre para asignatura nueva.
	    /*
	        Aqui desarrollar proximamente verificar si nombre ya existe.
	    */
	    system("cls");
	} while( revisa_nombre != 0 );
 	
 	archivo = fopen("data.bin","a+"); //Abrir archivo para ingresar nueva asignatura.
 	if(archivo != NULL) {
 		materia.nota = 0;
 		materia.test = 0;
 		materia.inasprof = 0;
 		materia.clases_dadas = 0;
 		materia.clase_asisten = 0;
 		gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	    gotoxy(30,1);printf("Ingresar Asignatura");
	    gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	    gotoxy(10,4);printf("Asignatura: %s.",materia.nombre);
	    gotoxy(5,6);printf("-----------------------------------------------------------------");
	    gotoxy(5,7);printf("| Profesor (a) |                                                |");
	    gotoxy(5,8);printf("-----------------------------------------------------------------");
	    gotoxy(5,9);printf("| Telefono     |                                                |");
	    gotoxy(5,10);printf("-----------------------------------------------------------------");
	    gotoxy(5,11);printf("| E-mail       |                                                |");
	    gotoxy(5,12);printf("-----------------------------------------------------------------");
	    gotoxy(5,13);printf("| U.C          |                                                |");
	    gotoxy(5,14);printf("-----------------------------------------------------------------");
	    fflush(stdin);
	    gotoxy(23,7);gets(materia.profe); //Pedir nombre del profesor o profesora.
	    fflush(stdin);
	    gotoxy(23,9);gets(materia.telefono); //Pedir numero de telefono.
	    fflush(stdin);
	    gotoxy(23,11);gets(materia.correo); //Pedir correo.
	    gotoxy(23,13);scanf("%i", &materia.uc); //Pedir cantidad de unidades de credito de la asignatura.
	    
	    fwrite(&materia,sizeof(curricular),1,archivo);
	    gotoxy(20,20);printf("<<--Asignatura Almacenada con exito-->>");
	    gotoxy(5,22);printf("Profesor (a): %s", materia.profe);fflush(stdin);
	    gotoxy(5,23);printf("Telefono: %s", materia.telefono);
	    gotoxy(5,24);printf("E-mail: %s", materia.correo);
	    gotoxy(5,25);printf("U.C: %i", materia.uc);
	    getch();
	}
	else {
		printf("<<--Opps! Hubo un error al intentar crear archivo de data!-->>");
		getch();
	}
 	fclose(archivo); //Cerrando archivo.
 }
 
 void ver_todo() { //Funcion para mostrar todas las asignaturas guardadas.
 	int tam=0;
	int vuelta=0;
	int x=6;

	archivo = fopen("data.bin","r");
	if (archivo == NULL) {
		gotoxy(20,10);printf("<<--Oh oh! Parece que la data esta vacia!-->>");
		getch();
	}
	else {
		while(!feof(archivo)) {
			fread(&materia,sizeof(curricular),1,archivo);
			tam++;
		}
		rewind(archivo);
		gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	     gotoxy(30,1);printf("Asignaturas Guardadas");
	     gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	     gotoxy(2,4);printf("Asignatura");
	     gotoxy(30,4);printf("UC");
	     gotoxy(38,4);printf("Clases");
	     gotoxy(45,4);printf("Asist");
	     gotoxy(55,4);printf("Inas");
	     gotoxy(65,4);printf("Inas Prof");
	     while(vuelta<=tam-2) {
	     	fread(&materia,sizeof(curricular),1,archivo);
	     	
	     	gotoxy(2,x);printf("%s",materia.nombre);
	     	gotoxy(30,x);printf("%i",materia.uc);
	     	gotoxy(38,x);printf("%i",materia.clases_dadas);
	     	gotoxy(45,x);printf("%i",materia.clase_asisten);
	     	gotoxy(55,x);printf("%i",materia.clases_dadas - materia.clase_asisten);
	     	gotoxy(65,x);printf("%i", materia.inasprof);
	     	x++;
	     	vuelta++;
		}
		
	}
	fclose(archivo);
	getch();
 }
 
 void busca_asigna() { //Funcion para buscar asignatura guardada.
 	int tam=0;
	int vuelta=0;
	int encontrar = 0;
	char buscar[50];
	float pro = 0;
	
	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Buscar Asignatura");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(20,4);printf("Ingrese Nombre De La Asignatura A Buscar.");
	gotoxy(20,6);printf("---------------------------------");
	gotoxy(20,7);printf("|                               |");
	gotoxy(20,8);printf("---------------------------------");
	fflush(stdin);
	gotoxy(22,7);gets(buscar);
	system("cls");
	archivo = fopen("data.bin","r"); //Abrir archivo para buscar asignatura.
	if (archivo == NULL) {
		gotoxy(20,10);printf("<<--Oh oh! Parece que la data esta vacia!-->>");
		getch();
	}
	else {
		while(!feof(archivo)) {
			fread(&materia,sizeof(curricular),1,archivo);
			tam++;
		}
		rewind(archivo);
		gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	     gotoxy(30,1);printf("Buscar Asignatura");
	     gotoxy(0,2);printf("--------------------------------------------------------------------------------");
		while(vuelta<=tam-2) {
			fread(&materia,sizeof(curricular),1,archivo);
			if(strcmp(buscar,materia.nombre)==0) {
			    encontrar++;
			    if (materia.clases_dadas > 0) {
	     	        pro = (materia.clase_asisten/materia.clases_dadas) * 100;
			    }
			    gotoxy(10,4);printf("Asignatura: %s.",materia.nombre);
	              gotoxy(5,6);printf("-----------------------------------------------------------------");
	              gotoxy(5,7);printf("| Profesor (a) |                                                |");
	              gotoxy(5,8);printf("-----------------------------------------------------------------");
	              gotoxy(5,9);printf("| E-mail       |                                                |");
	              gotoxy(5,10);printf("-----------------------------------------------------------------");
	              gotoxy(5,11);printf("| Telefono     |                                                |");
	              gotoxy(5,12);printf("-----------------------------------------------------------------");
	              gotoxy(5,13);printf("| U.C          |                                                |");
	              gotoxy(5,14);printf("-----------------------------------------------------------------");
	              gotoxy(5,15);printf("| Clases       |                                                |");
	              gotoxy(5,16);printf("-----------------------------------------------------------------");
	              gotoxy(5,17);printf("| Asistencias  |                                                |");
	              gotoxy(5,18);printf("-----------------------------------------------------------------");
	              gotoxy(5,19);printf("| Promedio     |                                                |");
	              gotoxy(5,20);printf("-----------------------------------------------------------------");
	              gotoxy(5,21);printf("| Evaluaciones |                                                |");
	              gotoxy(5,22);printf("-----------------------------------------------------------------");
	              gotoxy(5,23);printf("| Inas. Prof   |                                                |");
	              gotoxy(5,24);printf("-----------------------------------------------------------------");
	              gotoxy(23,7);printf("%s",materia.profe); //Mostrar profesor o profesora.
	              gotoxy(23,9);printf("%s",materia.correo); //Mostrar correo.
	              gotoxy(23,11);printf("%s",materia.telefono); //Mostrar numero de telefono.
	              gotoxy(23,13);printf("%i",materia.uc); //Unidades Curriculares de la Asignatura.
	              gotoxy(23,15);printf("%i",materia.clases_dadas); //Clases dadas.
	              gotoxy(23,17);printf("%i",materia.clase_asisten); //Clases asistidas.
	              gotoxy(23,19);printf("%.2f",pro);
	              gotoxy(23,21);printf("%i",materia.test);
	              gotoxy(23,23);printf("%i", materia.inasprof);
	              getch();
	              system("cls");
			}
			vuelta++;
		}
		if(encontrar == 0) {
			gotoxy(20,4);printf("<<--No se ha encontrado lo que busca-->>");
			getch();
		}
	}
	fclose(archivo); //Cerrar archivo.
 }
 
 void modificar() { //Funcion para modificar asignaturas guardadas.
 	int tam=0; //Contar ciclos cuando lee archivo.
	int vuelta=0; //Contar ciclos al usar archivo.
	int encontrar = 0; //Variable para indicar si hubo coincidencia de busqueda.
	char buscar[50]; //Arreglo para buscar asignatura a modificar.
	int m;
	
	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Editar Asignatura");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(20,4);printf("Ingrese Nombre De La Asignatura A Editar.");
	gotoxy(20,6);printf("---------------------------------");
	gotoxy(20,7);printf("|                               |");
	gotoxy(20,8);printf("---------------------------------");
	fflush(stdin);
	gotoxy(22,7);gets(buscar); //Pedir nombre de la asignatura a editar.
	system("cls");
	temp = fopen("temporal.bin","w"); //Crear archivo temporal para modificar asignatura.
	archivo = fopen("data.bin","r"); //Abrir archivo para editar asignatura.
	if(archivo == NULL) {
		gotoxy(20,10);printf("<<--Oh oh! Parece que la data esta vacia!-->>");
		getch();
	}
	else {
		while(!feof(archivo)) {
			fread(&materia,sizeof(curricular),1,archivo);
			tam++;
		}
		rewind(archivo);
		while(vuelta<=tam-2) {
			fread(&materia,sizeof(curricular),1,archivo);
			if(strcmp(buscar,materia.nombre)==0) {
				encontrar++;
				gotoxy(0,0);printf("--------------------------------------------------------------------------------");
               	gotoxy(5,1);printf("Editando a: %s", buscar);
	               gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	               gotoxy(30,4);printf("Ingrese campo a editar.");
	               gotoxy(5,6);printf("(1) Nombre: %s", materia.nombre);
	               gotoxy(5,7);printf("(2) Profesor (a): %s", materia.profe);
	               gotoxy(5,8);printf("(3) Telefono: %s", materia.telefono);
	               gotoxy(5,9);printf("(4) E-mail: %s", materia.correo);
	               gotoxy(5,10);printf("(5) U.C: %i", materia.uc);
	               gotoxy(5,11);printf("(6) Nota final: %i", materia.nota);
	               gotoxy(10,13);printf("------");
	               gotoxy(10,14);printf("|    |");
	               gotoxy(10,15);printf("------");
	               gotoxy(12,14);scanf("%i", &m); //Ingresar campo de modificar.
	               //Dependiendo de la opcion ingresada por el usuario, se modificara el campo correspondiente.
	               switch(m) {
	               	case 1:
	               		gotoxy(5,18);printf("Nombre Nuevo: "); //Ingresar nombre nuevo para asignatura.
	               		fflush(stdin);
	               		gets(materia.nombre);
	               	break;
	               	case 2:
	               		gotoxy(5,18);printf("Profesor Nuevo: "); //Ingresar nombre nuevo para profesor.
	               		fflush(stdin);
	               		gets(materia.profe);
	               	break;
	               	case 3:
	               		gotoxy(5,18);printf("Telefono Nuevo: "); //Ingresar telefono nuevo para asignatura.
	               		fflush(stdin);
	               		gets(materia.telefono);
	               	break;
	               	case 4:
	               		gotoxy(5,18);printf("E-mail Nuevo: "); //Ingresar correo nuevo para asignatura.
	               		fflush(stdin);
	               		gets(materia.correo);
	               	break;
	               	case 5:
	               		gotoxy(5,18);printf("U.C Nuevo: "); //Ingresar U.C nuevo para asignatura.
	               		scanf("%i", &materia.uc);
	               	break;
	               	case 6:
	               		gotoxy(5,18);printf("Nota Final de Asignatura: "); //Ingresar nota final para asignatura.
	               		scanf("%i", &materia.nota);
	               	break;
				}
	               gotoxy(20,20);printf("<<--Campo Actualizado Con Exito->>");
				fwrite(&materia,sizeof(curricular),1,temp); //Escribir estructura modificada a temporal.
			}
			else {
				fwrite(&materia,sizeof(curricular),1,temp); //Escribir estructura a temporal.
			}
			vuelta++;
		}
		if(encontrar == 0) {
			gotoxy(10,10);printf("<<--La asignatura %s no ha sido encontrada-->>",buscar);
			getch();
		}
	}
	fclose(archivo); //Cerrar archivo.
	fclose(temp);//Cerrar archivo temporal.
	
	remove("data.bin"); //Borrar archivo de data.
	rename("temporal.bin","data.bin"); //Convertir archivo temporal a data.
 }
 
 void borrar() { //Funcion para borrar asignatura.
 	int tam=0; //Contar ciclos cuando lee archivo.
	int vuelta=0; //Contar ciclos al usar archivo.
	int encontrar = 0; //Variable para indicar si hubo coincidencia de busqueda.
	char buscar[50]; //Arreglo para buscar asignatura a eliminar.
	
	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Eliminar Asignatura");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(20,4);printf("Ingrese Nombre De La Asignatura A Eliminar.");
	gotoxy(20,6);printf("---------------------------------");
	gotoxy(20,7);printf("|                               |");
	gotoxy(20,8);printf("---------------------------------");
	fflush(stdin);
	gotoxy(22,7);gets(buscar); //Pedir nombre de la asignatura a eliminar.
	temp = fopen("temporal.bin","w"); //Crear archivo temporal para eliminar asignatura.
	archivo = fopen("data.bin","r"); //Abrir archivo para eliminar asignatura.
	if(archivo == NULL) {
		gotoxy(20,10);printf("<<--Oh oh! Parece que la data esta vacia!-->>");
		getch();
	}
	else {
		while(!feof(archivo)) {
			fread(&materia,sizeof(curricular),1,archivo);
			tam++;
		}
		rewind(archivo);
		while(vuelta<=tam-2) {
			fread(&materia,sizeof(curricular),1,archivo);
			if(strcmp(buscar,materia.nombre)==0) {
				encontrar++;
				gotoxy(20,10);printf("<<--Asignatura Borrada Con Exito-->>");
			}
			else {
				fwrite(&materia,sizeof(curricular),1,temp); //Copiar Estructuras A Temporal.
			}
			vuelta++;
		}
		if(encontrar == 0) {
			gotoxy(10,10);printf("<<--La asignatura %s no ha sido encontrada-->>",buscar);
			getch();
		}
	}
	fclose(archivo); //Cerrar archivo.
	fclose(temp); //Cerrar archivo temporal.
	
	remove("data.bin"); //Borrar archivo de data.
	rename("temporal.bin","data.bin"); //Convertir archivo temporal a data.
 }
 
 void registrar_dia() { //Funcion para registrar dia.
    int tam = 0;//Contador para feof.
    int vuelta = 0;//Contador para lectura controlada del archivo.
    int x = 9;//Contador para Y en gotoxy.
    int op;
    
   	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Registrar dia.");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(10,4);printf("Ingresar fecha(dd-mm-aaaa): ");
	fflush(stdin);gets(dia.fecha);//Ingresar fecha.
	gotoxy(10,5);printf("Asignatura: ");
	//Mostrar asignaturas almacenadas.
	archivo = fopen("data.bin","rb");
	if(archivo == NULL) {
		system("cls");
		printf("<<--La data se encuentra vacia-->>");
		getch();
	}
	else { //Mostrar las asignaturas una vez no se NULL.
		while(!feof(archivo)) {
			fread(&materia,sizeof(curricular),1,archivo);
			tam++;
		}
		rewind(archivo);
		gotoxy(30,7);printf("Asignaturas Almacenadas:");
		while(vuelta<=tam-2) {
			fread(&materia,sizeof(curricular),1,archivo);
			gotoxy(5,x);printf("%s", materia.nombre);
			x++;
			vuelta++;
		}
	}
	fclose(archivo);//Cerrar archivo.
	fflush(stdin);
	gotoxy(22,5);gets(dia.nombre);//Ingresar nombre de la asignatura.
	system("cls");
	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Registrar dia %s para %s", dia.fecha, dia.nombre);
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(20,4);printf("Indique si hubo o no clase. ");
	gotoxy(10,6);printf("0- Falto el profesor.");
	gotoxy(10,7);printf("1- Clase Normal.");
	gotoxy(10,8);printf("2- Evaluacion.");
	gotoxy(12,10);printf(">> ");scanf("%i", &dia.tipo);//Indicar si hubo clase o no.
	//Guardar registro en historial.
	archid = fopen("historial.bin","a+");
	fwrite(&dia,sizeof(diario),1,archid);
	gotoxy(30,10);printf("<<--Registro Almacenado A Historial-->>");
	fclose(archid);
	tam = 0;//Contador para feof.
    vuelta = 0;//Contador para lectura controlada del archivo.
	temp = fopen("temporal.bin","wb");
	archivo = fopen("data.bin","rb");
	if(archivo == NULL) {
		system("cls");
		printf("<<--La data se encuentra vacia-->>");
		getch();
	}
	else {
		while(!feof(archivo)) {
			fread(&materia,sizeof(curricular),1,archivo);
			tam++;
		}
		rewind(archivo);
		while(vuelta<=tam-2) {
			fread(&materia,sizeof(curricular),1,archivo);
			if(strcmp(dia.nombre,materia.nombre)==0) {
				switch(dia.tipo) {
					case 0: materia.inasprof++; break;
					case 1: materia.clases_dadas++; break;
					case 2: materia.clases_dadas++; materia.test++; break;
				}
				if(dia.tipo > 0) {
					gotoxy(10,12);printf("Usted Asistio?: ");
					gotoxy(10,14);printf("0- No Asisti.");
					gotoxy(10,15);printf("1- Si Asisti");
					gotoxy(26,12);scanf("%i", &op);//Indicar asistencia.
					if(op > 0) {
						materia.clase_asisten++;
					}
				}
				fwrite(&materia,sizeof(curricular),1,temp); //Copiar Estructuras A Temporal.
			}
			else {
				fwrite(&materia,sizeof(curricular),1,temp); //Copiar Estructuras A Temporal.
			}
			vuelta++;
		}
	}
	fclose(temp);
	fclose(archivo);
	
	remove("data.bin");
	rename("temporal.bin","data.bin");
}
 
 void ver_registro() { //Funcion para ver registros diarios.
     int tam=0;
	int vuelta=0;
	int x=6;
	
    gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Registros Almacenados.");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	archid = fopen("historial.bin","r");
	if(archid != NULL) {
		while(!feof(archid)) {
			fread(&dia,sizeof(diario),1,archid);
			tam++;
		}
		rewind(archid);
		gotoxy(2,4);printf("FECHA");
		gotoxy(20,4);printf("ASIGNATURA");
		gotoxy(40,4);printf("TIPO");
		while(vuelta<=tam-2) {
			fread(&dia,sizeof(diario),1,archid);
	     	gotoxy(2,x);printf("%s",dia.fecha);
	     	gotoxy(20,x);printf("%s",dia.nombre);
	     	if (dia.tipo == 0) {
	     		gotoxy(40,x);printf("Falto el profesor");
			}
			else if (dia.tipo == 1) {
	     		gotoxy(40,x);printf("Clase Normal");
			}
			else {
				gotoxy(40,x);printf("Evaluacion");
			}
	     	x++;
	     	vuelta++;
		}
	}
	fclose(archid);
	getch();
 }
 
 void eventos() { //Funcion para menu eventos y notas.
    int m;
    
 	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Eventos.");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	//Registrar evento, modificar, eliminar, desplegar eventos.
	//Examen, Actividad, Evaluacion personalizada, notas.
	gotoxy(5,4);printf("(1) Registrar Evento.");
	gotoxy(40,4);printf("(2) Editar Evento.");
	gotoxy(5,6);printf("(3) Eliminar Evento.");
	gotoxy(40,6);printf("(4) Ver Eventos.");
	gotoxy(49,23);printf("(5) Regresar Al Menu Principal.");
	gotoxy(40,9);printf("------");
	gotoxy(40,10);printf("|    | <- Ingrese aqui su opcion.");
    gotoxy(40,11);printf("------");
	gotoxy(42,10);scanf("%i", &m);
	system("cls");
	switch(m) {
		case 1:
			registrar_evento(); //LLamar a funcon para registrar evento.
		break;
		case 2:
			editar_evento(); //LLamar a funcion para editar evento.
		break;
		case 3:
			eliminar_evento(); //Llamar a funcion para eliminar evento.
		break;
		case 4:
			ver_eventos(); //LLamar a funcion para mostrar todos los eventos.
		break;
	}
	
 }
 
 void eliminar_evento() { //Funcion para eliminar evento.
    int buscar, i=0, tam=0, sel;
 	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(20,1);printf("Eliminar Evento.");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(5,4);printf("Ingrese codigo del evento: "); scanf("%i", &buscar);
	archivo = fopen("eventos.bin","rb"); //Abrir archivo para leer eventos.
	temp = fopen("temporal.bin", "wb"); //Abrir archivo para borrar eventos.
	if(archivo == NULL) {
		gotoxy(10,6);printf("<<-Oh oh! La data esta vacia!");
	}
	else {
		while(!feof(archivo)) {
			fread(&eventodata,sizeof(evento),1,archivo);
			i++;
		}
		i--;
		rewind(archivo);
		while(tam<i) {
			fread(&eventodata,sizeof(evento),1,archivo);
			if(buscar != eventodata.codigo) {
				fwrite(&eventodata,sizeof(evento),1,temp);
			}
			else {
				gotoxy(20,6);printf("Esta seguro de elimnar este evento?");
				gotoxy(5,8);printf("(1) Fecha: %s", eventodata.fecha);
				switch(eventodata.prioridad) {
					case 0: gotoxy(5,9);printf("(2) Prioridad: Baja"); break;
					case 1: gotoxy(5,9);printf("(2) Prioridad: Media"); break;
					case 2: gotoxy(5,9);printf("(2) Prioridad: Alta"); break;
				}
				gotoxy(5,10);printf("(3) Resumen: %s", eventodata.resumen);
				gotoxy(5,12);printf("Ingrese seleccion(1=Si,0=No): "); scanf("%i", &sel);
				switch(sel) {
					case 0:
						fwrite(&eventodata,sizeof(evento),1,temp);
					    gotoxy(10,14); printf("<<-Operacion abortada->>"); 
					break;
					case 1:
						gotoxy(10,14); printf("<<-Evento Eliminado->>");
					break;
				}
			}
			tam++;
		}
	}
	getch();
	fclose(archivo); //Cerrar archivo.
	fclose(temp); //Cerrar archivo temporal.
	
	remove("eventos.bin"); //Eliminar archivo de eventos.
	rename("temporal.bin","eventos.bin"); //Renombrar archivo.
 }
 
 void editar_evento() { //Funcion para editar evento.
    int buscar, i=0, tam=0, sel;
 	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(20,1);printf("Editar Evento.");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(10,4);printf("Ingrese codigo del evento: ");
	scanf("%i", &buscar);
	
	archivo = fopen("eventos.bin","rb"); //Abrir archivo para leer eventos.
	temp = fopen("temporal.bin","wb"); //Abrir archivo temporarl para editar eventos.
	if(archivo == NULL) {
		gotoxy(20,6);printf("<<-Oh Oh! Esta la data vacia!->>");
	} 
	else {
		while(!feof(archivo)) {
			fread(&eventodata,sizeof(evento),1,archivo);
			i++;
		}
		i--;
		rewind(archivo);
		while(tam<i) {
			fread(&eventodata,sizeof(evento),1,archivo);
			if (buscar != eventodata.codigo) {
				fwrite(&eventodata,sizeof(evento),1,temp); //Copiar estructura sin modificar a temporal.
			}
			else {
				gotoxy(30,6);printf("Seleccione campo a editar.");
				gotoxy(5,8);printf("(1) Fecha: %s", eventodata.fecha);
				switch(eventodata.prioridad) {
					case 0: gotoxy(5,9);printf("(2) Prioridad: Baja"); break;
					case 1: gotoxy(5,9);printf("(2) Prioridad: Media"); break;
					case 2: gotoxy(5,9);printf("(2) Prioridad: Alta"); break;
				}
				gotoxy(5,10);printf("(3) Resumen: %s", eventodata.resumen);
				gotoxy(5,12);printf("Ingrese seleccion: "); scanf("%i", &sel);
				switch(sel) {
					case 1:
						fflush(stdin);
						gotoxy(5,14);printf("Fecha Nueva: "); gets(eventodata.fecha); break;
					break;
					case 2:
						gotoxy(5,14);printf("Prioridad Nueva: "); scanf("%i", &eventodata.prioridad);
					break;
					case 3:
						gotoxy(30,14);printf("Resumen Nuevo: ");
						gotoxy(2,16);printf("*****************************************************");
	                    gotoxy(2,17);printf("*                                                   *");
	                    gotoxy(2,18);printf("*****************************************************");
	                    fflush(stdin);
	                    gotoxy(4,17);gets(eventodata.resumen);
					break;
				}
			    fwrite(&eventodata,sizeof(evento),1,temp); //Copiar estructura modificada a temporal.	
			}
			tam++;
		}
	}
	fclose(archivo); //Cerrar Archivo.
	fclose(temp); //Cerrar archivo temporal.
	
	remove("eventos.bin"); //Eliminar archivo de eventos.
	rename("temporal.bin","eventos.bin"); //Renombrar archivo.
 }
 
 void ver_eventos() { //Funcion para ver eventos.
 	int tam=0, i=0,x=2,y=6;
 	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(20,1);printf("Mostrar todos los eventos.");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(0,4);printf("---------------------------------Prioridad Alta---------------------------------");
	gotoxy(2,y);printf("Codigo");
	gotoxy(10,y);printf("Fecha");
	gotoxy(40,y);printf("Resumen De Evento");
	archivo = fopen("eventos.bin","rb");
	if(archivo == NULL) {
		gotoxy(20,10);printf("EVENTOS ESTA VACIO!!!");
		getch();
	}
	else {
		while(!feof(archivo)) {
			fread(&eventodata,sizeof(evento),1,archivo);
			i++;
		}
		i--;
		rewind(archivo);
		y+=2;
		while(tam<i) {
			fread(&eventodata,sizeof(evento),1,archivo);
			if(eventodata.prioridad == 2) {
				gotoxy(2,y);printf("%i",eventodata.codigo);
			    gotoxy(10,y);printf("%s",eventodata.fecha);
			    gotoxy(22,y);printf("%s",eventodata.resumen);
			    y++;
			}
			tam++;
		}
		rewind(archivo);
		y+=2;
		gotoxy(0,y);printf("---------------------------------Prioridad Media--------------------------------");
		y+=2; tam = 0;
		while(tam<i) {
			fread(&eventodata,sizeof(evento),1,archivo);
			if(eventodata.prioridad == 1) {
				gotoxy(2,y);printf("%i",eventodata.codigo);
			    gotoxy(10,y);printf("%s",eventodata.fecha);
			    gotoxy(22,y);printf("%s",eventodata.resumen);
			    y++;
			}
			tam++;
		}
		rewind(archivo);
		y+=2;
		gotoxy(0,y);printf("---------------------------------Prioridad Baja---------------------------------");
		y+=2; tam = 0;
		while(tam<i) {
			fread(&eventodata,sizeof(evento),1,archivo);
			if(eventodata.prioridad == 0) {
				gotoxy(2,y);printf("%i",eventodata.codigo);
			    gotoxy(10,y);printf("%s",eventodata.fecha);
			    gotoxy(22,y);printf("%s",eventodata.resumen);
			    y++;
			}
			tam++;
		}
	}
	fclose(archivo);
	getch();
 }
 
 void registrar_evento() { //Funcion para registrar evento.
    int i=0, cod=0, tam=0, priori;
    char cadena[100],fecha_guarda[12];
 	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(30,1);printf("Registrar Evento.");
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	gotoxy(20,4);printf("Indicar fecha pautada(dd-mm-aaaa): ");
	fflush(stdin);gets(fecha_guarda);
	gotoxy(5,6);printf("Indicar prioridad del evento: ");
	gotoxy(5,8);printf("0 = Baja");
	gotoxy(5,9);printf("1 = Media");
	gotoxy(5,10);printf("2 = Alta");
	gotoxy(35,6);scanf("%i", &priori);
	system("cls");
	gotoxy(0,0);printf("--------------------------------------------------------------------------------");
	gotoxy(10,1);printf("Registrar Evento para el %s", eventodata.fecha);
	gotoxy(0,2);printf("--------------------------------------------------------------------------------");
	switch(eventodata.prioridad) {
		case 0: gotoxy(50,1); printf("Prioridad: Baja."); break;
		case 1: gotoxy(50,1); printf("Prioridad: Media."); break;
		case 2: gotoxy(50,1); printf("Prioridad: Alta."); break;
	}
	gotoxy(8,5);printf("*****************************************************");
	gotoxy(8,6);printf("*                                                   *");
	gotoxy(8,7);printf("*****************************************************");
    gotoxy(10,10);printf("Ingrese su nota de evento en el campo superior.");
    gotoxy(1,15);printf("IMPORTANTE: No se debe exceder del tamano del campo, ya que generara un error.");
    fflush(stdin);
    gotoxy(10,6);gets(cadena);
    archivo = fopen("eventos.bin","rb");
    if(archivo == NULL) {
    	eventodata.codigo = 1;
	}
	else {
		while(!feof(archivo)) {
			fread(&eventodata,sizeof(evento),1,archivo);
			i++;
		}
		i--;
		rewind(archivo);
		while(tam<i) {
			fread(&eventodata,sizeof(evento),1,archivo);
			cod = eventodata.codigo+1;
			tam++;
		}
		eventodata.codigo = cod;
		
	}
    fclose(archivo);
	
	gotoxy(20,20);printf("Codigo Asignado: %i", eventodata.codigo);
	archivo = fopen("eventos.bin","a+b");
	if(archivo == NULL) {
		printf("Oh oh! Hubo un error con el archivo!");
		getch();
	}
	else {
		strcpy(eventodata.resumen,cadena);
		eventodata.prioridad = priori;
		strcpy(eventodata.fecha,fecha_guarda);
		fwrite(&eventodata,sizeof(evento),1,archivo);
		gotoxy(20,22);printf("<<-El evento ha sido almacenado->>");
		gotoxy(20,23);printf("%s", eventodata.resumen);
	}
	fclose(archivo);
	getch();
 }
