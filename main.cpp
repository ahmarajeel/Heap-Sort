//Ahmar Mohammed

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class HeapSort
{
	private:
		int* heapArr;
		int size;
		char* inFile;
		char* outFile1;
		char* outFile2;
	
	
	public:
		HeapSort(int num, char* input, char* output1, char* output2)
		{
			
			size = num;
			inFile = input;
			outFile1 = output1;
			outFile2 = output2;
			heapArr = new int[size];
			
			for(int i = 0; i < size; i++)
			{
				heapArr[i] = 0;
			}
			buildHeap();
		}
		
		void buildHeap()
		{
			ifstream myFile(inFile);
			ofstream myoutFile1(outFile1);
			
			int item;
			while(myFile >> item && !isHeapFull())
			{
				insertOneItem(item);
				myoutFile1 << "Insert " << item << ":\t\t";
				myoutFile1 << printHeap(10) << endl;
			}
			myFile.close();
			myoutFile1.close();
			return;
		}
		
		bool isHeapEmpty()
		{
			if(heapArr[0] == 0)
				return true;
			else
				return false;
		}
		
		bool isHeapFull()
		{
			if(heapArr[0] == size-1)
				return true;
			else
				return false;
		}
		
		string printHeap(int num)
		{
			string str = "";
			for(int i = 1; i <= heapArr[0] && i <= num; i++)
			{
				ostringstream convert;
				convert << heapArr[i];
				str += convert.str() + " ";
			}
			return str;
		}
		
		void insertOneItem(int item)
		{
			heapArr[0]++;
			heapArr[heapArr[0]] = item;
			bubbleUp();
			return;
		}
		
		//delete root method
		void deleteRoot()
		{
			ofstream myoutFile1(outFile1, ios::app);  //ios:: app is neccesary to append
			ofstream myoutFile2(outFile2);
			myoutFile2 << "Sorted List: \n" ;
			while (!isHeapEmpty())
			{
				int rootItem = heapArr[1];
				myoutFile2 << rootItem << endl;
				heapArr[1] = heapArr[heapArr[0]];
				heapArr[0]--;
				bubbleDown(); 
				myoutFile1 << "Delete " << rootItem << ":\t\t";
				myoutFile1 << printHeap(10) << endl;
			}
			myoutFile1.close();
			myoutFile2.close();
			return;
		}
		
		// Bubble up method
		void bubbleUp()
		{
			int current = heapArr[0];
			while((current/2 > 0) && (heapArr[current] < heapArr[current/2]))
			{
				int temp = heapArr[current/2];
				heapArr[current/2] = heapArr[current];
				heapArr[current] = temp;
				current = current/2;	
			}
			return;
		}
		
		// Bubble down method
		void bubbleDown()
		{
			int pIndex = 1;
			int leftIndex = pIndex*2, rightIndex = (pIndex*2) + 1;
			 
			while((leftIndex <= heapArr[0] && heapArr[pIndex] > heapArr[leftIndex]) || (rightIndex <= heapArr[0] && heapArr[pIndex] > heapArr[rightIndex]))
			{
				if(rightIndex <= heapArr[0] && (heapArr[leftIndex] > heapArr[rightIndex])) 
				{
					int temp = heapArr[rightIndex];
					heapArr[rightIndex] = heapArr[pIndex];
					heapArr[pIndex] = temp;
					pIndex = rightIndex;	
				}
				else
				{
					int temp = heapArr[leftIndex];
					heapArr[leftIndex] = heapArr[pIndex];
					heapArr[pIndex] = temp;
					pIndex = leftIndex;	
				}
				leftIndex = pIndex*2;
				rightIndex = (pIndex*2) + 1;
			}
			return;
		}
		
		void deleteHeap()
		{
			deleteRoot();
			delete[] heapArr;
			heapArr = NULL;
			return;
		}
		
		//destructor
		~HeapSort()
		{
			delete[] heapArr;
		}
		
};

int main (int argc, char* argv[])
{
	int item, counter = 0;
		ifstream myFile;
		myFile.open(argv[1]);
		while(myFile >> item)
		{	
			counter++;
		}	
		myFile.close();
		HeapSort myHeap(counter+1,argv[1], argv[2], argv[3]);
		myHeap.deleteHeap();
}
