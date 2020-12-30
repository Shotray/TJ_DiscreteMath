#include<iostream>
#include<cmath>
#include<string.h>

#define N 50 

using namespace std;

void panduan(int b[N],int f);  //赋值函数
int tkh(char sz[N],char ccu[N],int icu[N],int h0);  //分级运算函数
int fkh(char sz[N],char ccu[N],int icu[N],int h0);  //主运算函数

int main()
{
	int i1,i2,d = 1,icu[N],kh = 0,jg,j = 0,h0;  //icu[N]用于存放变量值,kh用于括号计数,jg存放结果
	int bj = 0,hq[N],h = 0,x = 0,xq[N];  //hq[N]存放合取结果,xq[N]存放析取结果
	char sz[N],ccu[N],sz0[N];  //sz[N]存放式子,ccu[N]存放变量,sz0[N]也是用于存放式子
	hq[0] = -1;
	xq[0] = -1;
	cout<<"***************************************\n";  //标语
	cout<<"**                                   **\n";
	cout<<"**         欢迎进入逻辑运算软件      **\n";
	cout<<"**   (可运算真值表,主范式,支持括号)  **\n";
	cout<<"**                                   **\n";
	cout<<"**              用!表示非            **\n";
	cout<<"**              用&表示与            **\n";
	cout<<"**              用|表示或            **\n";
	cout<<"**             用^表示蕴含           **\n";
	cout<<"**             用~表示等值           **\n";
	cout<<"**                                   **\n";
	cout<<"***************************************\n\n";
	cout<<"请输入一个合法的命题公式:\n";  //输入式子
	cin>>sz;  //读取式子
	strcpy(sz0,sz);  //复制式子
	for(unsigned i1 = 0;i1 < strlen(sz);i1++)
	{
		if(sz[i1] == ')' || sz[i1] == '(')  //存储括号数量
			kh++;
		if(sz[i1] >= 'a' && sz[i1] <= 'z' || sz[i1] >= 'A' && sz[i1] <= 'Z') 
		{
			for(i2 = 0;i2 < j;i2++)  //判断并储存变量。
				if(ccu[i2] == sz[i1])  //去除重复变量
					d = 0;
			if(d == 1)
			{
				ccu[j] = sz[i1];
				j++;
			}
			d = 1; 
		}
	}
	cout<<"\n该式子中的变量个数为:"<<j<<endl;  //输出变量个数
	h0 = j; 
	cout<<"\n输出真值表如下:\n \n";  //输出真值表表头
	for(i1 = 0;i1 < h0;i1++)
		cout<<ccu[i1]<<" "; 
	cout<<"    ";
	cout<<sz;
	cout<<"\n"; 
	for(i1 = 0; i1 < j;i1++)   //先将所有的变量赋值为零。
		icu[i1] = 0;
	for(i2 = 0;i2 < j;i2++)  //输出真值表前项
		cout<<icu[i2]<<" ";
	jg = tkh(sz,ccu,icu,h0);  //用函数求结果
	if(jg == 0)  //结果为0，合取加1
		hq[h++] = bj;
	else  //否则，析取加1
		xq[x++] = bj; 
	cout<<"    "<<jg<<endl;  //输出运算结果
	strcpy(sz,sz0); 
	for(i1 = 0;i1 < (int)pow(2.0,j) - 1;i1++)
	{
		++bj;
		panduan(icu,j - 1);  //赋值变量
		jg = tkh(sz,ccu,icu,h0); 
		if(jg == 0)  //结果为0，合取加1
			hq[h++] = bj;
		else  //否则，析取加1
			xq[x++] = bj; 
		strcpy(sz,sz0);  //恢复被修改的数组
		for(i2 = 0;i2 < j;i2++)
			cout<<icu[i2]<<" ";  //输出真值表前项
		cout<<"    "<<jg<<endl;  //输出运算结果
	} 
	if(hq[0] == -1)  //不存在合取范式时
		cout<<"\n该命题公式不存在主合取范式.\n";
	else
	{ 
		cout<<"\n该命题公式的主合取范式:\n\t";
		for(i1 = 0;i1 < h;i1++)
			{
				if (i1 > 0)  //判断并添加符号
					cout<<"\\/";
				cout<<"M("<<hq[i1]<<")";  //输出主合取范式
			}
	}
	if(xq[0] == -1)  //不存在析取范式时
		cout<<"\n该命题公式不存在主析取范式.\n";
	else
	{
		cout<<"\n\n该命题公式的主析取范式:\n\t";
		for(i1 = 0;i1 < x;i1++)
		{
			if (i1 > 0)  //判断并添加符号
				cout<<"/\\";
			cout<<"m("<<xq[i1]<<")";  //输出主析取范式
		}
	}
	cout<<"\n"; 
	cout<<"\n欢迎下次再次使用!\n";  //结束
	return 0;
}

