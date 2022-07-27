#include <iostream>

using namespace std;

struct department;
int nb_people_in_table=0;
struct worker{
    worker *previous_worker=nullptr;
    string worker_name;
    worker *next_worker=nullptr;
    department* dep=nullptr;
};

struct department{
    string department_name;
    int nb_people_on_shift=0;
    int nb_people_in_dep=0;
    department* next_dep=nullptr;
    worker* pointer_worker=nullptr;

    void add_worker(worker *worker)
    {
        if(this->pointer_worker == nullptr)
        {
            this->pointer_worker=worker;
            worker->next_worker=worker;
            worker->previous_worker=worker;
            worker->dep=this;
        }
        else
        {
            worker->dep=this;
            worker->previous_worker=this->pointer_worker->previous_worker;
            this->pointer_worker->previous_worker->next_worker=worker;
            this->pointer_worker->previous_worker=worker;
            worker->next_worker=pointer_worker;
        }
        this->nb_people_in_dep++;
    }

    void delete_worker(worker *worker)
    {
        if(worker == nullptr)
            return;
        worker->dep->nb_people_in_dep--;
        if(worker->next_worker == worker && worker->dep->pointer_worker == worker)
        {
            worker->dep->pointer_worker=nullptr;
            worker->next_worker=nullptr;
            worker->previous_worker=nullptr;
        }
        else if(worker->next_worker != worker && worker->dep->pointer_worker == worker)
        {
            worker->dep->pointer_worker=worker->next_worker;
            worker->next_worker->previous_worker=worker->previous_worker;
            worker->previous_worker->next_worker=worker->next_worker;
            worker->next_worker=nullptr;
            worker->previous_worker=nullptr;
            //worker->dep=nullptr;
        }
        else {
            worker->next_worker->previous_worker=worker->previous_worker;
            worker->previous_worker->next_worker=worker->next_worker;
            worker->next_worker=nullptr;
            worker->previous_worker=nullptr;
            //     worker->dep=nullptr;
        }
        worker->dep=nullptr;
    }
};


struct department_list{
    department* dep=new department;
    department* last_dep = new department;
    int nb_of_departments=0;

    void add_department(department *new_department)
    {
        if(nb_of_departments == 0)
        {
            dep=new_department;
            last_dep=new_department;
        }
        else
        {
            last_dep->next_dep=new_department;
            last_dep=new_department;
        }
        nb_of_departments++;
    }

    department *find_department(string department_name)
    {
        department* temp=dep;
        while(temp->department_name != department_name && temp->next_dep != nullptr)
        {
            temp=temp->next_dep;
        }
        return temp;
    }

    void delete_department(string department_name)
    {
        department* department_temp=dep;
        department* deparment_temp_v2;
        worker worker;
        while(department_temp->department_name != department_name && department_temp != nullptr)
        {
            deparment_temp_v2=department_temp;
            department_temp=department_temp->next_dep;
        }
        if(department_temp != nullptr)
        {
            for(int i=0; i < department_temp->nb_people_in_dep; i++)
            {
                department_temp->pointer_worker->dep=nullptr;
                department_temp->pointer_worker=department_temp->pointer_worker->next_worker;
            }
            if(department_temp->next_dep != nullptr)
            {
                if(department_temp == dep)
                {
                    dep=dep->next_dep;
                }
                else
                {
                    deparment_temp_v2->next_dep=department_temp->next_dep;
                }
                if(department_temp == last_dep)
                    last_dep=deparment_temp_v2;
            }
            else
            {
                department_temp=nullptr;
            }
        }
        nb_of_departments--;

    }

