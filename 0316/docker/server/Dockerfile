FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y libboost-all-dev g++ 
RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app

COPY server.cpp /usr/src/app
RUN  g++ server.cpp -o server -lboost_system

CMD  ["./server"]
