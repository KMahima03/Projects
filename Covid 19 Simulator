#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 10000
#define MAX_EDGES 3000
#define MAX_TIME 300
#define TRANSMIT_EVENT 1
#define RECOVER_EVENT 2


// this is used to maintain the infected, susceptible and recovery list
struct list {
   int vertex;
   struct list *nextl;       // next pointer in list
};

// here priority queue is an event queue maintains all the events with respective priorities(lower the time(no of days to process that event) higher the priority)
typedef struct priority_queue {
   int event;                     // event 1 is transmit event(susceptible to infected), and event 2 is recovery event(infected to recovered)
   int vertex;
   int time;
   struct priority_queue *nextq;  // next pointer in queue
} pqueue; 



// function that adds new infected nodes to the infected list
struct list* add_to_infectedlist(struct list *head, int val) {
   struct list *temp, *lastptr, *temp1;
   if(head == NULL) {
      temp = malloc(sizeof(struct list));
      temp->vertex = val;
      temp->nextl = NULL;
      head = temp;
   }
   
   else {
      // when we add we check that the vertex to be added is not already in the list(since we choose them randomly) to avoid repetition
      temp = head;
      while(temp != NULL) {
         if(temp->vertex == val) {
            return NULL;
         }
         temp = temp->nextl;
      }  
      
      // if not we add it to the infected list (a linked list) 
      temp = head;
      while(temp->nextl != NULL) {
         temp = temp->nextl;
      }
      lastptr = temp;
      temp1 = malloc(sizeof(struct list));
      temp1->vertex = val;
      temp1->nextl = NULL;
      lastptr->nextl = temp1;
   }
   return temp;
}


// function that adds new susceptible nodes to the susceptible list
void add_to_susceptiblelist(struct list **sushead, struct list *inhead, struct list *rechead, int val) {
   struct list *temp, *lastptr, *temp1, *temp2, *temp3, *tempr;
   
   /* we check that the new vertex to be added is NOT already present in infected, susceptible of recovery lists. This is because:
         when new nodes get infected, all their neighbours are added to the susceptible list. So we check that those neighbours are not already 
         infected or susceptible or recovered , if so we cannot add them to the susceptible list again*/
         
   if(*sushead == NULL) {
      temp1 = inhead;
      while(temp1 != NULL) {
         if(temp1->vertex == val) {
            return;
         }
         temp1 = temp1->nextl;
      }
      
      tempr = rechead;
      while(tempr != NULL) {
         if(tempr->vertex == val) {
            return;
         }
         tempr = tempr->nextl;
      }
      
      temp = malloc(sizeof(struct list));
      temp->vertex = val;
      temp->nextl = NULL;
      *sushead = temp;
   }
   
   else {
      // we check if its present in infected list
      temp1 = inhead;
      while(temp1 != NULL) {
         if(temp1->vertex == val) {
            return;
         }
         temp1 = temp1->nextl;
      }
      
      // we check if its present in recovery list
      tempr = rechead;
      while(tempr != NULL) {
         if(tempr->vertex == val) {
            return;
         }
         tempr = tempr->nextl;
      }
      
      // we check if its present in susceptible list
      temp3 = *sushead;
      while(temp3 != NULL) {
         if(temp3->vertex == val) {
            return;
         }
         temp3 = temp3->nextl;
      }
      
      // if not only then we add them to susceptible list(which is a linked list)
      temp = *sushead;
      while(temp->nextl != NULL) {
         temp = temp->nextl;
      }
      lastptr = temp;
      temp2 = malloc(sizeof(struct list));
      temp2->vertex = val;
      temp2->nextl = NULL;
      lastptr->nextl = temp2;
   }

}


// function that adds new recovered nodes to the recovery list
struct list* add_to_recoverylist(struct list *head, int val) {
   struct list *temp, *lastptr, *temp1;
   
   // we need not check for repitition here because once recovery event comes in the event queue the infected node gets recovered and \
       no repitition happens because we already checked in the infected list  \
       So we directly add to the recovery list(a linked list)
   
   if(head == NULL) {
      temp = malloc(sizeof(struct list));
      temp->vertex = val;
      temp->nextl = NULL;
      head = temp;
   }
   
