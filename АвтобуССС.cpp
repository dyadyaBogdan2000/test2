// �������.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
 
using namespace std;
 
const int _maxLengthName = 21;
 
//��������� ��� ��������
struct Bus
{
    int bus;
    char *name;
    char i;
    char o;
  int route;
};
 
//���� ���� �������
struct Node
{
    Bus *data;
 
    Node *next;
    Node *prev;
};
 
//��������� ������ ��� ������
Bus * InitData()
{
    Bus *tk = new Bus;
    tk->name = new char [_maxLengthName];
    return tk;
}
 
//���� ������
Bus * EnterData()
{
	setlocale (LC_ALL,"Russian");
    Bus *bt = InitData();
    cout<<"������� = ";     cin>>bt->bus;
    cout<<"��� �������� = ";     cin>>bt->name>>bt->i>>bt->o;
    cout<<"������� = ";       cin>>bt->route;
    return bt;
}
 
//�������� ������� ���� ������
Node * First(Bus * tk)
{
    Node * pv= new Node;
    pv->data = tk;
    pv->next = 0;
    pv->prev = 0;
    return pv;
}
 
//���������� ��� � ����� ������
void Add(Node ** pend, Bus *tk)
{
    Node *pv = new Node;
    pv->data = tk;
    pv->next = 0;
    pv->prev = *pend;
    (*pend)->next = pv;
    *pend = pv;
}
 
//����� �������� � ������
Node *Find(Node * const pbeg, int bus)
{
    Node *pv = pbeg;
    while (pv)
    {
        if (pv->data->bus == bus) break;
        pv = pv->next;
    }
    return pv;
}
 
//�������� �������� �� ������ �� ����
bool Remove(Node **pbeg, Node **pend, int bus)
{
    if (Node *pkey = Find(*pbeg, bus))
    {
        if (pkey == *pbeg)
        {
            if ((*pbeg)->next)
            {
            *pbeg = (*pbeg)->next;
            (*pbeg)->prev = 0;
            }
            else
            {
                *pbeg = 0;
                *pend = 0;
            }
        }else if (pkey == *pend)
        {
            *pend = (*pend)->prev;
            (*pend)->next = 0;
        }else
        {
            (pkey->prev)->next = pkey->next;
            (pkey->next)->prev = pkey->prev;
        }
        delete pkey;
        return true;
    }
    return false;
}
 
//������� �������� �� ����� (������� ����� ������������� �� ����)
Node * insert (Node ** pbeg, Node **pend, Bus *bk)
{
    Node *pkey = *pbeg;
    if (pkey->data->bus < bk->bus)
    {
        while (pkey->next && pkey->data->bus < bk->bus)
            pkey = pkey->next;
        Node *pv = new Node;
        pv->data = bk;
        pv->next = pkey->next;
        pv->prev = pkey;
        pkey->next = pv;
        if (pkey != *pend)
            (pv->next)->prev = pv;
        else
            *pend = pv;
        return pv;
    }else
    {
        Node *pv = new Node;
        pv->data = bk;
        pv->next = *pbeg;
        pv->prev = 0;
        
        pkey->prev = pv;
        *pbeg = pv;
        return pv;
    }
    return 0;
}
 
//������ ������
void Print(Node * const pbeg)
{
	setlocale (LC_ALL,"Russian");
    Node *pv = pbeg;
    if (!pv)
    {
        cout<<" ������ ���� "<<endl;
        return;
    }
    printf("---------------------------------------------\n");
    printf("|  ������� | ���           | �������            |\n");
    printf("---------------------------------------------\n");
    while (pv)
    {
        Bus *bk = pv->data;
        printf("|%6d",bk->bus);
        printf("|%9s",bk->name);
        printf(" %c.",bk->i);
        printf(" %c.",bk->o);
        printf("|%19d",bk->route);
        printf("|\n");
        pv = pv->next;
 
    }
    printf("----------------------------------------------\n");
 
}
 
//����� ������
Bus* Search(Node * const pbeg)
{
    Node *pv = pbeg;
 
    int bus;
    char date[13];
    cout<<" bus             = "; cin>>bus;
    while (pv)
    {
        if (pv->data->bus == bus)
        {
            Node *pbeg = First(pv->data);
            Print(pbeg);
      return pbeg->data;
        }
        pv = pv->next;
    }
}
 
// ���������� ��������. ���� ������� ��� - �� �������
void NodeRead(Node ** pbeg, Node **pend, Bus *bk)
{
//  Bus *bk = EnterData();
    if (*pbeg)
        insert(pbeg,pend,bk);
    else
    {
        (*pbeg) = First(bk);
        (*pend) = (*pbeg);
    }
}
 
 
//����
int main()
{
	setlocale (LC_ALL,"Russian");
    Node *pbeg=0, *pend=0;
  Node *rbeg=0, *rend=0;
    int menu,bus;
    do
    {
        system("cls");
        cout<<" 1 - �������� "<<endl;
        cout<<" 2 - �������� � �����"<<endl;
        cout<<" 3 - �������� � �����"<<endl;
		cout<<" 4 - ������� ������� � ����"<<endl;
        cout<<" 5 - ������� ������� � ����"<<endl;
        cout<<" 0 - ����� "<<endl;
        cout<<"�������� ���� ";
        cin>>menu;
        switch (menu) 
        {
        case 1:
      NodeRead(&pbeg,&pend, EnterData());
            break;
        case 2:
            cout<<"������� � �����"<<endl;
            Print(pbeg);
            getch();
            break;
        case 3:
			 cout<<"������� � �����"<<endl;
             Print(rbeg);
            getch();
            break;
    case 4:
		  {
      Bus * b = Search(rbeg);
      Remove(&rbeg, &rend, b->bus);
      NodeRead(&pbeg,&pend,b);
      break;
      }
    
    case 5:
      {
      Bus * b = Search(pbeg);
      Remove(&pbeg,&pend,b->bus);
      NodeRead(&rbeg, &rend, b);
      break;
      }
        }
    }while (menu);
 
    //������������ ������
    while (pbeg)
    {
        Node *pv = pbeg;
        pbeg = pbeg->next;
        delete pv->data;
        delete pv;
    }
    return 0;
}