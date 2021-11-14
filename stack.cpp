#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define maxSize 100

//a template is defined so that the stack can be used for any data type.
template <typename dataType>
class Stack
{
      dataType array[maxSize]; //an array of maxsize 100
      int top = -1;

      //if top is equal to -1, that implies stack is empty.
      bool isEmpty()
      {
            return top == -1;
      }
      //if top is equal to maxsize -1, then the stack is full
      bool isFull()
      {
            return top == maxSize-1;
      }

      public:
            void push(dataType value)
            {
                  //if array is not full, then insert
                  if(!isFull())
                        array[++top] = value;
            }
            bool pop()
            {
                  //if array is not empty, then pop
                  if(isEmpty())
                        return false;
                  top--;
                  return true;
            }
            dataType* peek()
            {
                  //if array is not empty, then return the top element
                  if(!isEmpty())
                        return &array[top];
                  return NULL;
            }
            void print()
            {
                  //prints all the stack.
                  for (int i = top; i>= 0;i--)
                  {
                        cout << array[i]<<endl;
                  }
            }
};

class InfixConverter
{
      //declaring instance variables
      string infix ;
      string postfix ;
      int evaluatedOutput;
      Stack<char> stack;

      /*this function will evaluate the operand1 (operator) operand2
      type expression depending upon the operator*/
      double evaluate(int op1,int op2,char opr)
      {
            switch (opr)
            {
                  case '+':
                        return double(op1+op2);
                  case '-':
                        return double(op1-op2);
                  case '*':
                        return double(op1*op2);
                  case '/':
                        return double(op1/op2);
                  default:
                        return 0;
            }
      }

      //returns true if the argument is operator e.g. +,-,*,/
      bool isOperator(char value)
      {
            return value == '*' || value == '/' || value == '+' || value == '-';
      }

      //this function will convert infix to postfix.
      string convertToPostfix(string input)
      {
            string output = "";
            //until the input is scanned, for loop runs.
            for (char const temp : input)
            {
                  //if there is a bracket opener, it is pushed into stack.
                  if (temp=='(')
                  {
                        stack.push('(');
                  }
                  //if it is bracket closer, then stack will be poped until '('
                  else if(temp==')')
                  {
                        output+=" ";
                        while(*stack.peek() != '(')
                        {
                              output+=*stack.peek();
                              stack.pop();
                        }
                        stack.pop();
                  }
                  //if it is an operator, then the following conditions are checked.
                  else if(isOperator(temp))
                  {
                        output+=" ";

                        if (stack.peek() == NULL || (*stack.peek() == '('))
                              stack.push(temp);
                        else if((*stack.peek() == '+' || *stack.peek() == '-') && (temp=='*' || temp == '/'))
                              stack.push(temp);
                        else
                        {
                              while(!(stack.peek() == NULL) )
                              {
                                    output += *stack.peek();
                                    output+=' ';
                                    stack.pop();
                              }
                              stack.push(temp);
                        }

                  }
                  else if(temp != ' ')
                  {
                        output+=temp;
                  }
            }
            while(!(stack.peek() == NULL))
            {
                  output+=" ";
                  output+= *stack.peek();
                  stack.pop();
            }
            return output;
      }

      //this function will evaluate the postfix expression.
      double evaluatePostfix(string input)
      {
            Stack<double> evStack;
            string operand = "";
            double op1;
            double op2;

            for (char const val : input)
            {
                  if (isOperator(val))
                  {
                        op2 = *evStack.peek();
                        evStack.pop();
                        op1 = *evStack.peek();
                        evStack.pop();

                        evStack.push(evaluate(op1,op2,val));
                  }
                  else if (val == ' ' && operand != "")
                  {
                        evStack.push(stoi(operand));
                        operand = "";
                  }
                  else if (val != ' ')
                        operand += val;
            }
            if (!(evStack.peek() == NULL))
            {
                  op2 = *evStack.peek();
                  evStack.pop();
            }
            else if (!(operand == ""))
                  op2 = stoi(operand);

            return op2;
      }

      
      public:
            //constructor
            InfixConverter()
            {
                  infix = "";
                  postfix = "";
                  evaluatedOutput = 0;
            }
            //function to feed infix.
            void feedInfix(string input)
            {
                  infix = input;
                  postfix = convertToPostfix(infix);
                  evaluatedOutput = evaluatePostfix(postfix);
            }
            //getter for postfix
            string getPostfix()
            {
                  return postfix;
            }
            //getter for evaluated output
            double getOutput()
            {
                  return evaluatedOutput;
            }
            //function to return the instance variables of object.
            string toString()
            {
                  return "\nInfix              = " + infix +
                         "\nPostfix            = " + postfix +
                         "\nEvaluated Postfix  = " + to_string(evaluatedOutput); 
            }

};

int main()
{
      InfixConverter tn;

      //test case 1
      tn.feedInfix("9+9+88*(99*34)+(99-100)*199");
      cout << tn.toString() << endl;

      //test case 2
      tn.feedInfix("90*90*9+(99/9)/11+(90/9)+100");
      cout << tn.toString() << endl;

      return 0;
}