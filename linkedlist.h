
template< class T>
struct Node {
    public:
    T command;
    Node<T> *next;
    Node<T> *prev;

    Node(T command) {
        this->command = command;
        next = NULL;
        prev = NULL;
    }
    ~Node() {
    }
};

template <class T>
class Queue {
 public:
    Node<T> *head;
    Node<T> *tail;
    int numElements;
  
    Queue() {
        head = tail = NULL;
        numElements = 0;
    }


void enqueue1(T command) {
       
        Node<T> *nod = new Node<T>(command);
        if( numElements == 0){
        numElements ++;
        head = tail = nod;
        head->next = NULL;
        head->prev = NULL;
       }
       else {
           numElements ++;
           if(tail != NULL){
           tail->next = nod;
           nod->prev = tail;
           tail = nod;
           tail->next = NULL;
           }
       }
   
    }
    // metoda enqueue1 adauga elementele in coada in ordine, netinand cont de prioritate

    void enqueue(T command) {
       
        Node<T> *nod = new Node<T>(command);
        if( numElements == 0){
        numElements ++;
        head = tail = nod;
        head->next = NULL;
        head->prev = NULL;
       }
       else {
           if (command.priority == 0){
           numElements ++;
           if(head != NULL){
           head->prev = nod;
           nod->prev = NULL;
           nod->next = head;
           head = nod;
           }
           }
       
        else {
            numElements ++;
           tail->next = nod;
           nod->prev = tail;
           tail = nod;
           tail->next = NULL;
        }

       }
   
    }
    // metoda enqueue adauga elementele in coada in functie de prioritate


    T dequeue() {
            T data;
            this->numElements --;
            if(head != NULL)
            data = head->command;
            Node<T> *aux;
            aux = head;
            if(head != NULL)
            head = head->next;
            
            delete aux;
            if(head != NULL)
              head->prev = NULL;
            return data; 
    }

    // metoda dequeue returneaza elementul de la inceputul cozii, stergandu-l

    T dequeue_last() {
            T data;
            this->numElements --;
            if(tail != NULL)
            data = tail->command;
            Node<T> *aux;
            aux = tail;
            if(tail != NULL)
            tail = tail->prev;
            
            delete aux;
            if(tail != NULL)
              tail->next = NULL;
            return data; 
    }
    // metoda dequeue_last returneaza elementul de la sfarsitul cozii, stergandu-l


     T peek(int position) {
         int aux = 0;
        Node<T> *data;
        data = head;
        while(aux != position) {
            data = data->next;
            aux ++;
        }
        if(data != NULL)
            return data->command; 
    }
    // metoda peek returneaza elementul de pe o anumita pozitie

    int size() {
        return numElements;
    }
    // metoda size returneaza dimensiunea cozii


      ~Queue() {
          while(this->numElements > 0) {
              dequeue();
            }    
        }
};