   else {      
      temp = head;
      while(temp->nextl != NULL) {
         temp = temp->nextl;
      }
      lastptr = temp;
      temp1 = malloc(sizeof(struct list));
      temp1->vertex = val;
      temp1->nextl = NULL;
      lastptr->nextl = temp1;
   }
   
   return temp;   
}


// a function used to delete a node from a linked list
void delete_from_list(struct list **head, int val) {
   struct list *temp_pr, *temp_cu, *temp_del;
   // pr- previous pointer, cu - current pointer, del - the one to be deleted
   
   temp_pr = *head;
   
   if((*head) == NULL) {
      return;
   }
   
   temp_cu = (*head)->nextl;
   
   if((*head)->vertex == val) {
      temp_del = (*head);
      *head = (*head)->nextl;
      free(temp_del);
   }
   
   else {
      while (temp_cu != NULL && temp_cu->vertex != val) {
         temp_pr = temp_pr->nextl;
         temp_cu = temp_cu->nextl;
      }
      
      if (temp_cu != NULL) {
         temp_del = temp_cu;
         temp_pr->nextl = temp_cu->nextl;
         free(temp_del);
      }
   }

}


// function to generate a random number of days with the given probability (p = 0.2 for recovery) and (p = 0.5 for transmit)
int event_time(int event) {
   int count, r;
   count = 0;
   // count is the total number of days required for that event to process
   
   if(event == RECOVER_EVENT) {
      do {
        r = rand() %5;
        count++;
      } while (r != 1);
   }
   
   else if(event == TRANSMIT_EVENT) {
      do {
        r = rand() %2;
        count++;
      } while (r != 1);
   }
   
   return count;
}


// a function that adds a new node to the priority queue given the vertex, event, and day \
   the nodes are added according to the priority(least number of days) that is randomly generated    
pqueue* add_to_prqueue(pqueue *head, int vertex_val, int event, int extradays) {
   pqueue *temp, *tempnew, *tempx;
   int priority;
   // we assign the event time and that day as the priority('extra days' is the day when that node is added to the queue )
   priority = (event_time(event)) + extradays;
   tempnew = malloc(sizeof(pqueue));
   tempnew->event = event;
   tempnew->vertex = vertex_val;
   tempnew->time = priority;
   
   // we check if we are not repeating that vertex
   tempx = head;
   while(tempx != NULL) {
      if(tempx->vertex == vertex_val) {
         return NULL;
      }
      tempx = tempx->nextq;
   }
   
   if(head == NULL) {
      tempnew->nextq = NULL;      
      head = tempnew;
   }
   
   // if new vertex has more priority than head, we replace it with head
   else if(priority < head->time) {
      tempnew->nextq = head;
      head = tempnew;
   }
   
   // otherwise we check until we find right position to place(until we find a node with less priority) and then we add to queue 
   else {
      temp = head;
      while((temp->nextq != NULL) && (temp->nextq->time <= priority)) {
         temp = temp->nextq;
      }
      tempnew->nextq = temp->nextq;
      temp->nextq = tempnew;
      head = NULL;
   }
   return head;
}
      

// function to delete a node from the queue
void delete_from_queue(pqueue **head) {
   pqueue *temp;
   
   if(head != NULL) {
      temp = *head;
      *head = (*head)->nextq;
      free(temp);
   }
}


// function used to print a linked list
void print_list(struct list *head) {
   struct list *temp;
   temp = head;
   while(temp != NULL) {
      printf("%d ", temp->vertex);
      temp = temp->nextl;
   }
   printf("\n");
}
   

// a function that prints the queue elements in the order: time(no.of days), event, vertex
void print_queue(pqueue *head) {
   pqueue *temp;
   temp = head;
   while(temp != NULL) {
      printf("{%d,%d,%d}, ", temp->time, temp->event, temp->vertex);
      temp = temp->nextq;
   }
   printf("\n");
}


// a function for checking if the vertex is in the list (here recovery list)
int is_in_list(struct list *rec_head, int val) {
   struct list *tempr;
     
   tempr = rec_head;
   while(tempr != NULL) {
      if(tempr->vertex == val) {
         return 1;                      // that means it is present in the list 
      }
      tempr = tempr->nextl;
   }
   
   return 0;                            // that means it is not in the list
}