void panduan(int b[N],int f)   //二进制赋值
{
	int i;
	i = f;
	if(b[f] == 0)  //加1
		b[f] = 1;
	else  //进位
	{
		b[f] = 0;
		panduan(b,--i);
	} 
}

int tkh (char sz[N],char ccu[N],int icu[N],int h0)  //分级运算函数
{
	int i,j,h,s,kh = 0,wz[N],a; 
	char xs1[N],ckh[N];  //xs1用来保存括号内的字符 ckh用来保存括号。
	s = strlen(sz);
	for(i = 0;i < s;i++)
		if(sz[i] == '(' || sz[i] == ')')  //判断括号
		{
			wz[kh] = i;  //存储括号位置
			ckh[kh] = sz[i];  //存储括号类型
			kh++;
		}
		if(kh == 0)
			return fkh(sz,ccu,icu,h0);  //如果无括号，直接运行
		else
		{
			for(i = 0;i < kh;i++)
				if(ckh[i] == ')')  //找到第一个）
			break;
			for(j = wz[i-1]+1,h = 0;j < wz[i];j++,h++)  //存储最内级括号中的内容
				xs1[h] = sz[j]; 
			xs1[h] = '\0';
			a = fkh(xs1,ccu,icu,h0);  //运行最内级括号的式子，得到结果
			if(a == 1)  //判断并存储结果
				sz[wz[i-1]] = 1;
			else
				sz[wz[i-1]] = -2;
			for(j = wz[i-1]+1;j < s+wz[i-1]-wz[i];j++)  //将括号后内容前移
				sz[j] = sz[j+wz[i]-wz[i-1]];
			sz[j] = '\0'; 
			return tkh(sz,ccu,icu,h0);  //循环执行
		}
}

