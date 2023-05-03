typedef struct student
{
    int prn;
    char name[30];
    struct student* next;
} student;

typedef student* Club;

void initList(Club *c);
void AddMember(Club *c,int prn, char name[]);
void display(Club c);
int count(Club c);
void deleteMember(Club *c,int prn);

