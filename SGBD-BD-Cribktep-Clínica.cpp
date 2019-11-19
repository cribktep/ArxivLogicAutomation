/*************************************************************************************************************
 *                                                                                                           * 
 *        Design of the basic implementation of a nonrelational database and its management system (SGBD).   *
 *                                                                                                           *
 *        Using as an example, the design of a functional program of an                                      *
 *        administration system for a medical clinic.                                                        * 
 *                                                                                                           *
 *        Designer and Programmer: Cribktep (Fran Cruz).                                                     * 
 *        Platform: All Windows S.O versions.                                                                *
 *************************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WINDOWS
    #define WINDOWS
#endif
/* 
#ifndef UNIX
    #define UNIX 
#endif
*/

typedef struct variablesmed{
         char nombreM[130];
         char nombreP[130];
         int dniM;
         int dniP;
        }storage;
        
typedef struct nodo_medicos{
         int dni; 
         char nombre[130];
         struct nodo_medicos *next;
        }medicos;
        
typedef struct nodo_pacientes{
         int dni;
         int dniM;
         char nombre[130];
         struct nodo_pacientes *next;
        }pacientes;
                
int add_nodM(medicos **primero,storage info);
int add_nodP(pacientes **primero,storage info);
int see_listM(void *primero);
int see_listP(pacientes *primero);
int insert_fic(medicos *primero);
int insert_ficP(pacientes *primero);
int read_fic(medicos **primero); 
int read_ficP(pacientes **primero);



storage pedir_datos(int opc,medicos *primero, pacientes *primeroP); 

/* Busque en la base de datos - booleanos: 0 para medicos y 1 para pacientes */
int search_listM(medicos *primero,int dni);
int search_listP(pacientes *primero,medicos *primeroM,int dni);

int del_listP(pacientes **primero,int dni);
int del_listM(medicos **primero,pacientes **primeroP,int dni);

/* Validación de DNI, 0 para validar que no este en ninguna lista y 1 para comprobar que este en la lista Médicos */
bool val_dni(void *primero,int dni,bool opc); 

void menu(void);

