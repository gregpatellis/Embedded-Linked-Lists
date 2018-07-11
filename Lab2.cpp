#include <iostream>
#include <fstream>
using namespace std;
#define SYM "*"
#define SPACE " "

struct cat
{
	string cname;
	string type;
	string dob;
	int price;

  	cat (string c, string t, string d, int pr)
	{
		cname = c;
		type = t;
		dob = d;
		price = pr;
	}

	void print();
};

void cat::print()
{
	cout << cname << SPACE << type << SPACE << dob << SPACE << price << endl;
}

struct cnode
{
	cat * data;
	cnode * next;
	cnode(cat * d, cnode * n)
	{
	       	data = d;
		next = n;
	}
};

struct catList
{
        cnode * first;

        catList()
        {
                first = NULL;
        }
        void add_to_front(cat * cNode);
        void print();
        bool find(string catName);
        cnode * find_mostExp();
        cnode * findtoReplace(string catName);
        void add_cat(cnode * b);
};

void catList::add_cat(cnode * kitty)
{
	if(first!= NULL)
	{
		kitty -> next = first;
		first = kitty;
			
	}
	if(first == NULL)
	{
		first = kitty;
		kitty -> next = NULL;
	}
}

bool catList::find(string catName)
{
	cnode * tempo = first;
        while(tempo != NULL)
        {
                if(tempo -> data -> cname == catName)
                {
                        cout << endl;
                        tempo -> data-> print();
                        return(true);
                }
                tempo = tempo -> next;
        }
}

cnode * catList::findtoReplace(string catName)
{
	cnode * prev = NULL;
	cnode * found = NULL;
    cnode * tempo = first;
        while(tempo != NULL)
        {
                if(tempo -> data -> cname == catName)
                {
                    if (prev == NULL)
                    {
                        first = tempo->next;
                    }
                    else
                    {
                        prev->next = tempo->next;
                    }
                     
                found = tempo;
                found->next = NULL;
                tempo = NULL;
                return(found);
                   
                }
                prev = tempo;
                tempo = tempo -> next;
        }
	
	return(NULL);
}

void catList::add_to_front(cat * cNode)
{
        first = new cnode(cNode, first);
}

void catList::print()
{
        cnode * tempNext = first;
		
        while (tempNext != NULL)
        {
		tempNext -> data -> print();
		tempNext = tempNext -> next;
        }
}

cnode * catList::find_mostExp()
{	
	cnode * max = NULL;
	int maxNum = 0;
	cnode * temp = first;
	while(temp != NULL)
	{
		if(temp -> data -> price > maxNum)
		{
			maxNum = temp -> data -> price;
			max = temp;
		}
		
		temp = temp -> next;	
	}
	return(max);

}

struct person
{
	string name;
	string phone;
	int memnum;
	catList * pCatList;
	person(string n, string p, int m,catList * c)
	{
		name = n;
		phone = p;
		memnum = m;
		pCatList = c;
	}
	void print();	
};

void person::print()
{
	cout << name << SPACE << phone << SPACE << memnum << endl;
}

struct pnode
{       
	person * info;
	pnode *link;
	pnode(person * p, pnode * n)
	{
		info = p;
		link = n; 
	}
};

struct personList
{
	pnode * head;

	personList()
	{
		head = NULL;
	}
	void add_to_front(person * pNode);
	void print();
	void printList();
	void find_person(string p);
	void find_cat(string c);
	void find_mostExp();
	void find_personwithCat(string p, string c);	
};

void personList::find_mostExp()
{
	
	cnode * exp = NULL;
	pnode * temp = head;
	exp = temp -> info -> pCatList -> find_mostExp();
	
	if(temp->link != NULL)
	{
		temp = temp->link;
	}
	
	while(temp != NULL)
	{	
		if(temp	-> info -> pCatList -> first != NULL)
		
		{
			if(temp -> info -> pCatList -> find_mostExp()-> data->price > exp-> data -> price)
			{
				exp = temp -> info -> pCatList -> find_mostExp();
			}			
		}
		
		temp = temp -> link;
	}

	exp -> data -> print();

}

