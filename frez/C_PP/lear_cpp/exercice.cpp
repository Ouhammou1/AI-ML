#include <iostream>


void    icnrement (int &x)
{
    x++;
} 

int     &max(int arr[] , int size )
{   
    int index=0;
    int max = arr[0];
    for (int i = 0; i < size ; i++)
    {
        if(max < arr[i])
            index = i;
    }
    return  arr[index];
}
// int main()
// {
//     int arr[] = {1,2,3,6,9,17};
    
//     int &max_val = max(arr , 6);
//     std::cout << "m = " << max_val << std::endl;
// }
int main()
{
    int a = 5;
    int &b = a;

b++;
a++;
    int c = 210;
   b = c;
    std::cout << "a:  " << a << std::endl;
    std::cout << "b:  " << b << std::endl;
    std::cout << "c:  " << c << std::endl;
    // std::cout << "c:  " << bb << std::endl;


    // int c = 20 ;

    // b = c ;
    // std::cout << "a:  " << a << std::endl;
    // std::cout << "b:  " << b << std::endl;


    // int arr[] = {1,2,5,9,7};

    // int &ref = arr[2];
    // ref = ref + 10;

    // for (int  i = 0; i < 5; i++)
    // {
    //     std::cout  << "arr[i] = " << arr[i] << std::endl;
    // }
    
    return 0;
}