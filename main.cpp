#include "Lexer.h"
#include "SafeQueue.h"
#include <thread>

//TEST CONFIGURATIONS
const int N_THREADS = 14;

///PATHS
const string TEST_PATH = "./test_files";
const string RESULT_PATH = "./result_files";

//MULTITHREAD SAFE QUEUE
SafeQueue<fs::path> q;


void produce()
{
	for (const fs::path entry : fs::directory_iterator(TEST_PATH))
	{
		q.enqueue(entry);
	}
	
}

void consume()
{
	Lexer lex("table.csv", "states_definitions.txt");
	while (!q.isEmpty())
	{	
		fs::path path = q.dequeue();
		lex.analyze(path, RESULT_PATH);
	}	
}


void multithreadedAnalyzer(int nThreads, bool secuentiallyProduce = false)
{
	//PRODUCER THREAD
	thread producer(produce);

	//SECUENTIAL CONTROL
	if(secuentiallyProduce == true)
	{
		producer.join();
	}

	//CONSUMER THREADS
	vector<thread> consumers(nThreads);
	for (int i = 0; i < nThreads; i++)
	{
		consumers[i] = thread(consume);
	}

	//JOIN THREADS
	if (secuentiallyProduce == false)
	{
		producer.join();
	}
	for (int i = 0; i < nThreads; i++)
	{
		consumers[i].join();
	}
}


int main()
{
	//BEGIN TIMING
	for (int nThreads = 1; nThreads <= N_THREADS; nThreads++)
	{
		cout << "NUM THREADS: " << nThreads << endl << "DURATION: ";
		auto start = chrono::high_resolution_clock::now();
		multithreadedAnalyzer(nThreads, true);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = end - start;
		cout << duration.count() << endl << "------------------------------" << endl;
	}
	return 0;
}		