#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Token_Max 20
#define Stack_Max 50

void push_stack(char);
char pop_stack();
int comp_token(char,char);
void three_num_code(char [],int);
void CPU_code(char,char,char,char);

/*スタック*/
char stack[Stack_Max];
int stnum;

int main()
{

	int tnum;	//token number
	int onum;	//outstring number
	int i;
	/*トークン格納用配列*/
	char token[Token_Max];
	/*最終出力用配列*/
	char outstring[Token_Max];

	onum=tnum=0;
	char c,d;
	
	/*トークン読み込み*/
	for(;;)
	{
		printf("token[%d] : ",tnum);
		fflush(stdout);
		scanf("%c",&c);
		scanf("%c",&d);
		/*終了判定*/
		if(c=='q')
		{
			break;
		}else if(tnum>=Token_Max)		//オーバーフロー判定
		{
			printf("Overflow\n");
			exit(1);
		}else token[tnum]=c;
		
		tnum++;
	}
	
	/*トークン表示*/
	for(i=0;i<tnum;i++)
	{
		printf("%c",token[i]);
	}
	printf("\n");
	
	
	/*逆ポーランド変換*/
	for(i=0;i<tnum;i++)
	{
		if(token[i]>='A' && token[i]<='Z')
		{
			outstring[onum]=token[i];
			onum++;
		}else if(token[i]=='(')
		{
			push_stack(token[i]);
		}else if(token[i]==')')
		{
			for(;;)
			{
				c=pop_stack();
				if(c!='(')
				{
					outstring[onum]=c;
					onum++;
				}else break;
			}
		}else
		{
			c=pop_stack();
			/*スタックが空のとき無条件push*/
			if(c=='$')
			{
				//push_stack(c);
				push_stack(token[i]);
			}else
			{
				/*tokenの優先度>topの優先度*/
				if(comp_token(token[i],c)==1)
				{
					push_stack(c);
					push_stack(token[i]);
				}else
				{
					for(;;)
					{
						outstring[onum]=c;
						onum++;
						c=pop_stack();
						if(comp_token(token[i],c)==1)
						{
							push_stack(c);
							push_stack(token[i]);
							break;
						}
					}
				}
			}
		}
	}
	
	
	c=pop_stack();
	while(c!='$')
	{
		outstring[onum]=c;
		onum++;
		c=pop_stack();
	}
	
	printf("outstring : ");
	for(i=0;i<onum;i++)
		printf("%c",outstring[i]);
	printf("\n");
	
	three_num_code(outstring,onum);
	
	return 0;
}

void push_stack(char c)
{
	if(stnum==Token_Max)
	{
		printf("Overflow\n");
	}else
	{
		stack[stnum]=c;
		stnum++;
	}

}


char pop_stack()
{
	if(stnum<0)
	{
		printf("No Such Data\n");
		return '\0';
	}else if(stnum==0)
	{
		return '$';
	}else
	{
		stnum--;
		stack[stnum+1]='\0';
		return stack[stnum];
	}
}


int comp_token(char t,char s)
{
	int tn,sn;
	switch(t)
	{
		case '*':
		case '/':
			tn=3;
			break;
		case '+':
		case '-':
			tn=2;
			break;
		case '=':
		case '(':
			tn=1;
			break;
		case ')':
		case '$':
			tn=0;
			break;
		default:
			break;
	}

	switch(s)
	{
		case '*':
		case '/':
			sn=3;
			break;
		case '+':
		case '-':
			sn=2;
			break;
		case '=':
		case '(':
			sn=1;
			break;
		case ')':
		case '$':
			sn=0;
			break;
		default:
			break;
	}
	
	if(tn>=sn) return 1;
	else return 0;
}


void three_num_code(char str[],int num)
{
	char threecode[4];
	char twocode[3];
	int i;
	char c,ss;
	ss='a';
	for(i=0;i<num;i++)
	{
		if((str[i]>='A') && (str[i]<='Z'))
		{
			push_stack(str[i]);
		}else if(str[i]!='=')
		{
			threecode[0]=str[i];
			c=pop_stack();
			threecode[2]=c;
			c=pop_stack();
			threecode[1]=c;
			threecode[3]=ss;
			push_stack(ss);
			(int)ss++;
			
			printf("%c(%c %c %c)\n",threecode[0],threecode[1],threecode[2],threecode[3]);
			CPU_code(threecode[0],threecode[1],threecode[2],threecode[3]);
		}else if(str[i]=='=')
		{
			twocode[0]=str[i];
			c=pop_stack();
			twocode[1]=c;
			c=pop_stack();
			twocode[2]=c;
			
			printf("%c(%c %c)\n",twocode[0],twocode[1],twocode[2]);
			CPU_code(twocode[0],twocode[1],twocode[2],'\0');	//変数埋め用\0
		}
	}
}


void CPU_code(char calc,char va1,char va2,char va3)
{
	printf("[LD $%c]\n",va1);
	switch (calc)
	{
		case '+':
			printf("[AD $%c]\n",va2);
			break;
		case '-':
			printf("[SB $%c]\n",va2);
			break;
		case '*':
			printf("[ML $%c]\n",va2);
			break;
		case '/':
			printf("[DV $%c]\n",va2);
			break;
		case '=':
			va3=va2;
			break;
		default:
			break;
	}
	printf("[ST $%c]\n",va3);
}