    void rename_department(string department_name, string new_department_name, int nb_people_on_shift)
    {
        department* department_temp=dep;
        while (department_temp->department_name != department_name && department_temp != nullptr)
        {
            department_temp=department_temp->next_dep;
        }
        department_temp->department_name=new_department_name;
        department_temp->nb_people_on_shift=nb_people_on_shift;
    }
};
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    department_list *list=new department_list;
    int n;
    cin >> n;
    worker *tab[n];
    char user_char;
    for(int i=0;i<n;i++)
    {
        cin >> user_char;
        switch (user_char)
        {
            case 'a':
            {
                cin >> user_char;
                switch (user_char)
                {
                    case 'd':
                    {
                        department *new_department=new department;
                        cin >> new_department->department_name;
                        cin >> new_department->nb_people_on_shift;
                        list->add_department(new_department);
                        break;
                    }
                    case 'w':
                    {
                        worker *new_worker= new worker;
                        cin >> new_worker->worker_name;
                        string department_name;
                        cin >> department_name;
                        list->find_department(department_name)->add_worker(new_worker);
                        tab[nb_people_in_table]=new_worker;
                        nb_people_in_table++;

                        break;
                    }
                }
                break;
            }
            case 'd':
            {
                cin >> user_char;
                switch (user_char)
                {
                    case 'd':
                    {
                        string department_name;
                        cin >> department_name;
                        list->delete_department(department_name);
                        break;
                    }
                    case 'w':
                    {
                        int id;
                        cin >> id;
                        if(tab[id]->dep == nullptr)
                            tab[id]=nullptr;
                        else
                        {
                            tab[id]->dep->delete_worker(tab[id]);
                            tab[id]=nullptr;
                        }

                        break;

                    }
                }
                break;
            }
            case 'm':
            {
                int id;
                string department_name;
                cin >> id >> department_name;
                department *tmp;
                tmp=tab[id]->dep;
                if(tmp!=nullptr)
                {
                    tmp->delete_worker(tab[id]);
                }
                list->find_department(department_name)->add_worker(tab[id]);

                break;
            }
            case 'w':
            {
                cin >> user_char;
                switch (user_char)
                {
                    case 'd':
                    {
                        string new_department_name,department_name;
                        int new_nb_people_on_shift;
                        cin >> department_name;
                        cin >> new_department_name;
                        cin >> new_nb_people_on_shift;
                        list->rename_department(department_name, new_department_name, new_nb_people_on_shift);
                        break;
                    }
                    case 'w':
                    {

                        int id;
                        string new_worker_name;
                        cin >> id;
                        cin >> new_worker_name;
                        tab[id]->worker_name=new_worker_name;
                        break;
                    }
                }
                break;
            }
            case 's':
            {
                int nb_of_shifts,temp;
                cin >> nb_of_shifts;
                department *department_temp=list->dep;
                if(list->nb_of_departments > 0)
                {
                    for(int j=0;j<list->nb_of_departments; j++)
                    {
                        if(nb_of_shifts > 0)
                        {
                            if(department_temp->nb_people_in_dep != 0)
                            {
                                temp= (nb_of_shifts) * (department_temp->nb_people_on_shift) % (department_temp->nb_people_in_dep);
                                if(temp < (department_temp->nb_people_in_dep + 1) / 2)
                                {
                                    for(int h=0; h < temp; h++)
                                    {
                                        department_temp->pointer_worker=department_temp->pointer_worker->next_worker;
                                    }
                                }
                                else
                                {

                                    for(int h=0; h < department_temp->nb_people_in_dep - temp; h++)
                                    {
                                        department_temp->pointer_worker=department_temp->pointer_worker->previous_worker;

                                    }
                                }
                            }
                        }

                        if(department_temp->nb_people_on_shift > department_temp->nb_people_in_dep)
                        {
                            cout << "(shortage of Workers)" << department_temp->department_name << ":";
                            for(int i=0; i < department_temp->nb_people_in_dep; i++)
                            {
                                cout << department_temp->pointer_worker->worker_name;
                                if(department_temp->nb_people_in_dep - 1 != i)
                                {
                                    cout << ",";
                                    department_temp->pointer_worker=department_temp->pointer_worker->next_worker;
                                }
                                else
                                    department_temp->pointer_worker=department_temp->pointer_worker->next_worker;
                            }
                        }
                        else
                        {
                            worker *temp_v2=department_temp->pointer_worker;
                            cout << department_temp->department_name << ":";
                            for(int i=0; i < department_temp->nb_people_on_shift; i++)
                            {
                                if(i == department_temp->nb_people_on_shift - 1)
                                {
                                    cout << department_temp->pointer_worker->worker_name;
                                    department_temp->pointer_worker=temp_v2;
                                }
                                else
                                {
                                    cout << department_temp->pointer_worker->worker_name << ",";
                                    department_temp->pointer_worker=department_temp->pointer_worker->next_worker;
                                }
                            }
                        }
                        department_temp=department_temp->next_dep;
                        cout <<".\n";
                    }

                }
                cout << "-\n";
                break;
            }
        }

    }
    return 0;
}
