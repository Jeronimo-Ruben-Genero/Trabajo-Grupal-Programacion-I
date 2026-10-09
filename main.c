#include<stdio.h>
#include<stbool.h>
#include<ctype.h>
#include<string.h>
#define LIM 7
bool continua() {
    char continua;
    bool eleccion;

    do{
        printf("si (S).\nno (N).\nDesea continuar: ");
        scanf(" %c", &continua);
        continua=toupper(continua);
        if(continua!='N'&&continua!='S'){
            printf("La respuesta no es valida.\nIngrese nuevamente.");
        }

    }while(continua!='N'&&continua!='S');

    if(continua=='N'){
        eleccion=false;
    }else{
        eleccion=true;
    }



    return eleccion;
}
void IngresarDatos(t_auto a) {

    do {
        printf("Ingrese la patente del auto a revisar: ");
        fflush(stdin);
        scanf("%s", a.Patente);
        if (a.Patente[0] == '\0') {
            printf("La patente no existe\n");
        }
    }while (a.Patente[0] == '\0');

    do {
        printf("(A)Cambio de aceite.\n(M)Revision de motor.\n(C)Revision de chasis.\nSeleccione el servicio que desee: ");
        fflush(stdin);
        scanf(" %c", &a.TipoServicio);
        if (a.TipoServicio != 'A' && a.TipoServicio != 'M' && a.TipoServicio != 'C') {
            printf("El servicio seleccionado no es valido, ingrese nuevamente.\n");
        }
    }while (a.TipoServicio != 'A' && a.TipoServicio != 'M' && a.TipoServicio != 'C');

    do {
        printf("Introduzca el numero de orden: ");
        fflush(stdin);
        scanf("%d", &a.NumeroOrden);
        if (a.NumeroOrden < 1) {
            printf("El numero de ordenes no es valido, ingresar nuevamente.\n");
        }
    }while (a.NumeroOrden < 1);


    do {
        printf("Introduzca el costo del servicio: ");
        fflush(stdin);
        scanf("%f", &a.Costo);
        if (a.Costo <= 0) {
            prinf("El costo del servicio no puede ser igual o menor a cero. Ingrese nuevamente.\n");
        }
    }while (a.Costo <= 0 );

    do {
        printf("(1)Si.\n(0)No.\nIndique si el servicio ha finalizado: ");
        fflush(stdin);
        scanf("%d", &a.Finalizo);
        if(a.Finalizo == 1) {
            a.finalizo=true;
        }else if(a.Finalizo == 0) {
            a.Finalizo=false;
        }
        if (a.Finalizo !=0 && a.Finalizo != 1) {
            printf("El servicio no es valido, ingresar nuevamente.\n");
        }
    }while (a.Finalizo != 0 && a.Finalizo != 1);


    return;
}
void AgregarOrden() {
    t_auto a;
    bool sigo=true;
    FILE *Service_De_Autos = fopen(Service_De_Autos, "a");
    if (Service_De_Autos == NULL) puts("Error al abrir el archivo");
    else {
        while (sigo) {
            a=IngresarDatos();
            fprintf(Service_De_Autos,"%s %c %d %f %d", a.Patente, a.TipoServicio, a.NumeroOrden, a.Costo, a.Finalizo );
            sigo = continua();
        }
    }



}
void menu () {
    int menu;
    printf("(1)Agregar orden de servicio.\n(2)Mostrar en pantalla listado de servicios.\n(3)Mostrar en pantalla listado de servicios pendientes.");
    printf("(4)Buscar un servicio por patente.\n(5)Separar servicios finalizados y pendientes en dos archivos.\n(0)Salir.");
    printf("Introduzca su eleccion:");
    scanf("%d", &menu);

    do {
        switch (menu) {
            case 1: {
                AgregarOrden();
            }
            case 2: {
                ListadoCompleto();
            }
            case 3: {
                ListadoPendientes();
            }
            case 4: {
                BuscarPatente();
            }
            case 5: {
                SepararSericios();
            }
            case 0: {
                printf("El programa ha finalizado.");
            }
        }
    }while (menu!=0);

    return;
}
int main() {
    //paso 1. definir struct.
    typedef struct {
        char Patente[LIM];
        char TipoServicio;
        int NumeroOrden;
        float Costo;
        bool Finalizo;
    }t_auto;
    //paso 2. iniciar menu.
    menu();



    return 0;
}