int main(){
    medicos *primero,*ver;
    pacientes *primeroP,*verP;
    storage info;
    bool bo;
    char tempnum[11];
    int dni;
    char op;

    primero = NULL;
    primeroP = NULL;
    
    read_fic(&primero);
    read_ficP(&primeroP);
    
    do{
    #ifdef WINDOWS
     system("cls");
    #elif defined UNIX
     system("clear");
    #endif
         menu();
         switch(op = getchar()){
                   case 'a': case 'A':       
                        while(getchar()!='\n');
                        info = pedir_datos(0,primero,primeroP);
                        add_nodM(&primero,info);
                        
                        if(insert_fic(primero) == 0){
                         printf("Error al insertar los datos en el archivo.Pulse una tecla para continuar");
                          }else{
                            printf("Los datos fueron agregados correctamente.Pulse una tecla para continuar");
                            }
                         break;
                   case 'b': case 'B':
                        while(getchar()!='\n');
                        info = pedir_datos(1,primero,primeroP);
                        add_nodP(&primeroP,info);
                        if(insert_ficP(primeroP) == 0){
                         printf("Error al insertar los datos en el archivo. Pulse una tecla para continuar.");
                           }else{
                             printf("Los datos fueron agregados correctamente.Pulse una tecla para continuar.");
                             }
                         break;
                   case 'c': case 'C':
                        printf("\n\t\tIntroduzca el dni del medico a buscar: ");
                        /* Lo que hago con esta sentencia es avanzar posiciones en studin sin llegar a tocar 
                           el salto de linea de este, de esa forma no habra un salto de linea en stdin y fgets 
                           funcionará correctamente. */
                        while(getchar()!='\n'); 
                        fgets(tempnum,11,stdin);
                        if (tempnum[strlen(tempnum)-1] == '\n')
                           tempnum[strlen(tempnum)-1] = '\0';
                        sscanf(tempnum,"%d",&dni); 
                        printf("\n\n\t\t");
                        search_listM(primero,dni);
                        printf("\n\n\t\tPulse una tecla para continuar.");
                        //getchar();
                        break;
                   case 'd': case 'D':
                        printf("\n\t\tIntroduzca el dni del paciente a buscar: ");
                        while(getchar()!='\n');
                        fgets(tempnum,11,stdin);
                        if (tempnum[strlen(tempnum)-1] == '\n')
                           tempnum[strlen(tempnum)-1] = '\0';
                        sscanf(tempnum,"%d",&dni); 
                        search_listP(primeroP,primero,dni);
                        printf("Pulse una tecla para continuar.");
                        getchar();
                        break;

                   case 'e': case 'E':
                        printf("\n\t\tIntroduzca el dni del medico que desea borrar: ");
                        while(getchar()!='\n');
                        fgets(tempnum,11,stdin);
                        if (tempnum[strlen(tempnum)-1] == '\n')
                           tempnum[strlen(tempnum)-1] = '\0';
                        sscanf(tempnum,"%d",&dni);
                        if(del_listM(&primero,&primeroP,dni) == 0 || insert_fic(primero) == 0 /*|| insert_ficP(primeroP) == 0*/){printf("El medico no se puda borrar o bien por que no existe o por que dio error.");}
                          else{
                               printf("El medico se borro correctamente.");
                          }
                        
                        break;
                   case 'f': case 'F':
                        printf("\n\t\tIntroduzca el dni del paciente que desea borrar: ");
                        while(getchar()!='\n');
                        fgets(tempnum,11,stdin);
                        if (tempnum[strlen(tempnum)-1] == '\n')
                           tempnum[strlen(tempnum)-1] = '\0';
                        sscanf(tempnum,"%d",&dni);
                        if(del_listP(&primeroP,dni) == 0 || insert_ficP(primeroP) == 0){printf("El paciente no se puda borrar o bien por que no existe o por que dio error.");}
                          else{
                               printf("El paciente se borro correctamente.");
                          }
                        break;
                   case 'g': case 'G':
                        see_listM(primero);
                        printf("\n\n\t\tPresione una tecla para continuar.");
                        getchar();
                        break;
                   case 'h': case 'H':
                       see_listP(primeroP);
                       printf("\n\n\t\tPresione una tecla para continuar.");
                       getchar();
                       break;
                  case 's': case 'S':
                       return 0;
                       break;
                  default:
                        printf("\n\n\t\tLa opcion elegida no es correcta.Pulse una tecla.");
                        getchar();
                        break;
                   }
          op = getchar();
         }while(1);
}

int add_nodM(medicos **primero,storage info){
    medicos *nuevo,*aux;
    /* Convierto a un puntero que apunte a medicos, con (medicos *) por que el sizeof que yo realizo
    es un puntero, es decir yo hago un sizeof a un bloque de datos no a un dato simple por tanto para que
    sizeof pueda averiguar el tamaño de ese bloque de datos tengo que tener la dirección de memória (es decir, 
    un puntero de dicho bloque) */
    if((nuevo = (medicos *) malloc (sizeof(medicos))) == NULL){return 0;}
    
    if(nuevo == NULL){return 0;}
    
    /* Datos de la lista */
       nuevo->dni = info.dniM;
       strcpy(nuevo->nombre,info.nombreM);
       nuevo->next = NULL;       
    /* Algoritmo para insertar */
       
       aux = *primero;
 
       while(aux != NULL){
         if(aux->dni == info.dniM){return 0;};
         aux = aux->next;
        }
 
        /* Creación del nodo */
        if(*primero == NULL){
             *primero = nuevo;
             return 1;
            } else {
                   aux = *primero;
                   while(aux->next != NULL){
                   aux = aux->next;
              }
              aux->next = nuevo; /* La posicion de aux que apunte a NULL hago que apunte a toda la estructura nuevo*/
              return 1;
             }
}

