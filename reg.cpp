#include<fstream>
#include "customtime.h"
#include "customer.h"
#include "driver.h"
//#include "manager.h"
//#include "errcodes.h"
using namespace std;
int reg(Customer c)
{
    fstream f("Customer.dat", ios::binary|ios::in|ios::out|ios::ate), logger("log.txt", ios::in|ios::out|ios::app);
    char* dt = gettime();
    // Search if already that Customer-username is present or not
    Customer c1;
    int flag=0;
    f.seekg(0, ios::beg);// move to beg to start searching
    while(f.read((char*)&c1, sizeof(c1)))
        if(c1.getUser()==c.getUser())
    {
        flag=1;
        break;
    }
    if(flag==1){
        logger<<dt<<"Tried to register "<<c1.getUser()<<"usrname_already_exists"<<endl;
        logger.close();
        f.close();
        return -1;    // username already exists
    }
    // If username is unique => Register
    f.seekg(0, ios::end);// move to end to start writing
    f.write((char*)&c, sizeof(c));
    f.close();
    logger<<dt<<" Successfully registered user :"<<c1.getUser()<<endl;
    logger.close();
    return +1;// Registration success
}
