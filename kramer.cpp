
#include <iostream>

using namespace std;

/*функция возведения в определённую степень числа -1*/
int mypow(int x){
    int y=1;
    for(int z=1;z<=x;z++){
        y*=-1;
    }
    return y;
}

/*класс матрица*/
class matrix{
public:

/*Конструктор: все элементы 0, размерность 0 */
    matrix(){
        size=0;

        for(int x=0;x<=100;x++)
            for(int y=0;y<=100;y++)
                m[x][y];
    }
/*Рекурсивная функция вычисления определителя */
    int GetDet(){
        int result=0;
        if(size==1){ //Если у матрицы размерность 2, то вычисляем определитель
            return m[0][0]*m[1][1]-m[0][1]*m[1][0];
        }
        else{
/*Вычисляем определитель путём вычёркивания строк и столбцов. Берём элементы из первой строки. */
            for(int x=0;x<=size;x++){
                result+= mypow(x+2)*m[0][x]*(GetNew(x)).GetDet();
            }
            return result;
        }
    }

    /*Функия получения новой матрицы из старой, путём вычёркивания первой(нулевой) строки и х`овой колонки*/
    matrix GetNew(int st){
        matrix result;
        int z=0;
        result.size=size-1;

        for(int x=1;x<=size;x++){
            for(int y=0;y<=size;y++){
                if(y!=st){
                    result.m[x-1][z]=m[x][y];
                    z++;
                }

            }
            z=0;
        }
        return result;
    }

/*Функция вывода на экран квадратной матрицы*/
    void echo(void){
        for(int x=0;x<=size;x++){
            for(int y=0; y<=size;y++){
                cout<<m[x][y]<<" ";
            }
            cout<<"\r\n";
        }
    }
/*Функция вывода на экран матрицы-столбца */
    void echoEx(void){
        for(int x=0;x<=size;x++){
            cout<<m[x][0]<<"\r\n";
        }
    }

/*Функция установки размерности матрицы*/
    inline void SetSize(int r){
        size=r;
    }

/*Функция установки значения элемента*/
    inline void SetValue(int value, int x , int y){
        m[x][y]=value;
    }

    /*Функция замены колонки на матрицу-столбец*/
    inline void SetColumn(int column , matrix source){
        for(int x=0;x<=size;x++){
            m[x][column]=source.m[x][0];
        }
    }

private:
    int m[100][100]; //сама матрица
    int size; //размерность

};
int main()
{
    matrix A,b,temp; //наши матрицы
    int element,size,maindet; //необходимые переменные
    bool c=1; //для цикла
    cout<<"The Kramer method for the system of linear equations.\r\n\r\n";
    while(c){
        cout<<"\r\nInsert size of matrix:";
        cin>>size;
        A.SetSize(size);
        b.SetSize(size);

/* вводим основную матрицу */
        for(int x =0; x<=size; x++){
            for( int y=0; y<=size;y++){
                cout<<"\r\nInsert ["<<x<<";"<<y<<"] element of A matrix:";
                cin>>element;
                A.SetValue(element,x,y);
            }
        }

/* вводим матрицу-столбец с числами*/
        for(int x=0; x<=size; x++){
            cout<<"\r\nInsert "<<x<<" element of b matrix:";
            cin>>element;
            b.SetValue(element,x,0);
        }
/* вводим кол-во вычислителей*/
        int n;
        cout<<"\r\nInsert number of calculators:";
        cin >> n;

        maindet = A.GetDet(); //вычисляем основной определитель(на него будем делить)
        if(maindet!=0){
            #pragma omp parallel for num_threads(n)//распараллелим
            for(int x=0;x<=size;x++){ //кол-во элементов(переменных в линейном уравнении) == размерности главной матрицы.
//Заменяем колонку, вычисляем определитель , делим на главный определитель, пробуем сократить и выводим
                temp = A;
                temp.SetColumn(x,b); //заменянем колонку
                cout<<"\r\nElement "<<x<<" = "<<temp.GetDet()<<"/"<<maindet; // выводим на экран
            }
        }else{ //главный определитель == 0, Крамер не проходит
            cout<<"\r\nSorry, but the main determinat of A matrix is 0.Stop.";
        }

// The End
        cout<<"\r\n\r\nFinish!";
        cout<<"\r\nDo you want to again calculate new matrix(1/0)?:";
        cin>>c;
    }

    return 0;
}