int fkh(char sz[N],char ccu[N],int icu[N],int h0)  //主运算函数
{
	int i,h = 0,j = 0,j1 = 0,j2 = 0,j3 = 0,j4 = 0,j5 = 0,i1,i2,p1 = -1,p2 = -1,s;
	char dt[N];
	s = strlen(sz);
	if(s == 1)
		if(sz[0] == -2)  //判断是否是最后一项
			return 0;
		else
			return 1;   //1就是sz[0]的值
	else
	{ 
		for(i = 0;i < s-j;i++)  //先处理非
			if(sz[i] == '!')
			{ 
				for(i1 = 0;i1 <h0;i1++)
					if(sz[i+1] == ccu[i1])  //将变量赋值并给P1
						p1 = icu[i1];
				if(sz[i+1] == -2)  //如果是前运算结果的0，则P1等于0
					p1 = 0; 
				if(p1 == -1)  //如果是数字，直接给P1
					p1 = sz[i+1]; 
				dt[j+2] =! p1;  //非运算
				sz[i] = j+2;
				j++;
				p1 = 0;
				for(i1 = i+1;i1 < s-j;i1++)
					sz[i1] = sz[i1+1];  //将后续式子前移一项
			}
		p1 = -1; 
		j1 = j; 
		for(i = 0;i < s-j1-2*j2;i++)  //处理与
			if(sz[i] == '&')
			{ 
				for(i1 = 0;i1 < h0;i1++)
				{ 
					if(sz[i-1] == ccu[i1])  //将变量赋值并给P1
						p1 = icu[i1];
					if(sz[i+1] == ccu[i1])  //将变量赋值并给P2
						p2 = icu[i1];
				}
				for(i2 = 2;i2 < j+2;i2++) 
				{
					if(sz[i-1] == i2)  //如果为前计算结果，将结果赋值并给P1
						p1 = dt[i2]; 
					if(sz[i+1] == i2)  //如果为前计算结果，将结果赋值并给P2
						p2 = dt[i2];
				}
				if(sz[i-1] == -2)  //如果是前运算结果的0，则P1等于0
				p1 = 0; 
				if(sz[i+1] == -2)  //如果是前运算结果的0，则P2等于0
					p2 = 0;
				if(p1 == -1)  //如果是数字，直接给P1
					p1 = (int)(sz[i-1]);
				if(p2 == -1)  //如果是数字，直接给P2
					p2 = (int)(sz[i+1]); 
				dt[j+2] = p1 && p2;  //与运算
				sz[i-1] = j+2;
				j++;
				j2++;
				p1 = -1;
				p2 = -1; 
				for(i1 = i;i1 < s-j1-2*j2;i1++)  //将后续式子前移两项
					sz[i1] = sz[i1+2];
				i = i-1;
			}
		for(i = 0;i < s-j1-2*j2-2*j3;i++)  //处理或
			if(sz[i] == '|')
			{
				for(i1 = 0;i1 < h0;i1++)
				{ 
					if(sz[i-1] == ccu[i1])  //将变量赋值并给P1
						p1 = icu[i1];
					if(sz[i+1] == ccu[i1])  //将变量赋值并给P2
						p2 = icu[i1];
				}
				for(i2 = 2;i2 < j+2;i2++) 
				{
					if(sz[i-1] == i2)  //如果为前计算结果，将结果赋值并给P1
						p1 = dt[i2];
					if(sz[i+1] == i2)  //如果为前计算结果，将结果赋值并给P2
						p2 = dt[i2];
				}
				if(sz[i-1] == -2)  //如果是前运算结果的0，则P1等于0
					p1 = 0; 
				if(sz[i+1] == -2)  //如果是前运算结果的0，则P2等于0
					p2 = 0;
				if(p1 == -1)  //如果是数字，直接给P1
					p1 = sz[i-1];
				if(p2 == -1)  //如果是数字，直接给P2
					p2 = sz[i+1];
				dt[j+2] = p1 || p2;  //或运算
				sz[i-1] = j+2;
				j++;
				j3++;
				p1 = -1;
				p2 = -1; 
				for(i1 = i;i1 < s-j1-2*j2-2*j3;i1++)  //将后续式子前移两项
					sz[i1] = sz[i1+2];
				i--; 
			}
		for(i = 0;i < s-j1-2*j2-2*j3-2*j4;i++)  //处理蕴含
			if(sz[i] == '^')
			{
				for(i1 = 0;i1 < h0;i1++)
				{ 
					if(sz[i-1] == ccu[i1])  //将变量赋值并给P1
						p1 = icu[i1];
					if(sz[i+1] == ccu[i1])  //将变量赋值并给P2
						p2 = icu[i1];
				}
				for(i2 = 2;i2 < j+2;i2++) 
				{
					if(sz[i-1] == i2)  //如果为前计算结果，将结果赋值并给P1
						p1 = dt[i2];
					if(sz[i+1] == i2)  //如果为前计算结果，将结果赋值并给P2
						p2 = dt[i2];
				}
				if(sz[i-1] == -2)  //如果是前运算结果的0，则P1等于0
	   				p1 = 0; 
				if(sz[i+1] == -2)  //如果是前运算结果的0，则P2等于0
					p2 = 0;
				if(p1 == -1)  //如果是数字，直接给P1
	  				p1 = sz[i-1];
				if(p2 == -1)  //如果是数字，直接给P2
					p2 = sz[i+1];
				dt[j+2] =! p1 || p2;  //蕴含运算
				sz[i-1] = j+2;
				j++;
				j4++;
				p1 = -1;
				p2 = -1; 
				for(i1 = i;i1 < s-j1-2*j2-2*j3-2*j4;i1++)  //将后续式子前移两项
					sz[i1] = sz[i1+2];
				i--; 
			}
		for(i = 0;i < s-j1-2*j2-2*j3-2*j4-2*j5;i++)  //处理等值
			if(sz[i] == '~')
			{
				for(i1 = 0;i1 < h0;i1++)
				{ 
					if(sz[i-1] == ccu[i1])  //将变量赋值并给P1
						p1 = icu[i1];
					if(sz[i+1] == ccu[i1])  //将变量赋值并给P2
						p2 = icu[i1];
				}
				for(i2 = 2;i2 < j+2;i2++) 
				{
					if(sz[i-1] == i2)  //如果为前计算结果，将结果赋值并给P1
						p1 = dt[i2];
					if(sz[i+1] == i2)  //如果为前计算结果，将结果赋值并给P2
						p2 = dt[i2];
				}
				if(sz[i-1] == -2)  //如果是前运算结果的0，则P1等于0
					p1 = 0; 
				if(sz[i+1] == -2)  //如果是前运算结果的0，则P2等于0
					p2 = 0;
				if(p1 == -1)  //如果是数字，直接给P1
					p1 = sz[i-1];
				if(p2 == -1)  //如果是数字，直接给P2
					p2 = sz[i+1];
				dt[j+2] = (!p1 || p2) && (!p2 || p1);  //等值运算
				sz[i-1] = j+2;
				j++;
				j5++;
				p1 = -1;
				p2 = -1; 
				for(i1 = i;i1 < s-j1-2*j2-2*j3-2*j4-2*j5;i1++)  //将后续式子前移两项
					sz[i1] = sz[i1+2];
				i--; 
			}
		return dt[j+1];  //返回结果
    }
}