/* Tengo que hacer una doble indirección por que yo que pasarle el valor a la función por referéncia
para trabajar con la lista, pero primero resulta que ya es un puntero a una estructura (en este caso
un puntero a una lista) por lo que tengo que hacer una indirecciín multiple, es decir pasar la dirección de memoría
del puntero que apunta a la lista */


int add_nodP(pacientes **primero,storage info){
 pacientes *nuevo,*aux;
 
 if((nuevo = (pacientes *) malloc(sizeof(pacientes))) == NULL){return 0;}
 
 /* Datos del nodo */
 nuevo->dni = info.dniP;
 nuevo->dniM = info.dniM;
 strcpy(nuevo->nombre,info.nombreP);
 nuevo->next = NULL;
 
 /* Algoritmo para insertar */
       
 aux = *primero;
 
 while(aux != NULL){
    if(aux->dni == info.dniP){return 0;};
    aux = aux->next;
   }
 
   /* Creación del nodo */
   if(*primero == NULL){
               *primero = nuevo;
                return 1;
    } else {
           aux = *primero;
           while(aux->next != NULL){
           aux = aux->next;
          }
   aux->next = nuevo; /* La posicion de aux que apunte a NULL hago que apunte a toda la estructura nuevo*/
   return 1;
 }
}


int see_listM(void *primero){
      medicos *auxiliar;
      
      /* Esto es un ejemplo de como usar la conversion de punteros 'void' */
      auxiliar = (medicos *)primero;
      if (auxiliar == NULL) {printf( "\t\tLa lista esta vacia!!\n" ); return 0; }
      while (auxiliar!=NULL) {
             printf("\t\tDNI: %d \t Nombre: %s \n",auxiliar->dni,auxiliar->nombre);
             auxiliar = auxiliar->next;
            }
     }

int see_listP(pacientes *primero){
      pacientes *auxiliar;
      
      auxiliar = primero;
      if (auxiliar == NULL) {printf("\t\tLa lista esta vacia!!\n" ); return 0; }
      while (auxiliar!=NULL) {
             printf("\t\tDNI: %d \t Nombre: %s \t Medico: %d \n",auxiliar->dni,auxiliar->nombre,auxiliar->dniM);
             auxiliar = auxiliar->next;
            }
     }


int insert_fic(medicos *primero){
 FILE *fp;
 medicos aux,*aux2;
 
 int b = 1;
 if((fp = fopen("clinica.bin","w+b")) == NULL){printf("Error al abrir el archivo"); return 0;}
 aux2 = primero;

 while(aux2 != NULL){
  aux = *aux2;
  /* fseek lo que hace es escribir al final de fichero, 
  lo puedo quitar para que el fichero se sobreescriba 
  para usar fseek de esta forma no debo usar en fread
  en la condicion del bucle cuando aux.next != NULL 
  fseek (fp, 0L, SEEK_END); 
  */

  b = fwrite(&aux,sizeof(medicos),1,fp);
  if(b < 1){printf("error"); return 0;}
  aux2 = aux2->next;
 }
 fclose(fp);
 return 1;
}


int read_fic(medicos **primero){
 FILE *fp;
 storage info_medico;
 medicos *aux,aux2;
 if((fp = fopen("clinica.bin","r+b")) == NULL){printf("Error al abrir el archivo");  return 0;}
 fseek (fp, 0L, SEEK_SET);
 
 while(1){ 
   if(fread(&aux2,sizeof(medicos),1,fp) < 1){fclose(fp); return 1;}
   info_medico.dniM = aux2.dni;
   strcpy(info_medico.nombreM,aux2.nombre);
   add_nodM(primero,info_medico);
 }
 
}

int insert_ficP(pacientes *primero){
 FILE *fp;
 pacientes aux,*aux2;
 
 int b = 0;
 if((fp = fopen("clinicaP.bin","w+b"))==NULL){printf("Error al abrir el archivo"); return 0;}

 aux2 = primero;

 while(aux2 != NULL){
  aux = *aux2;
  b = fwrite(&aux,sizeof(pacientes),1,fp);
  if(b < 1){printf("error"); return 0;}
  aux2 = aux2->next;
 }
 fclose(fp);
 return 1;
}

