#include "dataio.h"
#include "parameterCal.h"
#define DEBUG 0



void dataRead()
{
    TPNode * head = createListFromFile("../data/TP.dat");

#if DEBUG

    // First: optput the length of list
    int len = lenListTP(head);
    cout<<"the number of nodes are "<<len<<endl;

    // Second: output some node of the list
    traverseTPList(head,3);

    // Third: output the data into another file
    saveListTP2File(head, "../data/output.dat");

    // Fourth: output the data compared with the variable
    find_lessthannum(head);

#endif


    //    这个函数将数据的米转换成厘米，暂时不用
//    dataTrans(head);
#if 1
    printf("height = %lf\n",head->next->data.tw[1]);
#endif

    // the calculate function is here
    parameterCal(head);
    


    destroyListTP(head);
}

void dataTrans(TPNode * head)
{
    head = head->next;
    while(head)
    {
    unsigned int len = head->data.coor[2];
    for(int i = 0; i < len; i++)
    {
        head->data.tw[2*i+1] = 100*head->data.tw[2*i+1];
    }
    head = head->next;
    }
}


void find_lessthannum(TPNode * head)
{
    unsigned int more = 0;
    unsigned int less = 0;
    unsigned int equal = 0;
    TPNode * t = head;
    t = t->next;
    while(t)
    {
        if(t->data.coor[2] > 3)
        {
            more++;
        }
        if(t->data.coor[2] == 3)
        {
            equal++;
        }
        if(t->data.coor[2] < 3)
            less++;


        t = t->next;
    }
        printf("more = %u\tequal = %u\tless = %u\t\n",more,equal,less);
        printf("sum = %u\n",more+equal+less);
}


/*
 * @ This function reads data from the file and return the pointer to the head 
 * 
 * @parameters:
 * filePath : the path to the data
 * 
 * @return:
 * head: the pointer to the head
 *
 * */
TPNode * createListFromFile(string filePath)
{
    ifstream infile;
    infile.open(filePath);

    if(infile.fail())
    {
        cout<<"Open file error!"<<endl;
    }

    TPNode * head = (TPNode*)malloc(sizeof(TPNode));
    head->next = NULL;

    TPNode * cur = (TPNode*)malloc(sizeof(TPNode));

    while(!infile.eof())
    {
        for(int i = 0; i < 3; i++)
        {
            infile >> cur->data.coor[i];
        }
        unsigned int length = (int)cur->data.coor[2];
        cur->data.tw = (double*)malloc(sizeof(double)*2*length);
        for(int i = 0; i < 2*length; i++)
        {
            infile >> cur->data.tw[i];
        }

        cur->next = head->next;
        head->next = cur;

        cur = (TPNode*)malloc(sizeof(TPNode));
    }
    free(cur);
    return head->next;
    infile.close();
}

/*
 * @ free the list space
 *
 * @ parameters:
 * head: the pointer to the list
 *
 * */
void destroyListTP(TPNode * head)
{
    TPNode * t;
    // from the first pointer, tw = NULL
    t = head;
    head = head->next;
    free(t);

    while(head)
    {
        t = head;
        head = head->next;
        free(t->data.tw);

        free(t->data.M2_f);
        free(t->data.M2_u);
        free(t->data.K1_f);
        free(t->data.K1_u);
        free(t->data.O1_f);
        free(t->data.O1_u);
        free(t->data.founier);
        free(t);
    }
}

/*
 * @output the number of node in the list
 * 
 * @parameters
 * head
 *
 * @ return
 * len: the number of node of the list
 *
 * */
int lenListTP(TPNode * head)
{
    int len = 0;
    head = head->next;
    while(head)
    {
        len++;
        head = head->next;
    }
    return len;
}

/*
 * @ putput the elements of the list
 *
 * @patameters:
 * head: the pointer to the first node of the list 
 * n: the number you want to traverse
 *
 * */
void traverseTPList(TPNode * head, int n)
{
    head = head->next;
    int length = 0;
    for(int i = 0; i < n; i++)
    {
        length = head->data.coor[2];
        cout<<"length = "<<length<<endl;
        cout<<fixed<<head->data.coor[0]<<","<<head->data.coor[1]<<","<<head->data.coor[2]<<endl;
        for(int j = 0; j < length; j++)
        {
            cout<<fixed<<head->data.tw[2*j]<<"\t\t"<<head->data.tw[2*j+1]<<endl;
        }
        head = head->next;
    }
}


void saveListTP2File(TPNode * head, string filePath)
{
    ofstream outfile;
    outfile.open(filePath);

    if(outfile.fail())
    {
        cout<<"output failed!"<<endl;
    }

    head = head->next;
    while(head)
    {
        for(int i = 0; i < 3; i++)
        {
            outfile<<head->data.coor[i]<<" ";
        }
        outfile<<endl;
        unsigned int length = (int )head->data.coor[2];
        for(int i = 0; i < length; i++)
        {
            outfile<<head->data.tw[2*i]<<" "<<head->data.tw[2*i+1]<<endl;
        }
        head = head->next;
    }
    outfile.close();
}
