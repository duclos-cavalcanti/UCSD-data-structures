#include <iostream>
#include <queue>
#include <vector>

struct Request {
  Request(int arrival_time, int process_time):
      arrival_time(arrival_time),
      process_time(process_time)
  {}

  int arrival_time;
  int process_time;
};

struct Response {
  Response(bool dropped, int start_time):
      dropped(dropped),
      start_time(start_time)
  {}

  bool dropped;
  int start_time;
};

class Buffer {
public:
  Buffer(int size):
      size_(size),
      finish_time_()
      {}

  Response Process(const Request &request) {
    Response response(false, 0);
    if (this->isBufferEmpty()) {
      finish_time_.push(request.arrival_time + request.process_time);
      response.start_time = request.arrival_time;
    } else {
      if (this->isBufferFree(request.arrival_time)) {
        if (request.arrival_time > finish_time_.back())
          response.start_time = request.arrival_time;
        else
          response.start_time = finish_time_.back();

        finish_time_.pop();
        finish_time_.push(finish_time_.back() + request.process_time);
      } else {
        if (this->getBufferSize() >= size_) {
          response.dropped = true;
        } else {
          response.start_time = finish_time_.back();
          finish_time_.push(finish_time_.back() + request.process_time);
        }
      }
    }
    return response;
  }

private:
  int size_;
  std::queue <int> finish_time_;

  int getBufferSize(void) {
    return finish_time_.size();
  }

  bool isBufferEmpty(void) {
    return finish_time_.empty();
  }

  bool isBufferFree(const int at) {
    int ft = finish_time_.front();
    if (at >= ft)
      return true;
    else
      return false;
  }

};

std::vector <Request> ReadRequests() {
  std::vector <Request> requests;
  int count;
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    int arrival_time, process_time;
    std::cin >> arrival_time >> process_time;
    requests.push_back(Request(arrival_time, process_time));
  }
  return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
  std::vector <Response> responses;
  for (int i = 0; i < requests.size(); ++i)
    responses.push_back(buffer->Process(requests[i]));

  return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
  for (int i = 0; i < responses.size(); ++i)
      std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
  // first line of the input contains the size 'S' of the buffer and the number of packets 'n'
  int size;
  std::cin >> size;
  std::vector <Request> requests = ReadRequests();

  Buffer buffer(size);
  std::vector <Response> responses = ProcessRequests(requests, &buffer);

  PrintResponses(responses);
  return 0;
}