int read_ficP(pacientes **primero){
 FILE *fp;
 storage infoP;
 int a = 1;
 pacientes *aux,aux2;
 
 if((fp = fopen("clinicaP.bin","r+b")) == NULL) {printf("Error al abrir el archivo"); return 0;}
 fseek (fp, 0L, SEEK_SET);

 /* Es mejor usar este fragmento, ya que en caso de fallo de la función: fread hay menos posibilidades de que se
 produzca fallo de segmentación */
 
  while(1){ 
   if(fread(&aux2,sizeof(pacientes),1,fp) < 1){fclose(fp); return 1;}
   infoP.dniP = aux2.dni;
   strcpy(infoP.nombreP,aux2.nombre);
   infoP.dniM = aux2.dniM;
   add_nodP(primero,infoP);
  }
}

storage pedir_datos(int opc,medicos *primero, pacientes *primeroP){
         medicos *aux;
         storage info;
         int numeros = 0;

         char temp[140];

         printf("Inserte datos personales\n");
         do{
          printf("Inserte DNI (8 numeros): ");
          fgets(temp,11,stdin);
          if (temp[strlen(temp)-1] == '\n')
           temp[strlen(temp)-1] = '\0';
           sscanf(temp,"%d",&numeros); // lo uso para convertir cadena de texto en un entero
           if(!temp[1]){ printf("\nEl campo DNI no puede dejarse vacio. Pulse Enter para continuar.\n"); getchar(); }
           if(val_dni(primero,numeros,0) == 1 || val_dni(primeroP,numeros,1) == 1 ){printf("\nEl dni introducido ya existe.\n\n");}
          }while(!temp[1] || val_dni(primero,numeros,0) == 1 || val_dni(primeroP,numeros,1) == 1);
         if(opc == 0){
                 info.dniM = numeros;
                } else{
                     info.dniP = numeros;
                }
         do{
             printf("Inserte nombre : ");
             fgets(temp,129,stdin);
             if(temp[strlen(temp)-1] == '\n'){temp[strlen(temp)-1] = '\0';}
             if(!temp[1]) {printf("\nEl campo nombre no puede dejarse vacio. Pulse Enter para continuar.\n");}
            }while(!temp[1]);
         if(opc == 0){
                 strcpy(info.nombreM,temp);
                } else{
                      strcpy(info.nombreP,temp);
                     }
         
         if(opc == 1){
                  do{
                     printf("Inserte DNI del medico (8 numeros): ");
                     fgets(temp,11,stdin);
                     if (temp[strlen(temp)-1] == '\n')
                        temp[strlen(temp)-1] = '\0';
                     sscanf(temp,"%d",&numeros); 
                     if(!temp[1]){ printf("\nEl campo DNI no puede dejarse vacio. Pulse Enter para continuar.\n"); getchar(); }
                     if(val_dni(primero,numeros,0) == 0){printf("\nEl medico no existe.\n\n");}
                  }while(!temp[1] || val_dni(primero,numeros,0) == 0);
                  info.dniM = numeros;
                }
         
    
     return info;
  }

int search_listM(medicos *primero,int dni){
      medicos *aux;
      int flag = 0;

      if(primero == NULL){printf("\n\t\tLa lista esta vacia."); return 0;}
      
      aux = primero;
      while(aux->next != NULL){
        if(aux->dni == dni){
         printf("DNI: %d \t Nombre: %s",aux->dni,aux->nombre);
         flag = 1;
        }
        aux = aux->next;
       }
      if(flag == 0){printf("\nNo se encontro el medico buscado.\n");}
     }

