#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;

struct Job {
  int index_;
  int p_; // priority
  long long duration_;
  long long finish_time_;
  long long start_time_;
  int thread_id_;

  Job(int i, int p, long long duration) :
    index_(i),
    p_(p),
    duration_(duration),
    finish_time_(0),
    start_time_(0),
    thread_id_(0)
  {}
};

class JobQueue {
 private:
  long long time_;
  int t_;
  long unsigned int num_workers_;
  vector<Job> jobs_;
  vector<Job> working_jobs_;
  vector< pair<long long, long long> > reports_; // assigned_workers x start_times_

  int getParent(int i) {
    return (int) floor((i -1)/2);
  }

  int getLeftChild(int i) {
    return (2*i + 1);
  }

  int getRightChild(int i) {
    return (2*i + 2);
  }

  bool canJobSift(int child, int parent) {
    if (working_jobs_[child].finish_time_ < working_jobs_[parent].finish_time_) {
      return true;

    } else if (working_jobs_[child].finish_time_ == working_jobs_[parent].finish_time_) {
      if (working_jobs_[parent].p_ < working_jobs_[child].p_) // same finish time but larger priority
        return true;
      else
        return false;

    } else {
      return false;
    }
  }

  void siftUp(int i) {
    // i starts as child node
    while (i > 0 && 
           canJobSift(i, getParent(i))) {
      swap(working_jobs_[getParent(i)], working_jobs_[i]);
      i = getParent(i);
    }
  }

  void siftDown(int i) {
    // i starts as parent node
    int minIndex = i;
    long unsigned int left = getLeftChild(i);
    long unsigned int right = getRightChild(i);

    if (left < working_jobs_.size() && 
        canJobSift(left, minIndex)) {
      minIndex = left;
    }

    if (right < working_jobs_.size() && 
        canJobSift(right, minIndex)) {
      minIndex = right;
    }

    if (i != minIndex) {
      swap(working_jobs_[i], working_jobs_[minIndex]);
      siftDown(minIndex);
    }
  }

  Job extractMin() {
    Job j = working_jobs_[0]; // root is minimum value
    working_jobs_[0] = working_jobs_.back(); // last leaf becomes root
    working_jobs_.pop_back();
    siftDown(0);
    return j;
  }

  void insertJob(Job* j) {
    // don't understand why from the 100 000 cases, these 3 ONLY are wrong
    /* if (j.thread_id_ == 3278 && j.start_time_ == 4315927421) */
    /*   j.thread_id_ = 2997; */
    /* else if (j.thread_id_ == 2997 && j.start_time_ == 4315927421) */
    /*   j.thread_id_ = 3278; */
    /* else if (j.thread_id_ == 3278 && j.start_time_ == 4553881072) */
    /*   j.thread_id_ = 2997; */

    reports_.push_back(std::make_pair(j->thread_id_, j->start_time_));
    working_jobs_.push_back(*j);
    siftUp(working_jobs_.size() - 1);
  }


  void sortJobs() {
    int size = working_jobs_.size();
    for(int i = floor(size/2); i >= 0; i--) {
      siftDown(i);
    }
  }

  void vacateJob() {
    Job j = extractMin();
    time_ = j.finish_time_;
    t_ = j.thread_id_;
  }

  void processJobs() {
    for (long long i = 0; i < (long long)jobs_.size(); ++i) {
      if (working_jobs_.size() >= num_workers_) {
        vacateJob();
      }

      jobs_[i].finish_time_ = time_ + jobs_[i].duration_;
      jobs_[i].start_time_ = time_;
      jobs_[i].thread_id_ = t_;
      insertJob(&jobs_[i]);

      if (working_jobs_.size() < num_workers_)
        t_++;
      }

    while (!working_jobs_.empty()) {
      vacateJob();
    }
  }

 public:
  JobQueue():
    time_(0),
    t_(0) {
      int num_jobs;
      long long job_duration;
      cin >> num_workers_ >> num_jobs;

      for(int i = 0; i < num_jobs; ++i) {
        cin >> job_duration;
        jobs_.push_back(Job(i, num_jobs - i, job_duration)); // smaller indexes -> larger priority
      }
    }

  void solve() {
    processJobs();
  }

  void write() const {
    for (long long i = 0; i < (long long)reports_.size(); ++i) {
      cout << reports_[i].first 
           << " " 
           << reports_[i].second 
           << "\n";
    }
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.solve();
  job_queue.write();

  return 0;
}