// Main function
int main() {
   int no_of_vertices, maxno_of_edges, no_of_edges, present_vertex, present_event, i, j, day, no_of_infected, infected_vertex;
   struct list *infected_head, *susceptible_head, *recovery_head, *temp, *temp1, *temp2;
   pqueue *pq_head, *ptemp2, *ptempx;
   
   srand(time(NULL));
   do {
      no_of_vertices = (rand() % MAX_VERTICES) + 1;
 
      //number of maximum edges a vertex can have
      maxno_of_edges = (rand() % MAX_EDGES) + 1;
    
      //graph is 2 dimensional array of pointers
      
   } while(no_of_vertices <= maxno_of_edges);      // since we can't have edges greater than vertices
        
   printf("Total Vertices = %d, Max # of Edges = %d\n",no_of_vertices, maxno_of_edges);
   
   unsigned char *graph[no_of_vertices];
    
   for(i =0; i<no_of_vertices; i++) {
      graph[i] = (unsigned char *) malloc(sizeof(unsigned char*) * no_of_vertices);
      for(j =0; j<no_of_vertices; j++) {
          graph[i][j] = 0;
      }
   }
   
   srand(time(NULL));
   
   // building the graph :- (basically an adjacent matrix given the maximum number of edges(again choosen randomly) for a vertex)
   for(i=0; i<no_of_vertices; i++) {
      no_of_edges = rand() % maxno_of_edges;
      for(j =0; j<=no_of_edges; j++) {
         present_vertex = rand() % no_of_vertices;
         if(graph[i][present_vertex] == 0) {
            graph[i][present_vertex] = 1;
            graph[present_vertex][i] = 1;
         }
      }
   }
   
   
   //----printing graph that is obtained for checking 
   /*
   printf("Adj martrix:\n");
   printf("   ");
   for (i=0; i<no_of_vertices; ++i) {
     printf("%4d", i);
   }
   printf("\n");
   for(i =0; i<no_of_vertices; i++) {
      printf("%3d", i);
      for(j =0; j<no_of_vertices; j++) {
         printf("%3d ", graph[i][j]);
      }
      printf("\n");
   } 
   printf("\n");
   */
   
      
   // we randomly take some x number of vertices to be infected
   no_of_infected = (rand() % no_of_vertices) + 1;
   printf("infected is %d\n", no_of_infected);
   // initialising all the head pointers of respective lists
   infected_head = NULL;
   susceptible_head = NULL;
   recovery_head = NULL;
   pq_head = NULL;
   
   // we now randomly choose a vertex and infect it to the infected list(while adding in add_to_infectedlist function we check that its not repeated)
   for(i=0; i<no_of_infected; i++) {
      infected_vertex = rand() % no_of_vertices;
      temp = add_to_infectedlist(infected_head, infected_vertex);
      if(infected_head == NULL) {
         infected_head = temp;
      }
   }
   
   /* since all the neighbours of infected vertices are susceptible to the disease we go to the graph(or adjacency matrix) and check for the neighbours
       and add to the susceptible list (while adding in add_to_susceptiblelist function we check that its not repeated and also 
       that its not already infected or recovered and only then we add it to the list) */
   temp1 = infected_head;
   while(temp1 != NULL) {
      for(j=0; j<no_of_vertices; j++) {  
         if(graph[temp1->vertex][j] == 1) {
            add_to_susceptiblelist(&susceptible_head, infected_head, recovery_head, j);
         }
      }
      temp1 = temp1->nextl;
   }  
    
   // now we add all the susceptible vertices to the priority queue one by one given the head pointer, vertex, event, and (priority which is number of days  \
       to process the event is randomly generated in the add-to-priority queue function itself)
   srand(time(NULL)); 
   temp1 = susceptible_head;
   while(temp1 != NULL) {
      ptemp2 = add_to_prqueue(pq_head, temp1->vertex, TRANSMIT_EVENT, 0);
      if(ptemp2 != NULL) {
         pq_head = ptemp2;
      }
      temp1 = temp1->nextl;
   } 
   
   // now we add all the infected vertices to the priority queue one by one given the queue head pointer, vertex, event(here event becomes recovery)  \
      and (priority which is number of days to process the event is randomly generated in the add-to-priority queue function itself)
   srand(time(NULL));
   temp1 = infected_head;
   while(temp1 != NULL) {
      ptemp2 = add_to_prqueue(pq_head, temp1->vertex, RECOVER_EVENT, 0);
      if(ptemp2 != NULL) {
         pq_head = ptemp2;
      }
      temp1 = temp1->nextl;
   }
     
   
   // we print all the lists at start
   printf("printing infected head:-\n");
   print_list(infected_head);
   printf("printing susceptible head:-\n");
   print_list(susceptible_head); 
   printf("printing event queue:-\n");
   print_queue(pq_head);  
   

