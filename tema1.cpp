// Copyright 2018 <Negru Bogdan Cristian 312CA>

#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

class Command {
 public:
    int id;
    int x;
    int y;
    int nr_boxes;
    int priority;
    char name[15];
    int executed_boxes;
    int contor;
    int timp;

        Command() {
            id = -1;
            x = -1;
            y = -1;
            nr_boxes = 0;
            priority = -12;
            executed_boxes = 0;
            contor = 0;
            timp = 0;
        }
  
};

#include "resizableArray.h"
#include "linkedlist.h"

template <class T>
class Robot {
 public:
    int id;
    int boxes_in_hands;
    Queue<T> coada;
    Stack<T> stiva;
    Stack<T> executed;

    Robot() {
        id = -1;
        boxes_in_hands = 0;
    }
};


int main(){

    FILE *in, *out;
    in = fopen("robots.in", "rt");
    if (in == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", "robots.out");
        return -1;
    }

    out = fopen("robots.out", "wt");

    if (out == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", "robots.out");
        return -1;
    }

 
    Robot<Command> robot, *aux_robot;
    int N, LIN, COL, i, j;
    fscanf(in, "%d %d %d", &N, &LIN, &COL);

    int **map;
    map = new int*[LIN];

    for (int i = 0; i < LIN; i++) {
        map[i] = new int[COL];
    }

  for ( i = 0; i < LIN; i++) {
    for ( j = 0; j < COL; j++) {

            fscanf(in, "%d", &map[i][j]);
    }
  }

    aux_robot = new Robot<Command>[N];

    for( i = 0; i < N; i++) {
        aux_robot[i].id = i;
    }
       
    char request[15], s[5];
    int id, priority, nr_boxes, x, y, time_contor = 0, timp = 0;

    Command command, aux_command, last_executed_command;
    last_executed_command.priority = -1;
                // prioritatea -1 pt last_executed_command inseamna ca nu a fost efectuata nicio comanda

    while (feof(in) == 0) {
        
        fscanf(in, "%s", request);             //citesc pt inceput numele comenzii, iar in functie de acesta 
                                               // citesc si restul datelor
         if( feof(in) != 0) {
                break;
            }
 
            if( strcmp(request, "ADD_GET_BOX") == 0 || 
                strcmp(request, "ADD_DROP_BOX") == 0) {

                       fscanf (in, "%d %d %d %d %d", &id, &x, 
                               &y, &nr_boxes, &priority);
                       strcpy(command.name, request);
                       command.id = id;
                       command.x = x;                                  //pun datele citite intr-o variabila de tip Command
                       command.y = y;
                       command.nr_boxes = nr_boxes;
                       command.priority = priority;
                       robot.coada.enqueue1(command);                 //adaug toate comenzile intr-o coada
                                                                  //metoda enqueue1 nu tine cont de prioritate

            }

            if(strcmp(request, "EXECUTE") == 0){
                fscanf (in, "%d", &id);
                command.id = id;
                strcpy(command.name, request);
                command.x = 0;
                command.y = 0;
                command.nr_boxes = 0;
                command.priority = 1;
                robot.coada.enqueue1(command);

            }

             if(strcmp(request, "UNDO") == 0){

                 strcpy(command.name, request);
                 command.priority = 1;
                 robot.coada.enqueue1(command);
            
               }


             if(strcmp(request, "LAST_EXECUTED_COMMAND") == 0){
                strcpy(command.name, request);
                command.x = 0;
                command.y = 0;
                command.priority = 1;
                robot.coada.enqueue1(command);
            }

             if(strcmp(request, "HOW_MUCH_TIME") == 0){
                strcpy(command.name, request);
                command.x = 0;
                command.y = 0;
                command.nr_boxes = 0;
                command.priority = 1;
                robot.coada.enqueue1(command);
            }
             if(strcmp(request, "HOW_MANY_BOXES") == 0){
                fscanf(in, "%d", &id);
                 strcpy(command.name, request);
                 command.id = id;
                 command.x = 0;
                command.y = 0;
                command.nr_boxes = 0;
                command.priority = 1;
                robot.coada.enqueue1(command);
            }

            if( strcmp(request, "PRINT_COMMANDS") == 0){
                fscanf(in, "%d", &id);
                command.id = id;
                strcpy(command.name, request);
                command.x = 0;
                command.y = 0;
                command.nr_boxes = 0;
                command.priority = 1;
                robot.coada.enqueue1(command);
            }

    }
     
        while (robot.coada.size() > 0){
            command = robot.coada.dequeue();                     // parcurg coada
            time_contor++;             // variabila time_contor contorizeaza numarul de comenzi

/////// ADD AND DROP

            if( strcmp(command.name, "ADD_GET_BOX") == 0 || strcmp(command.name, "ADD_DROP_BOX") == 0) {

                id = command.id;    
                command.contor = time_contor;
                robot.stiva.push(command);
                aux_robot[id].coada.enqueue(command);
              
               
            }
            // daca comanda a fost de tip ADD ii retin pozitia din coada si o pun
            // intr-o stiva(ce contine comenzi de tipul ADD sau EXECUTE),
            // apoi o pun in coada robotului caruia i se adreseaza

/////// EXECUTE
            if (strcmp(command.name, "EXECUTE") == 0) {
                id = command.id;
                
                if(aux_robot[id].coada.size() == 0) {
                    fprintf(out, "EXECUTE: No command to execute \n");
                }
                else {

                aux_command = aux_robot[id].coada.dequeue();
                robot.stiva.push(command);
                    
                    if (strcmp(aux_command.name, "ADD_GET_BOX") == 0) {
                        
                         if (map[aux_command.x][aux_command.y] >= aux_command.nr_boxes) {
               
                            map[aux_command.x][aux_command.y] -= aux_command.nr_boxes;
                            aux_robot[id].boxes_in_hands += aux_command.nr_boxes;
                            aux_command.executed_boxes = aux_command.nr_boxes;
                        }
                        else {
                            aux_robot[id].boxes_in_hands += map[command.x][command.y];
                            aux_command.executed_boxes = map[command.x][command.y];
                            map[aux_command.x][aux_command.y] = 0;
                            }

                    }

                    if (strcmp(aux_command.name, "ADD_DROP_BOX") == 0) {
          
                        if(aux_robot[id].boxes_in_hands >= aux_command.nr_boxes){

                        aux_robot[id].boxes_in_hands -= aux_command.nr_boxes;
                        map[aux_command.x][aux_command.y] += aux_command.nr_boxes;
                        aux_command.executed_boxes = -aux_command.nr_boxes;
                        }
                        else {
                            map[aux_command.x][aux_command.y] += aux_robot[id].boxes_in_hands;
                            aux_command.executed_boxes = -aux_robot[id].boxes_in_hands;
                            aux_robot[id].boxes_in_hands = 0;
                        }


                    }
                    if (last_executed_command.priority != -1)
                        robot.executed.push(last_executed_command);
                    
                     timp = time_contor - aux_command.contor; 
                    aux_command.timp = timp;   

                    last_executed_command = aux_command;

                
                    }
               
            }
            //daca comanda a fost de tip EXECUTE verific daca in coada robotului caruia i se adreseaza sunt elemente, iar
            // daca sunt pun comanda pe stiva si scot din coada primul element("aux_command") si il execut
            //daca am mai vreo comanda executata o pun intr-o alta stiva ("executed")
            //ii calculez timpul pana la executare (adica iteratia curenta minus iteratia la care a intrat in coada)
            // si retin aux_command in variabila last_executed_command
            // "executed_boxes" poate fi si negativ pt ca in caz de undo sa pot pune mai usor cutiile la loc
            // am ales negativ pt "DROP"


///////PRINT_COMMANDS
            if (strcmp(command.name, "PRINT_COMMANDS") == 0) {
                id = command.id;
                 
                if(aux_robot[id].coada.size() == 0) {
                    fprintf(out, "PRINT_COMMANDS: No command found \n");
                } 
                else {
                    fprintf(out, "PRINT_COMMANDS: %d: ", command.id);
                
                for ( i = 0; i < aux_robot[id].coada.size(); i ++) {
                    aux_command = aux_robot[id].coada.peek(i);
                    
                    if( strcmp(aux_command.name, "ADD_GET_BOX") == 0){
                         strcpy(s, "GET");
                    }

                     if( strcmp(aux_command.name, "ADD_DROP_BOX") == 0){
                         strcpy(s, "DROP");
                    }
                    if (i + 1 == aux_robot[id].coada.size()) {
                        fprintf(out, "%s %d %d %d", s, aux_command.x, aux_command.y, aux_command.nr_boxes);
                    }
                    else {
                        fprintf(out, "%s %d %d %d; ", s, aux_command.x, aux_command.y, aux_command.nr_boxes);
                    }
                   
                }
                fprintf(out, "\n");

            }

            }
            //parcurg coada robotului caruia i se adreseaza si afisez comenzile


////////LAST_EXECUTED_COMMAND

            if (strcmp(command.name, "LAST_EXECUTED_COMMAND") == 0){
                
                if (last_executed_command.priority == -1) {
                    fprintf(out, "LAST_EXECUTED_COMMAND: No command was executed\n");

                } else {

                    if( strcmp(last_executed_command.name, "ADD_GET_BOX") == 0){
                         strcpy(s, "GET");
                    }

                     if( strcmp(last_executed_command.name, "ADD_DROP_BOX") == 0){
                         strcpy(s, "DROP");
                    }
                    if (last_executed_command.executed_boxes < 0){
                        last_executed_command.executed_boxes = -last_executed_command.executed_boxes;

                    fprintf(out, "LAST_EXECUTED_COMMAND: %d: %s %d %d %d\n", last_executed_command.id, s,
                    last_executed_command.x, last_executed_command.y, last_executed_command.executed_boxes);

                    last_executed_command.executed_boxes = -last_executed_command.executed_boxes;
                    }
                    else {
                              fprintf(out, "LAST_EXECUTED_COMMAND: %d: %s %d %d %d\n", last_executed_command.id, s,
                    last_executed_command.x, last_executed_command.y, last_executed_command.executed_boxes);
                    }
                }
                
        }

        // afisez ultima comanda executata, avand grija sa afisez numarul de cutii executate pozitiv

//////UNDO

            if (strcmp(command.name, "UNDO") == 0) {
                if(robot.stiva.size() >= 0) {

                aux_command = robot.stiva.pop();    // scot ultima comanada din stiva pt ADD sau EXECUTE

                if(strcmp(aux_command.name, "ADD_GET_BOX") == 0 || strcmp(aux_command.name, "ADD_DROP_BOX") == 0) {
                    if (aux_command.priority == 0)
                        aux_robot[aux_command.id].coada.dequeue();

                   if (aux_command.priority == 1)
                        aux_robot[aux_command.id].coada.dequeue_last();

                }
                // daca este ADD scot comanda din coada robotului ei in functie de prioritate

                else {

                if (last_executed_command.priority == -1) {
                    fprintf(out, "UNDO: No history\n");

                } else {
                map[last_executed_command.x][last_executed_command.y] += last_executed_command.executed_boxes;
                aux_robot[last_executed_command.id].boxes_in_hands += -last_executed_command.executed_boxes;

                last_executed_command.contor = time_contor;
                last_executed_command.priority = 0;

                if (last_executed_command.executed_boxes < 0){
                        
                last_executed_command.nr_boxes = -last_executed_command.executed_boxes;
              aux_robot[last_executed_command.id].coada.enqueue(last_executed_command);

                }
                else {
                         last_executed_command.nr_boxes = last_executed_command.executed_boxes;
              aux_robot[last_executed_command.id].coada.enqueue(last_executed_command);
                }

                if(robot.executed.size() > 0) 
              last_executed_command = robot.executed.pop();
                else 
                    last_executed_command.priority = -1; 
            }
            }
            }
            else {
                fprintf(out, "UNDO: No history\n");
            }
        }
        // daca comanda este EXECUTE pun la loc cutiile daca a existat o ultima comanda executata, ii reactualizez 
        // timpul de intrare in coada, pun prioritatea 0 pt a intra la inceput, setez nrboxes ca fiind nr de cutii executate
        // cu valoare pozitiva si adaug comanda in coada robotului caruia i se adreseaza
        // reactualizez "last_executed_command" din stiva de comenzi executate


/////HOW MANY BOXES

            if (strcmp(command.name, "HOW_MANY_BOXES") == 0) {
                fprintf (out, "HOW_MANY_BOXES: %d\n", aux_robot[command.id].boxes_in_hands);
            }

        
/////HOW MUCH TIME

        if (strcmp(command.name, "HOW_MUCH_TIME") == 0) {
            if(last_executed_command.timp == 0) {
                fprintf (out, "HOW_MUCH_TIME: No command was executed\n");
            }
            else {
            fprintf (out, "HOW_MUCH_TIME: %d\n", last_executed_command.timp);

            }
        }


        }



    
    for ( i = 0; i < LIN; i++) {
        delete[] map[i];
    }
    delete[] map;
    delete[] aux_robot;

 
    fclose(in);
    fclose(out);
    



    return 0;
}