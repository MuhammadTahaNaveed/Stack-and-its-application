#include <iostream>
#include <string>
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

int main()
{
      Stack <int> stack;
      stack.push(100);
      cout << *stack.peek();
      stack.pop();      

      return 0;
}