void  personList::find_personwithCat(string name, string catname)
{
	cnode * foundCat = NULL;
	pnode * temp2 = head;
	pnode * temp = head;
	cnode * find = NULL;
	while(temp != NULL)
	{
		find = temp -> info -> pCatList -> findtoReplace(catname);
		
		if(find != NULL)
		{
			foundCat = find;
		}
		
		temp = temp -> link;
	}
	
	while(temp2 != NULL)
	{
		if(temp2 -> info -> name == name)
		{
			temp2 -> info -> pCatList -> add_cat(foundCat);
			temp2 -> info -> print();
			cout << endl;
			temp2 -> info -> pCatList -> print();
			break;
		}
		
		temp2 = temp2 -> link;
	}
}

void personList:: add_to_front(person * pNode)
{
	head = new pnode(pNode, head);
}

void personList::print()
{
	pnode * tempLink = head;
	
	while (tempLink != NULL)
{
		tempLink -> info -> print();
		tempLink -> info -> pCatList -> print();
		cout << endl;
		tempLink = tempLink -> link;
}
}

void personList::printList()
{
	pnode * temp = head;
	while(temp != NULL)
{
	temp -> info -> print();
	temp = temp -> link; 
}
}

void personList::find_person(string pfind)
{
	pnode * temps = head;
	while(temps != NULL)
	{
		if(temps -> info -> name == pfind)
		{	
			cout << endl;
			temps -> info-> print();
			temps -> info -> pCatList -> print();
		}
		temps = temps -> link;
	}
}

void personList::find_cat(string cfind)
{
	
	pnode * temp = head;
	while(temp != NULL)
	{
		
			
			if(temp -> info -> pCatList -> find(cfind) == true)
			{	
				cout << endl << "The owner is:" << endl;
				temp -> info -> print();
			}
		temp = temp -> link;
	}

}

void main()
{ 	
    personList * mypersonList = new personList();

    ifstream fin("Catclub.txt");

    if (fin.fail())
    {
        cout << "Error reading in file" << endl;
    }

    while(!fin.eof())
    {
        string name;
        string phone;
        int memnum;

        fin >> name >> phone >> memnum;
		
        if(name == SYM)
        {break;}

        catList * newClist = new catList();
		
        while(true)
        {
            string cname;
            string type;
            string dob;
            int price;
			
            fin >> cname;
				
            if (cname == SYM)
            {
                break;
                cin.clear();
            }
			
            fin >> type >> dob >> price;
			
            cat * c = new cat(cname, type, dob, price);
				
            newClist -> add_to_front(c);

        }
		
        person * p = new person(name, phone, memnum,newClist);
	
        mypersonList -> add_to_front(p);

    }
	

	while(true)
	{      
		int command;
		cout << "Enter a number for the following commands:" << endl << endl;
		cout << "1: Enter a person's name and print their cats" << endl;
		cout << "2: Enter a cat's name and print their information along with their owner's" << endl;
		cout << "3: Print the most expensive cat" << endl;
		cout << "4: Print every owner with their cats" << endl;
		cout << "5: Enter a cat's name and a new owners name to give the cat to" << endl;
		cout << "6: EXIT" << endl;	
		cin >> command;
		
            if(command == 6)
            {exit(1);}

			if(command == 4)
			{
				mypersonList -> print();
			}	
	
			if(command == 1)
			{
				string person;
				cout << "Enter a name you would like to find" << endl;
				cin >> person;
				mypersonList -> find_person(person);
			}

			if(command == 2)
			{
				string cat;
				cout << "Enter the name of the cat you would like to search" << endl;
				cin >> cat;
				mypersonList -> find_cat(cat);
			}

			if(command == 3)
			{
				cout << endl;
				mypersonList -> find_mostExp();		
			}

			if(command == 5)
			{	
				string name;
				string cat;
				cout << "Enter the cat you would like to remove" << endl;
				cin >> cat;
				cout << "Enter the person you would like to give the cat to" << endl;
				cin >> name;
				cout << endl;
				mypersonList -> find_personwithCat(name, cat);
		
			}
	}
}












