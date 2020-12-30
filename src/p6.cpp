#include<iostream>
#include<vector>


//对数据进行输入判断
int get_matrix(std::vector<std::vector<int>>& a,int n)
{
    for (int i = 0;i < n;i++) 
    {
        std::vector<int> temp;
        a.push_back(temp);
        for (int j = 0;j < n;j++)
        {
            int t;
            std::cin>>t;
            a[i].push_back(t);
            //对输入数据进行判断，如果输入不合法就返回1
            if (a[i][j] != 0 && a[i][j] != 1)
                return 1;            
         }
    }
    return 0;
}


//输出矩阵
int output_matrix(std::vector<std::vector<int>> a)
{
    int i = 0,j = 0;
    for (i = 0;i < a.size();i++) {
        for (j = 0;j < a[i].size();j++) {
            std::cout<<a[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}
int warshall(std::vector<std::vector<int>>& a)
{    
//(1)i＝1；
//(2)对所有j如果a[j，i]＝1，则对k＝0，1，…，n-1，a[j，k]＝a[j，k]∨a[i，k]；
//(3)i加1；
//(4)如果i<n，则转到步骤2，否则停止
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0;i < a.size();i++) 
    {                  
        for (j = 0;j < a[i].size();j++) 
        {
            if (a[j][i]) 
            {
                for (k = 0;k < a.size();k++) 
                {
                    a[j][k] = a[j][k] | a[i][k];//逻辑加 
                }
            } 
        }
    }
}
int main()
{
    std::vector<std::vector<int>> a;
    std::cout<<"please input n:";
    int n;
    std::cin>>n;
    std::cout<<"please input a matrix with "<<n<<" * "<< n<<" :"<<std::endl;
    if (get_matrix(a,n))
     {  
        printf("Get matrix error!Only 0 or 1 in matrix!\n");
        return 1; //错误返回主函数，返回值为1； 
     }
    warshall(a);
    std::cout<<"The answer is:"<<std::endl;
    output_matrix(a);
    return 0;//正常返回主函数，返回值为0； 
}