/* ----------------SIMULATION:----------------------
     This is the simulation process. We process the event queue elements one by one.
     - If the present vertex is infected and event is recovery on that particular day, then we remove it from infected list and add it to recovery list.
     - If the present vertex is susceptible and the event is transmit on that day, then we remove it from susceptible list and add it to infected list and also..
       once the vertex becomes infected, then all its neighbours become susceptible, so we check all its neighbours and add them to susceptible list
     - We continue this process for total number of days(MAX_TIME) */
    
   // since the queue changes everyday(elements are added and removed) we change the queue head pointer
                                          
   for(day=1; day<=MAX_TIME; day++) {
      
      // once the queue is empty simulation stops
      if (pq_head == NULL) break;
      
      //if day of processing of an element is that particular day, all the elements having the same day as priority are processed 
      if (pq_head->time == day) {
         while(pq_head != NULL && pq_head->time == day) {
            present_vertex = pq_head->vertex;
            present_event = pq_head->event;
            delete_from_queue(&pq_head);
            
            // after removing it from queue we check the event and process it
            if(present_event == RECOVER_EVENT) {
               delete_from_list(&infected_head, present_vertex);
               temp2 = add_to_recoverylist(recovery_head, present_vertex);
               if(recovery_head == NULL) {
                  recovery_head = temp2;
               }
            }
         
            else if(present_event == TRANSMIT_EVENT) {
               delete_from_list(&susceptible_head, present_vertex);
            
               temp = add_to_infectedlist(infected_head, present_vertex);
               if(infected_head == NULL) {
                  infected_head = temp;
               }
               
               // after it gets infected it has to be processed again for recovery so we again add it to queue for recovery event and also.. \
                  while adding to queue we add that'day' to the randomly generated time because it is getting processed on that particular day and not firstday
               ptemp2 = add_to_prqueue(pq_head, present_vertex, RECOVER_EVENT, day);
               if(ptemp2 != NULL) {
                  pq_head = ptemp2;
               } 
               
               // after it gets infected, we search for its neighbours and add them to susceptible list and add all those to the piority queue for transmit event
  	           for(j=0; j<no_of_vertices; j++) {  
			      if(graph[present_vertex][j] == 1) {
			         add_to_susceptiblelist(&susceptible_head, infected_head, recovery_head, j);
				     
				    // while adding to queue we add that'day' to the randomly generated time because it is getting processed on that particular day and not firstday
				     if(is_in_list(recovery_head, j) == 0) {
				        ptempx = add_to_prqueue(pq_head, j, TRANSMIT_EVENT, day);
				        if(ptempx != NULL) {
                           pq_head = ptempx;
                        }
                     }
			      }
			   }
		     
            } // end else if      
         } // end while
         
      } // end if
      
      
      // at the end of the day we print all the elements of all the lists' to keep track
      printf("End of Day %d\n", day);
      printf("Infected: \n");
      print_list(infected_head);
      printf("\nSuspectible: \n");
      print_list(susceptible_head);
      printf("\nRecovery: \n");
      print_list(recovery_head);
      printf("\nQueue: \n");
      print_queue(pq_head);
      printf("\n===============================================================================================\n");
   
   } // end for  
            
            
   // after the processing is over we print the lists at the end
   printf("\n");
   printf("printing recovery list at the end:\n");
   print_list(recovery_head);
   printf("printing infected list at the end:\n");
   print_list(infected_head);
   printf("printing susceptible list at the end:\n");
   print_list(susceptible_head);
   printf("printing priority queue at the end:\n");
   print_queue(pq_head);
              
}    
          