int search_listP(pacientes *primero,medicos *primeroM,int dni){
      pacientes *aux;
      medicos *auxM;
      int flag = 0;
      char nombre[130];
      

      
      if(primero == NULL){printf("\n\t\tLa lista esta vacia."); return 0;}
      aux = primero;
     
      while(aux->next != NULL){
        if(aux->dni == dni){
         auxM = primeroM;
         while(auxM->next != NULL || auxM->dni == aux->dniM){
                          if(auxM->dni == aux->dniM){strcpy(nombre,auxM->nombre);}
                          auxM = auxM->next;
         }
         
         printf("DNI: %d \t Nombre: %s \t Medico: %s",aux->dni,aux->nombre,nombre);
         flag = 1;
        }
        aux = aux->next;
       }
      if(flag == 0){printf("\nNo se encontro el paciente buscado.\n");}
     }

bool val_dni(void *primero,int dni,bool opc){
    medicos *auxM;
    pacientes *auxP;
    int m = 0;
    int p = 0;

    /* Para la validación uso los siguientes valores booleanos:
       0 para medicos, 1 para pacientes.
       0 si, NO existe, 1 si, SI existe.   
    */
    
    if(opc == 1){
                
           auxP = (pacientes *)primero;
           while(auxP != NULL){
                        if(auxP->dni == dni){ return 1; }
                        auxP = auxP->next;
                     }
           return 0; 
    }else{
          auxM = (medicos *)primero;
          while(auxM != NULL){
                        if(auxM->dni == dni){return 1; }
                        auxM = auxM->next;
                     }
          return 0;
    }
}


int del_listP(pacientes **primero,int dni){
      pacientes *aux,*ant;
      
       if(val_dni(*(primero),dni,1) == 0 || primero == NULL )
         return 0;
         
      ant = *primero;
      if(ant->dni == dni){
           *primero = ant->next;
           free(ant);
      } else{
             while(ant->next->dni != dni && ant != NULL){ 
              ant = ant->next;
             }
            aux = ant->next;
            ant->next = ant->next->next;
            free(aux);
        }
       return 1;
      }

int del_listM(medicos **primero,pacientes **primeroP,int dni){
      medicos *aux,*ant;
      pacientes *auxP,*antP;
      
      /* Si el DNI introducido no existe: */
      if(val_dni(*(primero),dni,0) == 0 || primero == NULL) /* Para desreferenciar un puntero uso: *(puntero) */
         return 0;
      
      ant = *primero;
      if(ant->dni == dni){
           *primero = ant->next;
           free(ant);
      } else{ 
             while(ant->next->dni != dni && ant != NULL){
              ant = ant->next;
             }
              aux = ant->next;
              ant->next = ant->next->next;
              free(aux);
        }     
          antP = *primeroP;
          
          if(antP == NULL){return 1;}
           while(antP->next != NULL){
                    if(antP->dniM == dni){
               *primeroP = antP->next;
               free(antP);
               antP = *primeroP;
              } else{
                   if(antP->next->dniM == dni ){
                     del_listP(primeroP,antP->next->dni);
                     antP = *primeroP;
                    }else{
                         antP = antP->next;
                    }
                   }        
               }
           if(antP->dniM == dni){
               *primeroP = antP->next;
               free(antP);
               antP = *primeroP;
              }   
            return 1;  
                       
    }
    
void menu(void){
      printf("\n\n\t\t------------------------------------------------\n");
      printf("\t\t----------------- Elija una opcion -------------\n");
      printf("\t\t------------------------------------------------\n");
      printf("\t\t-----------   a - Insertar Medico.   -----------\n");
      printf("\t\t-----------   b - Insertar Paciente. -----------\n");
      printf("\t\t-----------   c - Buscar Medico.     -----------\n");
      printf("\t\t-----------   d - Buscar Paciente.   -----------\n");
      printf("\t\t-----------   e - Eliminar Medico.   -----------\n");
      printf("\t\t-----------   f - Eliminar Paciente. -----------\n");
      printf("\t\t-----------   g - Listar Medicos.    -----------\n");
      printf("\t\t-----------   h - Listar Pacientes.  -----------\n");
      printf("\t\t-----------   s - Salir.             -----------\n");
      printf("\t\t------------------------------------------------\n");
      printf("\t\t------------------------------------------------\n");
      
      printf("\n\t\tElija una opcion: ");
     }

