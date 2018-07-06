//the code is unperfect,it can not handle nagative sign.

#include "../../Include/Stack.hpp"

void cal_postfix(std::string tmp)
{/*{{{*/
	Stack<int> opnd;
	int operand1,operand2,result;
	char op;
	std::string::iterator cg = tmp.begin();
	while(cg != tmp.end())
	{
		operand1 = 0;
		// if(isdigit(*cg)|| *cg == '-')
		if(isdigit(*cg))
		{
			while(isdigit(*cg))
			{
				operand1 = operand1 * 10 + *cg - '0';
				cg++;
			}
			opnd.Push(operand1);
			/* if(*cg == '-' && opnd.Size() <= 1) */
			// {
				// while(isspace(*cg))
					// cg++;
				// while(isdigit)
			/* } */
		}
		while(isspace(*cg))
			cg++;
		if(!isdigit(*cg))
		{
			 op = *cg;
			 cg++;
			 if(opnd.Size() >= 2)
			 {/*{{{*/
				 opnd.Pop(operand2);
				 opnd.Pop(operand1);
			 	switch(op)
				{/*{{{*/
					case '+':
						result = operand1 + operand2;
						break;
					case '-':
						result = operand1 - operand2;
						break;
					case '*':
						result = operand1 * operand2;
						break;
					case '/':
						result = operand1 / operand2;
						break;
					case '%':
						result = operand1 % operand2;
						break;
				}/*}}}*/
				opnd.Push(result);
			 }/*}}}*/
			 else
			 {
				std::cout<<"invalid expression."<<std::endl;		
				exit(1);
			 }
		}
	}
	if(opnd.Size() == 1)
	{
		opnd.Pop(result);
		std::cout<<result<<std::endl;
	}
	else
	{
		std::cout<<"invalid expression"<<std::endl;
		exit(1);
	}
}/*}}}*/
int judgepos(char c)
{/*{{{*/
	if(c == '(')
		return 0;
	else if( c == '*' || c == '/' || c == '%')
		return 1;
	else if( c == '+' || c == '-')
		return 2;
	else if( c == ')')
		return 3;
	else
		return -1;
}/*}}}*/
void infixexp2posfix(std::string &res)
{/*{{{*/
	int isp[] = {1,5,3,6},icp[] = {6,4,2,1};
	//initialize in-stack and in-coming-stack operator priority
	//same operator have different priority in isp and icp because we should handle instack operator first.
	//the operator order of isp[] is same as icp[],the bigger num means the higher priority.
	//to reduce code work,write another function judgepos() to get the index of icp and isp.
	//		(	*,/,%	+,-		)
	//isp	1	  5		 3		6
	//icp	6	  4		 2		1
	Stack<char> optr;
	int ops,opc;
	char opsp,opcp;
	std::string result;//temporary result,assign to res in the end.
	std::string::iterator cg = res.begin();
	while(cg != res.end())
	{/*{{{*/
		if(isdigit(*cg) || isspace(*cg) || ispunct(*cg))
		{
			while(isdigit(*cg) || isspace(*cg))
			{
				result += *cg;
				cg++;
			}
			if(ispunct(*cg))
			{
				result += ' ';//
				if(optr.IsEmpty())
				{
					optr.Push(*cg);
					cg++;
				}
				else
				{
					optr.Top(opsp);
					opcp = *cg;
					ops = judgepos(opsp);
					opc = judgepos(opcp);
					if(ops == -1 || opc == -1)
					{
						std::cout<<"invalid expression"<<std::endl;
						exit(1);
					}
					if(icp[opc] > isp[ops])
					{
						optr.Push(opcp);
						cg++;
					}
					else if(icp[opc] < isp[ops])
					{
						optr.Pop(opsp);
						result += opsp;
					}
					else
					{
						optr.Pop(opsp);
						cg++;
					}
				}
			}
		}
		else
			cg++;
	}/*}}}*/
	while(!optr.IsEmpty())
	{
		optr.Pop(opsp);
		result += opsp;
	}
	res = result;
	std::cout << res << std::endl;
}/*}}}*/
/* int main() */
// {
	// std::string tmp;
	// while(getline(std::cin,tmp))
	// {
		// infixexp2posfix(tmp);
		// cal_postfix(tmp);
	// }
/* } */
