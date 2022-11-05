#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <atomic>
#include <thread>
#include <stdio.h>

using namespace std;

atomic<int> node_id = 0;

void event(int item_id)
{
  string url;
  int group_id = item_id & ~(~0U << 1);

  do {
    string it = to_string(item_id), 
    no = to_string(node_id), 
    gr = to_string(group_id);

    ++node_id;
    node_id &= ~(~0U << 1);
    
    url  = "curl https://demoflask.andrewgolovnev.repl.co/data/name/" + 
    gr + '/' + no + '/' + it + '/' + " --max-time 3";
  } while (WEXITSTATUS(system(url.c_str())) != 0);
  
  cout << '\n';
  
  ++node_id;
  node_id &= ~(~0U << 1);
}

int main()
{
  vector<int> req = {1, 13, 12, 20, 25};
  vector<thread*> th;
  
  for (auto idx : req) {
    thread* t = new thread(event, idx);
    th.push_back(t);
  }

  for (auto& t : th)
    t->join();
  
  cout << "Done\n";
}