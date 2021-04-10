#include <iostream> //for input/output operations
#include <random>   //for random numbers
#include <string>   //string

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
    #define CLEAR "cls"
#elif defined __linux__
    #include <unistd.h>
    #define CLEAR "clear"
#else
    #error "unknown platform"
#endif

#define wipe() system( CLEAR )  //to clear the console screen use wipe();

void mySleep(int sleepMs)
{
    #if defined _WIN32 || defined _WIN64
        Sleep(sleepMs);
    #elif defined __linux__
        usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
    #else
        #error "unknown platform"
    #endif
}

using std::cout;
using std::cin;
using std::endl;

int main()
{
    cout << "Lucky Number v1.0" << endl;
    
    int max_number = 32;
    std::string input;
    cout << "Input Maximum Number(higher than 2; default: 32): ";
    std::getline(std::cin, input);

    for(int loop_i=0; loop_i<input.size(); ++loop_i)
        if(!isdigit(input[loop_i]))
        {
            input = "";
            break;
        }
    
    if ( !input.empty() )
    {
        short trial_num = std::stoi(input);
        if(trial_num>2)
            max_number = trial_num;
    }
        
    cout << max_number << endl;
    mySleep(1500);
    
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> rand_num(1, max_number);


    short tab[3] {};

    if(max_number == 32)
    {
        tab[0] = 23;
        tab[1] = 28;
    }
    else
        for(int loop_i=0; loop_i<2; ++loop_i)
        {
            short test;
            do
            {
                test = rand_num(gen);
            }   while(test==tab[0]);

            tab[loop_i] = test;
        }

    int time {};

    while(time <= 3000)
    {
        do
        {
            tab[2] = rand_num(gen);
        }   while(tab[2]==tab[0] || tab[2]==tab[1]);
        
        cout << tab[2] << endl;
        mySleep(100);
        time += 100;
        wipe();
    }

    cout << "End up with:\t" << tab[2] << endl << endl;


    short order[3] {};
    std::uniform_int_distribution <int> rand_num_order(1, 3);

    for(int loop_i=0; loop_i<3; ++loop_i)
    {
        short test;
        do
        {
            test = rand_num_order(gen);
        }   while(test==order[0] || test==order[1]);

        order[loop_i] = test;
    }
 
    //print out numbers in tab
    for(int loop_i=0; loop_i<3; ++loop_i)
        cout << "No" << loop_i+1 << ". in tab:\t" << tab[loop_i] << endl;
    cout << endl;

    //print out order numbers 
    for(int loop_i=0; loop_i<3; ++loop_i)
        cout << "No" << loop_i+1 << ". in order:\t" << order[loop_i] << endl;
    cout << endl;

    //print out the results
    for(int loop_i=0; loop_i<3; ++loop_i)
        cout << "No." << loop_i+1 << ". - " << tab[(order[loop_i]-1)] << endl;
}
