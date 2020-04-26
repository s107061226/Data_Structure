#include <iostream>
#include <string.h>
using namespace std;

class People {
    private:
        int i;                  // looping index
    public:
        string state;           // health condition (Healthy, Masked, Sick, Death)
        string name;            // person name
        int recovery_time;      // recovery time
        int insert_time;        // insert time
        int contagious;         // is this person can infect others
};

class List {
    private:
        int i;                  // looping index
    public:
        // nodes connection pointer
        List *right;            // pointer to right cell
        List *down;             // pointer to down cell
        List *next;             // pointer to next header
        int node_kind;          // 1: header of header; 2: header; 3: element
        // header of header nodes
        int row_num;            // the number of rows
        int col_num;            // the number of columns
        int people_num;         // the number of people
        // header nodes
        int number;             // Nth header
        // element nodes
        int row;                // row location of the cell
        int col;                // column location of the cell
        People people;          // the data of the person in the cell
};

void Connect(List *head, List *ptr);
void Show(List *head);
void Infect(List *head);
void BeContagious(List *head);
void lengthen_recovery(List *head, int day);
void BeHealthy(List *head);
void MoveToICU(List *head, int *space, People *ICU, int capacity);

int main()
{
    int i, j, k;
    int ICU_capacity;
    int time_end;
    int day;
    int come_day;
    int client;
    int read;
    int space_left;
    List *head;
    List *ptr;
    List *cur;
    People *ICU;

    // set the header of header nodes and information of matrix
    head = new List;
    head->node_kind = 1;
    cin >> head->row_num >> head->col_num;
    cin >> ICU_capacity >> time_end;
    cin >> head->people_num;
    ICU = new People[ICU_capacity];
    space_left = ICU_capacity;

    // set the header nodes
    j = head->row_num > head->col_num ? head->row_num : head->col_num;
    cur = head;
    for (i = 0; i < j; i++) {
        ptr = new List;
        ptr->node_kind = 2;
        ptr->number = i;
        cur->next = ptr;
        cur = ptr;
        cur->down = ptr;
        cur->right = ptr;
    }
    cur->next = head;

    // start to insert people
    day = 0;
    client = 0;
    read = 1;
    for (day = 0; day < time_end; day++) {
        // do the function in this day
        BeContagious(head);
        Infect(head);
        // insert people in this day
        if (client < head->people_num) {
            do {
                if (read) {
                    cin >> come_day;
                }
                if (come_day == day) {
                    ptr = new List;
                    ptr->node_kind = 3;
                    ptr->people.insert_time = day;
                    cin >> ptr->row >> ptr->col;
                    cin >> ptr->people.name;
                    cin >> ptr->people.state;
                    if (ptr->people.state == "Sick") {
                        ptr->people.recovery_time = 14;
                        ptr->people.contagious = 1;
                    } else {
                        ptr->people.recovery_time = 0;
                        ptr->people.contagious = 0;
                    }
                    Connect(head, ptr);
                    client++;
                    read = 1;
                } else {
                    read = 0;
                }
            } while (come_day == day && client < head->people_num);
        }
        // increase the recovery day
        BeHealthy(head);
        lengthen_recovery(head, day);
        MoveToICU(head, &space_left, ICU, ICU_capacity);
        cout << "day " << day << "result:" << endl;
        Show(head);
    }

    return 0;
}

void Connect(List *head, List *ptr)
{
    int con = 0;
    int complete;
    List *tmp, *cur, *p;

    cur = head;
    while (con < 2) {
        p = cur;
        cur = p->next;
        if (cur->number == ptr->row) {
            complete = 0;
            tmp = cur;
            while(!complete) {
                p = cur->right;
                if (p->node_kind == 2) {
                    cur->right = ptr;
                    ptr->right = p;
                    complete++;
                } else if (p->col < ptr->col) {
                    cur = p;
                } else {
                    cur->right = ptr;
                    ptr->right = p;
                    complete++;
                }
            }
            cur = tmp;
            con++;
        }
        if (cur->number == ptr->col) {
            complete = 0;
            tmp = cur;
            while (!complete) {
                p = cur->down;
                if (p->node_kind == 2) {
                    cur->down = ptr;
                    ptr->down = p;
                    complete++;
                } else if (p->row < ptr->row) {
                    cur = p;
                } else {
                    cur->down = ptr;
                    ptr->down = p;
                    complete++;
                }
            }
            cur = tmp;
            con++;
        }
    } 
    return;
}

void Show(List *head)
{
    int stop = 0;
    List *ptr, *cur;

    ptr = head;
    cur = head;
    while (stop < 2) {
        cout << "node_kind: ";
        if (cur->node_kind == 1) {
            cout << "header of header nodes. The matrix size is ";
            cout << cur->row_num << " by " << cur->col_num;
            cout << " and with " << cur->people_num << " people." << endl;
            ptr = cur->next;
            cur = ptr;
            stop++;
        } else if (cur->node_kind == 2) {
            cout << "header nodes H" << cur->number << endl;
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            } 
        } else if (cur->node_kind == 3) {
            cout << "element nodes (" << cur->row << ", " << cur->col << "). ";
            cout << cur->people.name << " " << cur->people.state;
            cout << ". recovery time: " << cur->people.recovery_time;
            if (cur->people.contagious) cout << " contagious! ";
            cout << endl;
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                cur = ptr;
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            }
        }
    }
    return;
}

void Infect(List *head)
{
    int stop = 0;
    List *ptr, *cur, *p;

    ptr = head;
    cur = head;
    while (stop < 2) {
        if (cur->node_kind == 1) {
            ptr = cur->next;
            cur = ptr;
            stop++;
        } else if (cur->node_kind == 2) {
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            } 
        } else if (cur->node_kind == 3) {
            if (cur->people.contagious) {
                // check the same row
                for (p = cur->right; p != cur; p = p->right) {
                    if (p->col == cur->col + 1 || p->col == cur->col - 1) {
                        if (p->people.state == "Healthy") {
                            p->people.state = "Sick";
                            p->people.recovery_time = 14;
                        }
                    }
                }
                // check the same column
                for (p = cur->down; p != cur; p = p->down) {
                    if (p->row == cur->row + 1 || p->row == cur->row - 1) {
                        if (p->people.state == "Healthy") {
                            p->people.state = "Sick";
                            p->people.recovery_time = 14;
                        }
                    }
                }
                // decrease the recovery time
                cur->people.recovery_time--;
            } 
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                cur = ptr;
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            }
        }
    }
    return;
}

void BeContagious(List *head)
{
    int stop = 0;
    List *ptr, *cur, *p;

    ptr = head;
    cur = head;
    while (stop < 2) {
        if (cur->node_kind == 1) {
            ptr = cur->next;
            cur = ptr;
            stop++;
        } else if (cur->node_kind == 2) {
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            } 
        } else if (cur->node_kind == 3) {
            if (cur->people.state == "Sick") {
                cur->people.contagious = 1;
            } 
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                cur = ptr;
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            }
        }
    }
    return;
}

void lengthen_recovery(List *head, int day)
{
    int stop = 0;
    List *ptr, *cur, *p;

    ptr = head;
    cur = head;
    while (stop < 2) {
        if (cur->node_kind == 1) {
            ptr = cur->next;
            cur = ptr;
            stop++;
        } else if (cur->node_kind == 2) {
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            } 
        } else if (cur->node_kind == 3) {
            if (cur->people.state == "Sick") {
                // check the same row
                for (p = cur->right; p != cur; p = p->right) {
                    if (p->col == cur->col + 1 || p->col == cur->col - 1) {
                        if (p->people.state == "Sick" && (p->people.contagious == 0 ||
                            p->people.insert_time == day)) {
                            cur->people.recovery_time += 7;
                        }
                    }
                }
                // check the same column
                for (p = cur->down; p != cur; p = p->down) {
                    if (p->row == cur->row + 1 || p->row == cur->row - 1) {
                        if (p->people.state == "Sick" && (p->people.contagious == 0 ||
                            p->people.insert_time == day)) {
                            cur->people.recovery_time += 7;
                        }
                    }
                }
            } 
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                cur = ptr;
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            }
        }
    }
    return;
}

void BeHealthy(List *head)
{
    int stop = 0;
    List *ptr, *cur, *p;

    ptr = head;
    cur = head;
    while (stop < 2) {
        if (cur->node_kind == 1) {
            ptr = cur->next;
            cur = ptr;
            stop++;
        } else if (cur->node_kind == 2) {
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            } 
        } else if (cur->node_kind == 3) {
            if (cur->people.state == "Sick") {
                if (cur->people.recovery_time == 0) {
                    cur->people.state = "Healthy";
                    cur->people.contagious = 0;
                }
            } 
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                cur = ptr;
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            }
        }
    }
    return;
}

void MoveToICU(List *head, int *space, People *ICU, int capacity)
{
    int stop = 0;
    List *ptr, *cur, *p;
    List *frt, *bhd;

    ptr = head;
    cur = head;
    while (stop < 2 && space > 0) {
        if (cur->node_kind == 1) {
            ptr = cur->next;
            cur = ptr;
            stop++;
        } else if (cur->node_kind == 2) {
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            } 
        } else if (cur->node_kind == 3) {
            if (cur->people.recovery_time > 28) {
                // disconnect in row dimension
                bhd = cur->right;
                for (p = cur->right; p != cur; p = p->right) {
                    frt = p;
                }
                frt->right = bhd;
                // disconnect in column dimension
                bhd = cur->down;
                for (p = cur->down; p != cur; p = p->down) {
                    frt = p;
                }
                frt->down = bhd;
                // move to ICU
                ICU[capacity - *space].name = cur->people.name;
                ICU[capacity - *space].insert_time = cur->people.insert_time;
                delete(cur);
                *space--;
            } 
            ptr = cur->right;
            if (ptr->node_kind == 2) {
                cur = ptr;
                ptr = cur->next;
                cur = ptr;
            } else {
                cur = ptr;
            }
        }
    }
    return;
}